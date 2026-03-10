#ifndef PARSEUR_DELETE_CPP
#define PARSEUR_DELETE_CPP

#include "Compilateur/Instruction/ParseurDelete.h"


ParseurDelete::ParseurDelete(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurDelete::~ParseurDelete()
{}

INoeud* ParseurDelete::parser(std::vector<Token>& tokens, int& index)
{
  // TODO: Implémenter le parseur pour Delete
  (void)tokens;
  (void)index;
  return nullptr;
}

#endif /* PARSEUR_DELETE_CPP */




