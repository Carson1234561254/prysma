#include "Compilateur/AST/Noeuds/New/NoeudNew.h"
#include <utility>

NoeudNew::NoeudNew(Token nomType) : _nomType(std::move(nomType))
{

}

NoeudNew::~NoeudNew()
{}

void NoeudNew::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}