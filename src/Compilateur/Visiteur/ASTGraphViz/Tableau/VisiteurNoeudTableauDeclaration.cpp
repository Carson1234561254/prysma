#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/Noeuds/Tableau/NoeudTableauDeclaration.h"

void VisiteurGeneralGraphViz::visiter(NoeudTableauDeclaration* noeudTableauDeclaration)
{
    int idNoeud = _sortieGrapheVisuel.ajouterNoeud("Tableau: " + noeudTableauDeclaration->getNomVariable() + "[" + std::to_string(noeudTableauDeclaration->getTaille()) + "]");
    _dernierId = idNoeud;
}
