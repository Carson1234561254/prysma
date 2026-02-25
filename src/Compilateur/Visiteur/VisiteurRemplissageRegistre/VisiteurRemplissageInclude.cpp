#include "Compilateur/Visiteur/VisiteurRemplissageRegistre/VisiteurRemplissageRegistre.h"
#include "Compilateur/AST/Utils/OrchestrateurInclude/OrchestrateurInclude.h" 
#include "Compilateur/AST/Noeuds/Include/NoeudInclude.h" 


void VisiteurRemplissageRegistre::visiter(NoeudInclude* noeudInclude)
{
    _orchestrateur->inclureFichier(noeudInclude->getPath(), _contextGenCode);
}

