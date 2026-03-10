#ifndef PARSEUR_NEW_CPP
#define PARSEUR_NEW_CPP

#include "Compilateur/Instruction/ParseurNew.h"


ParseurNew::ParseurNew(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurNew::~ParseurNew()
{}

INoeud* ParseurNew::parser(std::vector<Token>& tokens, int& index)
{
  // TODO: Implémenter le parseur pour New
  (void)tokens;
  (void)index;
  return nullptr;
}

#endif /* PARSEUR_NEW_CPP */




