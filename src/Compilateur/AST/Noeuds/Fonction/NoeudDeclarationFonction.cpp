#include "Compilateur/AST/Noeuds/Fonction/NoeudDeclarationFonction.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudArgFonction.h"
#include "Compilateur/AST/Noeuds/NoeudScope.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"
#include <utility>

NoeudDeclarationFonction::NoeudDeclarationFonction(
    std::string nom,
    IType* typeRetour,
    const std::vector<NoeudArgFonction*>& arguments,
    NoeudScope* corps
)
    : _nom(std::move(nom)),
      _typeRetour(typeRetour),
      _arguments(arguments),
      _corps(corps)
{
}

void NoeudDeclarationFonction::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}
