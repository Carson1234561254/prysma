#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieRef.h"
#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/Lexer/TokenType.h"
#include <stdexcept>

StrategieRef::StrategieRef(llvm::BumpPtrAllocator& arena) : _arena(arena) {}

INoeud* StrategieRef::construire(std::vector<Token>& equation) {
    if (equation.size() < 2 || equation[1].type != TOKEN_IDENTIFIANT) {
        throw std::runtime_error("Erreur: 'ref' doit être suivi d'un identifiant");
    }
    return new (_arena.Allocate(sizeof(NoeudRefVariable), alignof(NoeudRefVariable))) NoeudRefVariable(equation[1].value);
}
