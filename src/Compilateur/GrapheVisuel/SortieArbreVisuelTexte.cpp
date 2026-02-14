#include "Compilateur/GrapheVisuel/SortieGrapheVisuelTexte.h"
#include <fstream>
#include <stdexcept>

SortieGrapheVisuelTexte::SortieGrapheVisuelTexte(const std::string& cheminSortie)
    : _cheminSortie(cheminSortie), _compteurId(0) {}

void SortieGrapheVisuelTexte::ajouterNoeudValeur(int noeudId, const std::string& valeur) {
    _contenuGraphe << "    node" << noeudId 
                   << " [label=\"" << valeur << "\", shape=ellipse, style=filled, fillcolor=lightgreen];\n";
}

void SortieGrapheVisuelTexte::ajouterNoeudOperation(int noeudId, const std::string& operateur) {
    _contenuGraphe << "    node" << noeudId 
                   << " [label=\"" << operateur << "\", shape=ellipse, style=filled, fillcolor=lightgreen];\n";
}

void SortieGrapheVisuelTexte::ajouterArete(int parentId, int enfantId) {
    _contenuGraphe << "    node" << parentId << " -> node" << enfantId << ";\n";
}

void SortieGrapheVisuelTexte::generer() {
    std::ofstream fichier(_cheminSortie);
    
    if (!fichier.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier: " + _cheminSortie);
    }
    
    fichier << "digraph AST {\n";
    fichier << "    rankdir=TB;\n";
    fichier << "    node [fontname=\"Arial\"];\n";
    fichier << _contenuGraphe.str();
    fichier << "}\n";
    
    fichier.close();
}

int SortieGrapheVisuelTexte::obtenirNouvelId() {
    return _compteurId++;
}
