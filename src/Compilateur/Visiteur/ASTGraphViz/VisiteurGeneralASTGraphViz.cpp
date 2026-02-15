#include "Compilateur/GrapheVisuel/SortieGrapheVisuelTexte.h"
#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/Noeuds/Operande/NoeudLitteral.h"


VisiteurGeneralGraphViz::VisiteurGeneralGraphViz(SortieGrapheVisuelTexte sortieGrapheVisuel) : _sortieGrapheVisuel(std::move(sortieGrapheVisuel)), _dernierId(0)
{}

VisiteurGeneralGraphViz::~VisiteurGeneralGraphViz()
{}

void VisiteurGeneralGraphViz::generer()
{
    _sortieGrapheVisuel.generer();
}

void VisiteurGeneralGraphViz::visiter(NoeudLitteral* noeudLitteral)
{
    _dernierId = _sortieGrapheVisuel.ajouterNoeud("Litteral: " + noeudLitteral->getToken().value);
}

