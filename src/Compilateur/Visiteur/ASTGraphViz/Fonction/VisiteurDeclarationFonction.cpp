#include "Compilateur/LLVM/GenerateurFonction.h"
#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudDeclarationFonction.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudArgFonction.h"
#include "Compilateur/AST/Noeuds/NoeudScope.h"

#include <memory>

void VisiteurGeneralGraphViz::visiter(NoeudDeclarationFonction* noeudDeclarationFonction) 
{
    int idNoeud = _sortieGrapheVisuel.ajouterNoeud("Declaration Fonction: " + noeudDeclarationFonction->getNom());

    // Visiter les arguments
    for (NoeudArgFonction* arg : noeudDeclarationFonction->getArguments()) {
        arg->accept(this);
        _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);
    }

    // Visiter le corps
    NoeudScope* corps = noeudDeclarationFonction->getCorps();
    if (corps != nullptr) {
        corps->accept(this);
        _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);
    }

    _dernierId = idNoeud;
}