#ifndef EXPRESSION_APPELCENTRAL_CPP
#define EXPRESSION_APPELCENTRAL_CPP

#include "Compilateur/objet/ExpressionAppelCentral.h"

#include "Compilateur/Fonction/ParseurAppelFonction.h"
#include "Compilateur/objet/ParseurAppelObjet.h"

ExpressionAppelCentral::ExpressionAppelCentral(ContexteExpression& contexteExpression)
    : _contexteExpression(contexteExpression)
{}

ExpressionAppelCentral::~ExpressionAppelCentral()
{}

INoeud* ExpressionAppelCentral::construire(std::vector<Token>& equation)
{
    int indexZero = 0;

    const bool appelObjet = equation.size() >= 3
        && equation[0].type == TOKEN_CALL
        && equation[1].type == TOKEN_IDENTIFIANT
        && equation[2].type == TOKEN_POINT;

    if (appelObjet) {
        ParseurAppelObjet parseurAppel(*_contexteExpression.contextParseur);
        return parseurAppel.parser(equation, indexZero);
    }

    ParseurAppelFonction parseurAppel(*_contexteExpression.contextParseur);
    return parseurAppel.parser(equation, indexZero);
}

#endif /* EXPRESSION_APPELCENTRAL_CPP */