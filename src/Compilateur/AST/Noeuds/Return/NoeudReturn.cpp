#include "Compilateur/AST/Noeuds/Return/NoeudReturn.h"
#include "Compilateur/LLVM/LLVMBackend.h"
#include <llvm-18/llvm/IR/Instructions.h>
#include <utility>

NoeudReturn::NoeudReturn(std::shared_ptr<LLVMBackend> backend, std::shared_ptr<INoeud> valeurRetour, llvm::Type* typeRetour)
    : _backend(std::move(backend)), _valeurRetour(std::move(valeurRetour)), _typeRetour(typeRetour)
{
}

llvm::Value* NoeudReturn::genCode()
{
    if (_backend == nullptr) {
        throw std::runtime_error("Erreur : backend LLVM non initialisé dans NoeudReturn");
    }

    if (_valeurRetour == nullptr) {
        _backend->getBuilder().CreateRetVoid();
        return nullptr;
    }

    llvm::Value* valeur = _valeurRetour->genCode();
    if (valeur == nullptr) {
        throw std::runtime_error("Erreur : impossible d'évaluer l'expression de retour");
    }

    if (_typeRetour != nullptr && valeur->getType() != _typeRetour) {

        if (_typeRetour->isIntegerTy() && valeur->getType()->isFloatTy()) {
            valeur = _backend->getBuilder().CreateFPToSI(valeur, _typeRetour);
        }
        else if (_typeRetour->isFloatTy() && valeur->getType()->isIntegerTy()) {
            valeur = _backend->getBuilder().CreateSIToFP(valeur, _typeRetour);
        }
    }

    _backend->getBuilder().CreateRet(valeur);
    return valeur;
}
