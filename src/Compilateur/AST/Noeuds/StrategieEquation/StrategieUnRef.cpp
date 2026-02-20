#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieUnRef.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudUnRefVariable.h"
#include "Compilateur/Lexer/TokenType.h"
#include <stdexcept>

StrategieUnRef::StrategieUnRef(llvm::BumpPtrAllocator& arena) : _arena(arena) {}

INoeud* StrategieUnRef::construire(std::vector<Token>& equation) {
    if (equation.size() < 2 || equation[1].type != TOKEN_IDENTIFIANT) {
        throw std::runtime_error("Erreur: 'unref' doit être suivi d'un identifiant");
    }
    return new (_arena.Allocate(sizeof(NoeudUnRefVariable), alignof(NoeudUnRefVariable))) NoeudUnRefVariable(equation[1].value);
}
