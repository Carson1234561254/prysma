#include "Compilateur/AST/Noeuds/Condition/NoeudIf.h"
#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include <llvm-18/llvm/IR/Value.h>

void VisiteurGeneralGraphViz::visiter(NoeudIf* noeudIf) 
{
    int idNoeud = _sortieGrapheVisuel.ajouterNoeud("If");

    noeudIf->getNoeudCondition()->accept(this);
    _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);

    noeudIf->getNoeudBlocIf()->accept(this);
    _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);

    if (noeudIf->getNoeudBlocElse()) {
        noeudIf->getNoeudBlocElse()->accept(this);
        _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);
    }
    _dernierId = idNoeud;
}
