#ifndef PARSEUR_ARGFONCTION_CPP
#define PARSEUR_ARGFONCTION_CPP

#include "Compilateur/Fonction/ParseurArgFonction.h"
#include "Compilateur/AST/AST_Genere.h"


ParseurArgFonction::ParseurArgFonction(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurArgFonction::~ParseurArgFonction()
{}

INoeud* ParseurArgFonction::parser(std::vector<Token>& tokens, int& index) 
{

  consommer(tokens,index,TOKEN_ARG,"Erreur: le token n'est pas 'arg' !");

  IType* type = _contextParseur.parseurType->parser(tokens, index);

  Token nom = consommer(tokens,index,TOKEN_IDENTIFIANT,"Erreur: ce n'est pas un identifiant!");

  return _contextParseur.constructeurArbreEquation->allouer<NoeudArgFonction>(type, nom.value);
}

#endif /* PARSEUR_ARGFONCTION_CPP */




