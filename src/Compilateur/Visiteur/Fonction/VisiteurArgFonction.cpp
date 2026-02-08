#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"

void VisiteurGeneralGenCode::visiter([[maybe_unused]]NoeudArgFonction* noeudArgFonction) 
{
    // C'est le parent qui gère en récupèrant les informations des enfants
    _contextGenCode->valeurTemporaire = nullptr;
}