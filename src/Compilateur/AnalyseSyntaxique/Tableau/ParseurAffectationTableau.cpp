#ifndef PARSEUR_AFFECTATIONTABLEAU_CPP
#define PARSEUR_AFFECTATIONTABLEAU_CPP

#include "Compilateur/Tableau/ParseurAffectationTableau.h"


ParseurAffectationTableau::ParseurAffectationTableau(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurAffectationTableau::~ParseurAffectationTableau()
{}

INoeud* ParseurAffectationTableau::parser(std::vector<Token>& tokens, int& index)
{
  // TODO: Implémenter le parseur pour AffectationTableau
  (void)tokens;
  (void)index;
  return nullptr;
}

#endif /* PARSEUR_AFFECTATIONTABLEAU_CPP */




