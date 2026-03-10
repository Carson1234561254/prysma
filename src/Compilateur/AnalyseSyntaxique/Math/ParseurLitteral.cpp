#ifndef PARSEUR_LITTERAL_CPP
#define PARSEUR_LITTERAL_CPP

#include "Compilateur/Math/ParseurLitteral.h"


ParseurLitteral::ParseurLitteral(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurLitteral::~ParseurLitteral()
{}

INoeud* ParseurLitteral::parser(std::vector<Token>& tokens, int& index)
{
  // TODO: Implémenter le parseur pour Litteral
  (void)tokens;
  (void)index;
  return nullptr;
}

#endif /* PARSEUR_LITTERAL_CPP */




