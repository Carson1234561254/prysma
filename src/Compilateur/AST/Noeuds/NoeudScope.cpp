#include "Compilateur/AST/Noeuds/NoeudScope.h"

NoeudScope::NoeudScope()
{
}

NoeudScope::~NoeudScope()
{
}

void NoeudScope::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}
