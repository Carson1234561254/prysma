#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudDeclarationFonction.h"
#include <string>


void VisiteurGeneralGenCode::visiter(NoeudDeclarationFonction* noeudDeclarationFonction) 
{
     if (_contextGenCode->backend == nullptr) {
        throw std::runtime_error("Erreur : backend LLVM non initialisé dans NoeudDeclarationFonction");
    }

    llvm::Type* retType = _contextGenCode->registreType->getType( noeudDeclarationFonction->_typeRetourToken);
    llvm::FunctionType* funcType = llvm::FunctionType::get(retType, false);

    llvm::Function* function = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
         noeudDeclarationFonction->_nom,
        &_contextGenCode->backend->getModule()
    );

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(_contextGenCode->backend->getContext(), "entry", function);
    _contextGenCode->backend->getBuilder().SetInsertPoint(entryBlock);

    _contextGenCode->registreFonction->enregistrer( noeudDeclarationFonction->_nom, function);

    _contextGenCode->returnContextCompilation->piler( noeudDeclarationFonction->_typeRetourToken);
    _contextGenCode->registreVariable->piler();

    parcourirEnfant(noeudDeclarationFonction);

    _contextGenCode->registreVariable->depiler();
    _contextGenCode->returnContextCompilation->depiler();

    _contextGenCode->valeurTemporaire = function;
    
}