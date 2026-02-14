#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/Noeuds/Equation/NoeudOperation.h"
#include "Compilateur/Lexer/TokenType.h"
#include <llvm/IR/Type.h>
#include <memory>

void VisiteurGeneralGraphViz::visiter(NoeudOperation* noeud)
{
    int idNoeud = _sortieGrapheVisuel.ajouterNoeud(to_string(noeud->getTypeOperation()));
    
    const std::shared_ptr<INoeud>& gauche = noeud->getGauche();
    if (gauche) {
        gauche->accept(this);
        _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);
    }

    const std::shared_ptr<INoeud>& droite = noeud->getDroite();
    if (droite) {
        droite->accept(this);
        _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);
    }
    _dernierId = idNoeud;
}

