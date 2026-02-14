#include "Compilateur/AST/Noeuds/NoeudScope.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"

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
