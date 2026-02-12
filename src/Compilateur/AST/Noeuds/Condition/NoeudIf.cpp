#include "Compilateur/AST/Noeuds/Condition/NoeudIf.h"

NoeudIf::NoeudIf()
    = default;

NoeudIf::NoeudIf(std::shared_ptr<INoeud>&& condition, std::shared_ptr<INoeud>&& blocIf, std::shared_ptr<INoeud>&& blocElse, std::shared_ptr<INoeud>&& blocEndif)
    : noeudCondition(std::move(condition)), noeudBlocIf(std::move(blocIf)), noeudBlocElse(std::move(blocElse)), noeudBlocEndif(std::move(blocEndif))
{
}

NoeudIf::~NoeudIf()
 {}
 
 void NoeudIf::accept(IVisiteur* visiteur) 
 {
    visiteur->visiter(this);
 }