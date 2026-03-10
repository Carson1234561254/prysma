#ifndef PARSEUR_OPERATION_CPP
#define PARSEUR_OPERATION_CPP

#include "Compilateur/Math/ParseurOperation.h"


ParseurOperation::ParseurOperation(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurOperation::~ParseurOperation()
{}

INoeud* ParseurOperation::parser(std::vector<Token>& tokens, int& index)
{
  // TODO: Implémenter le parseur pour Operation
  (void)tokens;
  (void)index;
  return nullptr;
}

#endif /* PARSEUR_OPERATION_CPP */




