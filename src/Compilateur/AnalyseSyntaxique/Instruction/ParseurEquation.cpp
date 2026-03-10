#ifndef PARSEUR_EQUATION_CPP
#define PARSEUR_EQUATION_CPP

#include "Compilateur/Instruction/ParseurEquation.h"


ParseurEquation::ParseurEquation(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurEquation::~ParseurEquation()
{}

INoeud* ParseurEquation::parser(std::vector<Token>& tokens, int& index)
{

  INoeud* expression = _contextParseur.constructeurArbreEquation->construire(tokens, index);

  consommer(tokens, index, TOKEN_POINT_VIRGULE, "Erreur : ';' attendu à la fin de l'instruction");
  
  return expression;
}

#endif /* PARSEUR_EQUATION_CPP */




