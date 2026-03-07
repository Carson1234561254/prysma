#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/AST_Genere.h"

void VisiteurGeneralGraphViz::visiter([[maybe_unused]]NoeudArgFonction* noeudArgFonction) 
{
    _dernierId = _sortieGrapheVisuel.ajouterNoeud("Argument: " + noeudArgFonction->getNom());
}