#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudArgFonction.h"

void VisiteurGeneralGraphViz::visiter([[maybe_unused]]NoeudArgFonction* noeudArgFonction) 
{
    _dernierId = _sortieGrapheVisuel.ajouterNoeud("Argument: " + noeudArgFonction->getNom());
}