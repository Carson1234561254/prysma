#include "Compilateur/AST/Noeuds/New/NoeudNew.h"
#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"

void VisiteurGeneralGraphViz::visiter(NoeudNew* noeudNew)
{
    int idNoeud = _sortieGrapheVisuel.ajouterNoeud("New " + noeudNew->getNomType().value);
    _dernierId = idNoeud;
}