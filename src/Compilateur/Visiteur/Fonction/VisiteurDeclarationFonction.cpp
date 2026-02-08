#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudDeclarationFonction.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudArgFonction.h"
#include <string>


void VisiteurGeneralGenCode::visiter(NoeudDeclarationFonction* noeudDeclarationFonction) 
{
    llvm::Type* retType = _contextGenCode->registreType->getType(noeudDeclarationFonction->_typeRetourToken);
    
    std::vector<llvm::Type*> argTypes;
    const auto& enfants = noeudDeclarationFonction->getEnfants();
    
    for (size_t i = 0; i < enfants.size(); ++i) {
        auto* noeudArg = dynamic_cast<NoeudArgFonction*>(enfants[i].get());
        if (noeudArg != nullptr) {
            llvm::Type* argType = _contextGenCode->registreType->getType(noeudArg->_type);
            argTypes.push_back(argType);
        }
    }
    
    llvm::FunctionType* funcType = llvm::FunctionType::get(retType, argTypes, false);

    llvm::Function* function = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        noeudDeclarationFonction->_nom,
        &_contextGenCode->backend->getModule()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(_contextGenCode->backend->getContext(), "entry", function);
    _contextGenCode->backend->getBuilder().SetInsertPoint(entryBlock);

    _contextGenCode->registreFonction->enregistrer(noeudDeclarationFonction->_nom, function);

    _contextGenCode->returnContextCompilation->piler(noeudDeclarationFonction->_typeRetourToken);
    _contextGenCode->registreVariable->piler();

    size_t argIndex = 0;
    for (size_t i = 0; i < enfants.size(); ++i) {
        auto* noeudArg = dynamic_cast<NoeudArgFonction*>(enfants[i].get());
        if (noeudArg != nullptr) {
            llvm::Argument* arg = function->getArg(argIndex);
            arg->setName(noeudArg->_nom);
            
            llvm::Type* argType = arg->getType();
            llvm::AllocaInst* alloca = _contextGenCode->backend->getBuilder().CreateAlloca(argType);
            _contextGenCode->backend->getBuilder().CreateStore(arg, alloca);
            
            Token argumentToken;
            argumentToken.value = noeudArg->_nom;
            argumentToken.type = TOKEN_IDENTIFIANT;
            
            _contextGenCode->registreVariable->enregistrer(argumentToken, alloca);
            
            argIndex++;
        }
    }

    for (size_t i = 0; i < enfants.size(); ++i) {
        auto* noeudArg = dynamic_cast<NoeudArgFonction*>(enfants[i].get());
        if (noeudArg == nullptr) {
            enfants[i]->accept(this);
        }
    }

    _contextGenCode->registreVariable->depiler();
    _contextGenCode->returnContextCompilation->depiler();

    _contextGenCode->valeurTemporaire = function;
}