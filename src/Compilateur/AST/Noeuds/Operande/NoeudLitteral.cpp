#include "Compilateur/AST/Noeuds/Operande/NoeudLitteral.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"

NoeudLitteral::NoeudLitteral(const Token& token)
    : _token(token)
{
}

void NoeudLitteral::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}
