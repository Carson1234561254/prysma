#include "Compilateur/GrapheVisuel/SortieGrapheVisuelTexte.h"
#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/Noeuds/Operande/NoeudLitteral.h"


VisiteurGeneralGraphViz::VisiteurGeneralGraphViz(SortieGrapheVisuelTexte sortieGrapheVisuel) : _sortieGrapheVisuel(std::move(sortieGrapheVisuel))
{}

VisiteurGeneralGraphViz::~VisiteurGeneralGraphViz()
{}

void VisiteurGeneralGraphViz::visiter(NoeudLitteral* noeudLitteral)
{

}

