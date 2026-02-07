#include "Compilateur/AST/Noeuds/Fonction/NoeudArgPassFonction.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"

void VisiteurGeneralGenCode::visiter(NoeudArgPassFonction* noeudArgPassFonction)
{ 
    llvm::Value* valeurVariable =  _contextGenCode->registreVariable->recupererVariables(noeudArgPassFonction->_tokenVariable);
    _contextGenCode->registreArgument->ajouter(valeurVariable);
    _contextGenCode->valeurTemporaire = valeurVariable;   
}