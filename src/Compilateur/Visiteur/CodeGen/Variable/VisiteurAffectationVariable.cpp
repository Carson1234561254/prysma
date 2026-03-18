#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/LLVM/GestionVariable.h"

void VisiteurGeneralGenCode::visiter(NoeudAffectationVariable* noeudAffectationVariable)
{
    llvm::Value* expressionResult = evaluerExpression(noeudAffectationVariable->getExpression()).adresse;

    AdresseurVariable adresseur(_contextGenCode);
    Symbole symbole = adresseur.recupererAdresse(noeudAffectationVariable->getToken().value);
    
    llvm::Value* variableExistante = symbole.adresse;
    
    llvm::Type* typeVariableLLVM = nullptr;
    if (symbole.type != nullptr) {
        typeVariableLLVM = symbole.type->genererTypeLLVM(_contextGenCode->backend->getContext());
    }
    
    AffecteurVariable affecteur(_contextGenCode);
    affecteur.affecter(variableExistante, expressionResult, typeVariableLLVM);
    
    // Reset la valeur pour éviter des problèmes
    _contextGenCode->valeurTemporaire.adresse = nullptr;
}

