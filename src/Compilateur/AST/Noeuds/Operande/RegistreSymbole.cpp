#include "Compilateur/AST/Noeuds/Operande/RegistreSymbole.h"
#include <stdexcept>

void RegistreSymbole::enregistrer(
    char symbole, 
    std::function<std::shared_ptr<INoeud>()> fournisseur) {
    _carteSymboles[symbole] = fournisseur;
}

std::shared_ptr<INoeud> RegistreSymbole::recupererNoeud(char symbole) {
    auto iterator = _carteSymboles.find(symbole);
    if (iterator == _carteSymboles.end()) {
        throw std::invalid_argument(std::string("Symbole inconnu: ") + symbole);
    }
    return iterator->second();
}

bool RegistreSymbole::estOperateur(char symbole) const {
    return _carteSymboles.count(symbole) > 0;
}

std::set<char> RegistreSymbole::obtenirSymboles() const {
    std::set<char> symboles;
    for (const auto& pair : _carteSymboles) {
        symboles.insert(pair.first);
    }
    return symboles;
}
