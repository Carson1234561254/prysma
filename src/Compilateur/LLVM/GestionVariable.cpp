#include "Compilateur/LLVM/GestionVariable.h"
#include <llvm-18/llvm/IR/Type.h>
#include <stdexcept>

ExtracteurTypeVariable::ExtracteurTypeVariable(ContextGenCode* context) : _context(context) {}

llvm::Type* ExtracteurTypeVariable::extraire(llvm::Value* adresseMemoire) {
    if (auto* allocaInst = llvm::dyn_cast<llvm::AllocaInst>(adresseMemoire)) {
        return allocaInst->getAllocatedType();
    }
    return llvm::Type::getFloatTy(_context->backend->getContext());
}

AdresseurVariable::AdresseurVariable(ContextGenCode* context) : _context(context) {}

Symbole AdresseurVariable::recupererAdresse(const std::string& nomVariable) {
    Token tokenRecherche;
    tokenRecherche.value = nomVariable;

    if (_context->registreVariable->existeVariable(nomVariable)) {
        return _context->registreVariable->recupererVariables(tokenRecherche);
    }

    if (!_context->nomClasseCourante.empty()) {
        auto* classInfo = _context->registreClass->recuperer(_context->nomClasseCourante);
        if (classInfo->memberIndices.find(nomVariable) != classInfo->memberIndices.end()) {
            unsigned int idx = classInfo->memberIndices[nomVariable];
            
            Symbole modeleSymbole;
            if(classInfo->registreVariable->existeVariable(nomVariable)) {
                modeleSymbole = classInfo->registreVariable->recupererVariables(tokenRecherche);
            }

            Token thisToken; thisToken.value = "this";
            Symbole thisSymbole = _context->registreVariable->recupererVariables(thisToken);
            
            llvm::Value* thisPtrAddr = thisSymbole.adresse;
            llvm::Type* pointeurType = llvm::PointerType::getUnqual(_context->backend->getContext());

            llvm::Value* thisPtr = _context->backend->getBuilder().CreateLoad(pointeurType, thisPtrAddr, "this_val");

            std::vector<llvm::Value*> indices = {
                _context->backend->getBuilder().getInt32(0),
                _context->backend->getBuilder().getInt32(idx)
            };

            llvm::Value* fieldPtr = _context->backend->getBuilder().CreateGEP(
                classInfo->structType,
                thisPtr,
                indices,
                nomVariable + "_ptr"
            );

            return Symbole(fieldPtr, modeleSymbole.type, modeleSymbole.typePointeElement);
        }
    }

    throw std::runtime_error("Erreur sémantique : La variable '" + nomVariable + "' n'est pas déclarée.");
}

ChargeurVariable::ChargeurVariable(ContextGenCode* context) 
    : _context(context), _adresseur(context), _extracteur(context) {}

Symbole ChargeurVariable::charger(const std::string& nomVariable) {
    Symbole symbole = _adresseur.recupererAdresse(nomVariable);
    llvm::Value* adresseMemoire = symbole.adresse;
    
    llvm::Type* typeDonneeVal = nullptr;
    if (symbole.type != nullptr) {
        typeDonneeVal = symbole.type->genererTypeLLVM(_context->backend->getContext());
    } else {
        typeDonneeVal = _extracteur.extraire(adresseMemoire);
    }
    
    llvm::Value* valeurChargee = _context->backend->getBuilder().CreateLoad(
        typeDonneeVal,
        adresseMemoire,
        nomVariable
    );

    symbole.adresse = valeurChargee;
    return symbole;
}

Symbole ChargeurVariable::chargerUnref(const std::string& nomVariable) {
    Symbole symbole = _adresseur.recupererAdresse(nomVariable);
    llvm::Value* adresseMemoire = symbole.adresse;
    
    llvm::Type* typeDonneeVal = nullptr;
    if (symbole.type != nullptr) {
        typeDonneeVal = symbole.type->genererTypeLLVM(_context->backend->getContext());
    } else {
        typeDonneeVal = _extracteur.extraire(adresseMemoire);
    }
    
    if (adresseMemoire == nullptr) {
        throw std::runtime_error("Erreur sémantique : La variable '" + nomVariable + "' n'est pas déclarée.");
    }

    if(typeDonneeVal->isPointerTy()) {   
        llvm::Value* adressePointeur = _context->backend->getBuilder().CreateLoad(
            typeDonneeVal,
            adresseMemoire,
            nomVariable
        );

        llvm::Type* typePointeElement = symbole.typePointeElement;
        if (typePointeElement == nullptr) {
            typePointeElement = llvm::Type::getInt32Ty(_context->backend->getContext());
        }

        llvm::Value* valeurChargeDeuxiemeSaut = _context->backend->getBuilder().CreateLoad(
            typePointeElement,
            adressePointeur,
            nomVariable + "_unref"
        );

        symbole.adresse = valeurChargeDeuxiemeSaut;
    } else {
        throw std::runtime_error("Erreur sémantique : La variable '" + nomVariable + "' n'est pas un pointeur. Unref ne peut s'appliquer qu'à des pointeurs.");
    }

    return symbole;
}

AllocateurVariable::AllocateurVariable(ContextGenCode* context) : _context(context) {}

llvm::AllocaInst* AllocateurVariable::allouer(llvm::Type* type, const std::string& nomVariable) {
    llvm::BasicBlock* insertBlock = _context->backend->getBuilder().GetInsertBlock();
    _context->backend->definirPointInsertionApresAllocation();

    llvm::AllocaInst* allocaInst = _context->backend->getBuilder().CreateAlloca(type, nullptr, nomVariable);
    
    _context->backend->getBuilder().SetInsertPoint(insertBlock);

    return allocaInst;
}

void AllocateurVariable::stocker(llvm::Value* valeur, llvm::AllocaInst* allocaInst) {
    _context->backend->getBuilder().CreateStore(valeur, allocaInst);
}

AffecteurVariable::AffecteurVariable(ContextGenCode* context) 
    : _context(context), _extracteur(context) {}

void AffecteurVariable::affecter(llvm::Value* variableExistante, llvm::Value* valeur, llvm::Type* typeVariableLLVM) {
    llvm::Type* typeAllouer = typeVariableLLVM;
    if (typeAllouer == nullptr) {
        if (auto* allocaValue = llvm::dyn_cast<llvm::AllocaInst>(variableExistante)) {
            typeAllouer = allocaValue->getAllocatedType();
        } else {
            typeAllouer = _extracteur.extraire(variableExistante);
        }
    }

    if(typeAllouer->isPointerTy()) {
        llvm::Value* valeurCharger = _context->backend->getBuilder().CreateLoad(
            _context->backend->getBuilder().getPtrTy(),
            variableExistante,
            "ptr_chargé"
        );
        _context->backend->getBuilder().CreateStore(valeur, valeurCharger);
    } else {
        llvm::Value* valeurCast = _context->backend->creerAutoCast(valeur, typeAllouer);
        _context->backend->getBuilder().CreateStore(valeurCast, variableExistante);
    }
}
