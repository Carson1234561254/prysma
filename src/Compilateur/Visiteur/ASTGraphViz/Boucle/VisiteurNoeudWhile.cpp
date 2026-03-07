#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"

void VisiteurGeneralGraphViz::visiter(NoeudWhile* noeudWhile) 
{
    int idNoeud = _sortieGrapheVisuel.ajouterNoeud("While");

    noeudWhile->getNoeudCondition()->accept(this);
    _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);

    noeudWhile->getNoeudBlocWhile()->accept(this);
    _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);
    _dernierId = idNoeud;
}