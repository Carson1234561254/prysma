#ifndef PARSEUR_NEGATION_CPP
#define PARSEUR_NEGATION_CPP

#include "Compilateur/Math/ParseurNegation.h"


ParseurNegation::ParseurNegation(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurNegation::~ParseurNegation()
{}

INoeud* ParseurNegation::parser(std::vector<Token>& tokens, int& index)
{
  // TODO: Implémenter le parseur pour Negation
  (void)tokens;
  (void)index;
  return nullptr;
}

#endif /* PARSEUR_NEGATION_CPP */




