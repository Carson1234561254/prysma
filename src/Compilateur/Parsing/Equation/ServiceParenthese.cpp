#include "Compilateur/Parsing/Equation/ServiceParenthese.h"
#include <cctype>
#include <utility>

ServiceParenthese::ServiceParenthese(std::shared_ptr<RegistreSymbole> registreSymbole)
    : _registreSymbole(std::move(registreSymbole)) {}

std::string ServiceParenthese::enleverParenthesesEnglobantes(std::string equation) {
    // Trimmer les espaces
    equation.erase(0, equation.find_first_not_of(" \t\n\r"));
    equation.erase(equation.find_last_not_of(" \t\n\r") + 1);
    
    while (equation.length() >= 2 && 
           equation.front() == '(' && 
           equation.back() == ')' && 
           estEnglobante(equation)) {
        equation = equation.substr(1, equation.length() - 2);
        equation.erase(0, equation.find_first_not_of(" \t\n\r"));
        equation.erase(equation.find_last_not_of(" \t\n\r") + 1);
    }
    return equation;
}

bool ServiceParenthese::estEnglobante(const std::string& equation)  {
    int profondeur = 0;
    for (size_t i = 0; i < equation.length() - 1; i++) {
        char caractere = equation[i];
        profondeur += (caractere == '(' ? 1 : caractere == ')' ? -1 : 0);
        if (profondeur == 0) 
        {
            return false;
        }
    }
    return true;
}

int ServiceParenthese::trouverDernierAuNiveauZero(const std::string& equation, char operateur) {
    int profondeur = 0;
    for (int i = equation.length() - 1; i >= 0; i--) {
        char caractere = equation[i];
        profondeur += (caractere == ')' ? 1 : caractere == '(' ? -1 : 0);
        
        if (caractere == operateur && profondeur == 0 && !estSigneUnaire(equation, i)) {
            // Vérifier pour les opérateurs doubles (comme --)
            if (i > 0 && operateur == equation[i - 1]) {
                return i - 1;
            }
            return i;
        }
    }
    return -1;
}

bool ServiceParenthese::estSigneUnaire(const std::string& equation, int indice) const {
    if (indice == 0)
    {
        return true;
    }
    char precedent = equation[indice - 1];
    return _registreSymbole->estOperateur(precedent) || precedent == '(';
}
