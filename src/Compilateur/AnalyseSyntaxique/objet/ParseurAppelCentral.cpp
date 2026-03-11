#ifndef PARSEUR_APPELCENTRAL_CPP
#define PARSEUR_APPELCENTRAL_CPP

#include "Compilateur/objet/ParseurAppelCentral.h"

#include "Compilateur/Fonction/ParseurAppelFonction.h"
#include "Compilateur/objet/ParseurAppelObjet.h"

ParseurAppelCentral::ParseurAppelCentral(ContextParseur& contextParseur)
    : _contextParseur(contextParseur)
{}

ParseurAppelCentral::~ParseurAppelCentral()
{}

INoeud* ParseurAppelCentral::parser(std::vector<Token>& tokens, int& index)
{
    const int indexCourant = index;
    const bool appelObjet = indexCourant + 2 < static_cast<int>(tokens.size())
        && tokens[static_cast<size_t>(indexCourant)].type == TOKEN_CALL
        && tokens[static_cast<size_t>(indexCourant + 1)].type == TOKEN_IDENTIFIANT
        && tokens[static_cast<size_t>(indexCourant + 2)].type == TOKEN_POINT;

    if (appelObjet) {
        ParseurAppelObjet parseurObjet(_contextParseur);
        return parseurObjet.parser(tokens, index);
    }

    ParseurAppelFonction parseurFonction(_contextParseur);
    return parseurFonction.parser(tokens, index);
}

#endif /* PARSEUR_APPELCENTRAL_CPP */