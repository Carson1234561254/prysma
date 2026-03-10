#ifndef PARSEUR_TABLEAUINITIALISATION_CPP
#define PARSEUR_TABLEAUINITIALISATION_CPP

#include "Compilateur/Tableau/ParseurTableauInitialisation.h"


ParseurTableauInitialisation::ParseurTableauInitialisation(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurTableauInitialisation::~ParseurTableauInitialisation()
{}

INoeud* ParseurTableauInitialisation::parser(std::vector<Token>& tokens, int& index)
{
  // TODO: Implémenter le parseur pour TableauInitialisation
  (void)tokens;
  (void)index;
  return nullptr;
}

#endif /* PARSEUR_TABLEAUINITIALISATION_CPP */




