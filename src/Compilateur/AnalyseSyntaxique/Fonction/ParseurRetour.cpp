#ifndef PARSEUR_RETOUR_CPP
#define PARSEUR_RETOUR_CPP

#include "Compilateur/Fonction/ParseurRetour.h"
#include "Compilateur/AST/AST_Genere.h"


ParseurRetour::ParseurRetour(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurRetour::~ParseurRetour()
{}

INoeud* ParseurRetour::parser(std::vector<Token>& tokens, int& index)
{
  consommer(tokens, index, TOKEN_RETOUR, "Erreur: ce n'est pas le bon token ! 'return'");

  INoeud* valeurRetour = nullptr;

  if (index < static_cast<int>(tokens.size()) && tokens[static_cast<size_t>(index)].type != TOKEN_POINT_VIRGULE) {
      valeurRetour = _contextParseur.constructeurArbreEquation->construire(tokens, index);
  } else {
      consommer(tokens, index, TOKEN_POINT_VIRGULE, "Erreur: point-virgule attendu après return");
      return _contextParseur.constructeurArbreEquation->allouer<NoeudRetour>(valeurRetour);
  }
  
  consommer(tokens, index, TOKEN_POINT_VIRGULE, "Erreur : ';' attendu à la fin du return");

  return _contextParseur.constructeurArbreEquation->allouer<NoeudRetour>(valeurRetour);
}

#endif /* PARSEUR_RETOUR_CPP */




