#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"

void VisiteurGeneralGraphViz::visiter(NoeudNew* noeudNew)
{
    int idNoeud = _sortieGrapheVisuel.ajouterNoeud("New " + noeudNew->getNomType().value);
    _dernierId = idNoeud;
}