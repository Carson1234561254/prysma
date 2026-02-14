#include "Compilateur/AST/Noeuds/Boucle/NoeudWhile.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"

NoeudWhile::NoeudWhile()
    = default;

NoeudWhile::NoeudWhile(std::shared_ptr<INoeud>&& condition, std::shared_ptr<INoeud>&& blocWhile, std::shared_ptr<INoeud>&& blocEndWhile)
    : noeudCondition(std::move(condition)), noeudBlocWhile(std::move(blocWhile)), noeudBlocFinWhile(std::move(blocEndWhile))
{
}

NoeudWhile::~NoeudWhile()
{
}

void NoeudWhile::accept(IVisiteur* visiteur) 
{
    visiteur->visiter(this);
}
