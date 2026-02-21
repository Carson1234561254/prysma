#include "Compilateur/AST/Noeuds/Variable/NoeudRefVariable.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"

void VisiteurGeneralGenCode::visiter(NoeudRefVariable* noeudRefVariable) 
{
    Token variableToken;
    variableToken.value = noeudRefVariable->getNomVariable();
    Symbole symbole = _contextGenCode->registreVariable->recupererVariables(variableToken);
    llvm::Value* variable = symbole.adresse;
    _contextGenCode->valeurTemporaire.adresse = variable;
    _contextGenCode->valeurTemporaire.type = symbole.type;
}
