#ifndef PARSEUR_LECTURETABLEAU_CPP
#define PARSEUR_LECTURETABLEAU_CPP

#include "Compilateur/Tableau/ParseurLectureTableau.h"


ParseurLectureTableau::ParseurLectureTableau(ContextParseur& contextParseur) 
    : _contextParseur(contextParseur)
{}

ParseurLectureTableau::~ParseurLectureTableau()
{}

INoeud* ParseurLectureTableau::parser(std::vector<Token>& tokens, int& index)
{
  // TODO: Implémenter le parseur pour LectureTableau
  (void)tokens;
  (void)index;
  return nullptr;
}

#endif /* PARSEUR_LECTURETABLEAU_CPP */




