#ifndef PARSEUR_INSTRUCTION_CPP
#define PARSEUR_INSTRUCTION_CPP

#include "Compilateur/Equation/ParseurInstruction.h"


ParseurInstruction::ParseurInstruction(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurInstruction::~ParseurInstruction()
{}

INoeud* ParseurInstruction::parser(std::vector<Token>& tokens, int& index)
{
  // TODO: Implémenter le parseur pour Instruction
  (void)tokens;
  (void)index;
  return nullptr;
}

#endif /* PARSEUR_INSTRUCTION_CPP */




