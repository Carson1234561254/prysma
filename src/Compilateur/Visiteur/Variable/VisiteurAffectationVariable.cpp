#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudAffectationVariable.h"
#include "Compilateur/AST/Registre/ContextGenCode.h"

void assignation(llvm::AllocaInst* allocaInst, llvm::Value* valeur, std::shared_ptr<ContextGenCode> contextGenCode);
llvm::AllocaInst* recupererVariable(NoeudAffectationVariable* noeudAffectationVariable, std::shared_ptr<ContextGenCode> contextGenCode);

void VisiteurGeneralGenCode::visiter(NoeudAffectationVariable* noeudAffectationVariable)
{
    // Évaluer l'expression et assigner immédiatement
    llvm::Value* valeur = nullptr;
    if (noeudAffectationVariable->_expression != nullptr) {
        noeudAffectationVariable->_expression->accept(this);
        valeur = _contextGenCode->valeurTemporaire;
    }
    assignation(recupererVariable(noeudAffectationVariable, _contextGenCode), valeur, _contextGenCode);
    
    // Reset la valeur pour éviter des problèmes
    _contextGenCode->valeurTemporaire = nullptr;
}


void assignation(llvm::AllocaInst* allocaInst, llvm::Value* valeur, std::shared_ptr<ContextGenCode> contextGenCode)
{
    if (valeur != nullptr && allocaInst != nullptr)
    {
        // Si la valeur est une AllocaInst (variable), charger sa valeur
        if (auto* sourceAlloca = llvm::dyn_cast<llvm::AllocaInst>(valeur)) {
            llvm::Value* loadedValue = contextGenCode->backend->getBuilder().CreateLoad(sourceAlloca->getAllocatedType(), sourceAlloca);
            contextGenCode->backend->getBuilder().CreateStore(loadedValue, allocaInst);
        } else {
            // Sinon, assigner directement la valeur
            llvm::Value* valeurCast = contextGenCode->backend->creerAutoCast(valeur, allocaInst->getAllocatedType());
            contextGenCode->backend->getBuilder().CreateStore(valeurCast, allocaInst);
        }
    }
}


llvm::AllocaInst* recupererVariable(NoeudAffectationVariable* noeudAffectationVariable, std::shared_ptr<ContextGenCode> contextGenCode)
{
    // Récupérer la variable existante du registre
    llvm::AllocaInst* variableExistante = nullptr;
    if (contextGenCode->registreVariable != nullptr) {
        try {
            llvm::Value* valeur = contextGenCode->registreVariable->recupererVariables(noeudAffectationVariable->_token);
            variableExistante = llvm::dyn_cast<llvm::AllocaInst>(valeur);
        } catch (const std::exception& e) {
            // La variable n'existe pas
            throw std::runtime_error(std::string("Erreur : la variable '") + noeudAffectationVariable->_nom + "' n'existe pas. Vous devez d'abord la déclarer avec 'dec type nom = valeur;'");
        }
    }
    return variableExistante;
}

