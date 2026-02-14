#include "Compilateur/AST/Noeuds/Variable/NoeudRefVariable.h"
#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"

void VisiteurGeneralGraphViz::visiter(NoeudRefVariable* noeudRefVariable) 
{
    _dernierId = _sortieGrapheVisuel.ajouterNoeud("Ref: " + noeudRefVariable->getNomVariable());
}
