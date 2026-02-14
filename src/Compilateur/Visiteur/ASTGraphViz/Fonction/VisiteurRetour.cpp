#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudRetour.h"

void VisiteurGeneralGraphViz::visiter(NoeudRetour* noeudReturn)
{
    int idNoeud = _sortieGrapheVisuel.ajouterNoeud("Retour");

    noeudReturn->getValeurRetour()->accept(this);
    _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);
    _dernierId = idNoeud;
}