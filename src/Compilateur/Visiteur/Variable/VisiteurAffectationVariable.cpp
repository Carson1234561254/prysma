#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudAffectationVariable.h"
#include "Compilateur/AST/Registre/ContextGenCode.h"
#include <llvm-18/llvm/IR/Instructions.h>

void assignation(llvm::AllocaInst* allocaInst, llvm::Value* valeur, std::shared_ptr<ContextGenCode> contextGenCode);

void VisiteurGeneralGenCode::visiter(NoeudAffectationVariable* noeudAffectationVariable)
{

    llvm::Value* expressionResult = evaluerExpression(noeudAffectationVariable->_expression);

    llvm::Value* valeur = _contextGenCode->registreVariable->recupererVariables(noeudAffectationVariable->_token);
    llvm::AllocaInst*  variableExistante = llvm::dyn_cast<llvm::AllocaInst>(valeur);
    assignation(variableExistante, expressionResult, _contextGenCode);
    
    // Reset la valeur pour éviter des problèmes
    _contextGenCode->valeurTemporaire = nullptr;
}


void assignation(llvm::AllocaInst* allocaInst, llvm::Value* expressionResult, std::shared_ptr<ContextGenCode> contextGenCode)
{
 
    llvm::Value* valeurCast = contextGenCode->backend->creerAutoCast(expressionResult, allocaInst->getAllocatedType());
    contextGenCode->backend->getBuilder().CreateStore(valeurCast, allocaInst);
    
}

