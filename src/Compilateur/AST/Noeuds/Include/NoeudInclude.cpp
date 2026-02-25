#include "Compilateur/AST/Noeuds/Include/NoeudInclude.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"

NoeudInclude::NoeudInclude(const std::string& path) : _path(path) {}

NoeudInclude::~NoeudInclude()
{}

void NoeudInclude::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}
