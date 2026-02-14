#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudArgFonction.h"

void VisiteurGeneralGenCode::visiter([[maybe_unused]]NoeudArgFonction* noeudArgFonction) 
{
    _contextGenCode->valeurTemporaire = nullptr;
}