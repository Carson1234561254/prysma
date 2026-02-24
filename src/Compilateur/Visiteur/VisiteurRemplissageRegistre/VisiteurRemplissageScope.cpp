#include "Compilateur/AST/Noeuds/NoeudScope.h"
#include "Compilateur/Visiteur/VisiteurRemplissageRegistre/VisiteurRemplissageRegistre.h"


void VisiteurRemplissageRegistre::visiter(NoeudScope* noeudScope)
{
    VisiteurBaseGenerale::visiter(noeudScope); 
}