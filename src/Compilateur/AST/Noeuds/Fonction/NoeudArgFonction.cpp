#include "Compilateur/AST/Noeuds/Fonction/NoeudArgFonction.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"

NoeudArgFonction::NoeudArgFonction(std::shared_ptr<RegistreType> registreType, std::string nom, TokenType type)
{
    _registreType = std::move(registreType);
    _nom = std::move(nom);
    _type = type;
}

NoeudArgFonction::~NoeudArgFonction()
{
}

void NoeudArgFonction::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}

