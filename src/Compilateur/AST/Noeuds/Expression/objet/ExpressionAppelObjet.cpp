#ifndef EXPRESSION_APPELOBJET_CPP
#define EXPRESSION_APPELOBJET_CPP

#include "Compilateur/objet/ExpressionAppelObjet.h"
#include "Compilateur/objet/ParseurAppelObjet.h"

ExpressionAppelObjet::ExpressionAppelObjet(ContexteExpression& contexteExpression)
    : _contexteExpression(contexteExpression)
{}

ExpressionAppelObjet::~ExpressionAppelObjet()
{}
// Exemple : call objet.methode() ou call objet.methode(arg int64 param1,arg int64 param2)
INoeud* ExpressionAppelObjet::construire(std::vector<Token>& equation)
{
    ParseurAppelObjet parseurAppel(*_contexteExpression.contextParseur);
    int indexZero = 0;
    return parseurAppel.parser(equation, indexZero);
}

#endif /* EXPRESSION_APPELOBJET_CPP */