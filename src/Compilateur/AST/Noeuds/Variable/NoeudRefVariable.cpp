#include "Compilateur/AST/Noeuds/Variable/NoeudRefVariable.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"

NoeudRefVariable::NoeudRefVariable(const std::string& nomVariable)
    : _nomVariable(nomVariable)
{
}

NoeudRefVariable::~NoeudRefVariable()
{
}

void NoeudRefVariable::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}
