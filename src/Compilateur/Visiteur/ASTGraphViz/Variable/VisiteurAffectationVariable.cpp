#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/LLVM/GestionVariable.h"

void VisiteurGeneralGraphViz::visiter(NoeudAffectationVariable* noeudAffectationVariable)
{
    int idNoeud = _sortieGrapheVisuel.ajouterNoeud("Affectation: " + noeudAffectationVariable->getNom());

    noeudAffectationVariable->getExpression()->accept(this);
    _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);
    _dernierId = idNoeud;
}

