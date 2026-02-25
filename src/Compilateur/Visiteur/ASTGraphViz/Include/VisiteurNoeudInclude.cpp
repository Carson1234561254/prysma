#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/Noeuds/Include/NoeudInclude.h"
#include <string>

void VisiteurGeneralGraphViz::visiter(NoeudInclude* noeudInclude)
{
    int idNoeud = _dernierId++;
    _sortieGrapheVisuel.ajouterNoeud(std::to_string(idNoeud) + "Include: " + noeudInclude->getPath());
}