#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"

void VisiteurGeneralGraphViz::visiter(NoeudRefVariable* noeudRefVariable) 
{
    _dernierId = _sortieGrapheVisuel.ajouterNoeud("Ref: " + noeudRefVariable->getNomVariable());
}
