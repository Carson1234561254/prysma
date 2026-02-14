#include "Compilateur/AST/Noeuds/Operande/NoeudLitteral.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"

NoeudLitteral::NoeudLitteral(float valeur)
    : _valeur(valeur)
{
}

void NoeudLitteral::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}
