#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/AST_Genere.h"

void VisiteurGeneralGenCode::visiter([[maybe_unused]]NoeudArgFonction* noeudArgFonction) 
{
    _contextGenCode->valeurTemporaire.adresse = nullptr;
}