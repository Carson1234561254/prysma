#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieRef.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudRefVariable.h"
#include "Compilateur/Lexer/TokenType.h"
#include <stdexcept>

std::shared_ptr<INoeud> StrategieRef::construire(std::vector<Token>& equation, [[maybe_unused]] IConstructeurArbre* constructeurEquation, [[maybe_unused]] IConstructeurArbre* instructionBuilder) {
    if (equation.size() < 2 || equation[1].type != TOKEN_IDENTIFIANT) {
        throw std::runtime_error("Erreur: 'ref' doit être suivi d'un identifiant");
    }
    return std::make_shared<NoeudRefVariable>(equation[1].value);
}
