#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/LLVM/GestionVariable.h"

void VisiteurGeneralGraphViz::visiter(NoeudUnRefVariable* noeudUnRefVariable) 
{
    _dernierId = _sortieGrapheVisuel.ajouterNoeud("UnRef: " + noeudUnRefVariable->getNomVariable());
}