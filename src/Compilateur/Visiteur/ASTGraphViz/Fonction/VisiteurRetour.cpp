#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/AST_Genere.h"

void VisiteurGeneralGraphViz::visiter(NoeudRetour* noeudReturn)
{
    int idNoeud = _sortieGrapheVisuel.ajouterNoeud("Retour");

    noeudReturn->getValeurRetour()->accept(this);
    _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);
    _dernierId = idNoeud;
}