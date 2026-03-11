#ifndef PARSEUR_APPELOBJET_CPP
#define PARSEUR_APPELOBJET_CPP

#include "Compilateur/objet/ParseurAppelObjet.h"
#include "Compilateur/AST/AST_Genere.h"


ParseurAppelObjet::ParseurAppelObjet(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurAppelObjet::~ParseurAppelObjet()
{}

INoeud* ParseurAppelObjet::parser(std::vector<Token>& tokens, int& index)
{
  const bool appelCommeInstruction = index == 0 || tokens[static_cast<size_t>(index - 1)].type != TOKEN_EGAL;

  consommer(tokens, index, TOKEN_CALL, "Erreur: 'call' attendu");
  Token nomObjet = consommer(tokens, index, TOKEN_IDENTIFIANT, "Erreur: identifiant d'objet attendu");
  consommer(tokens, index, TOKEN_POINT, "Erreur: '.' attendu après le nom de l'objet");
  Token nomMethode = consommer(tokens, index, TOKEN_IDENTIFIANT, "Erreur: identifiant de méthode attendu");
  consommer(tokens, index, TOKEN_PAREN_OUVERTE, "Erreur: '(' attendue");

  IInstruction* noeudAppel = _contextParseur.constructeurArbreEquation->allouer<NoeudAppelObjet>(nomObjet, nomMethode);

  consommerEnfantCorps(tokens, index, noeudAppel, _contextParseur.constructeurArbreEquation, TOKEN_PAREN_FERMEE);

  consommer(tokens, index, TOKEN_PAREN_FERMEE, "Erreur: ')' attendue");

  if (appelCommeInstruction && index < static_cast<int>(tokens.size()) && tokens[static_cast<size_t>(index)].type == TOKEN_POINT_VIRGULE) {
      consommer(tokens, index, TOKEN_POINT_VIRGULE, "Erreur : ';' attendu à la fin de l'appel d'objet");
  }

  return noeudAppel;
}

#endif /* PARSEUR_APPELOBJET_CPP */




