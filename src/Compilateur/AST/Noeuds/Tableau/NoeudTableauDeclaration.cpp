#include "Compilateur/AST/Noeuds/Tableau/NoeudTableauDeclaration.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"

NoeudTableauDeclaration::NoeudTableauDeclaration(std::string nomVariable, int taille, TokenType tokenType)
    : _nomVariable(std::move(nomVariable)), _taille(taille), _tokenType(tokenType)
{}

NoeudTableauDeclaration::~NoeudTableauDeclaration()
{}

void NoeudTableauDeclaration::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}