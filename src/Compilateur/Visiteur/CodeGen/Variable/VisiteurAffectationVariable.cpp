#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/LLVM/GestionVariable.h"

void VisiteurGeneralGenCode::visiter(NoeudAffectationVariable* noeudAffectationVariable)
{
    GestionVariable gestionVariable(_contextGenCode);

    llvm::Value* expressionResult = evaluerExpression(noeudAffectationVariable->getExpression()).adresse;

    Symbole symbole = _contextGenCode->registreVariable->recupererVariables(noeudAffectationVariable->getToken());
    llvm::Value* valeur = symbole.adresse;
    llvm::AllocaInst* variableExistante = llvm::dyn_cast<llvm::AllocaInst>(valeur);
    
    gestionVariable.affecterVariable(variableExistante, expressionResult);
    
    // Reset la valeur pour éviter des problèmes
    _contextGenCode->valeurTemporaire.adresse = nullptr;
}

