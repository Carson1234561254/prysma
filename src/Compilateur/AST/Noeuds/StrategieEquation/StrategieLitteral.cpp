#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieLitteral.h"
#include "Compilateur/AST/AST_Genere.h"

StrategieLitteral::StrategieLitteral(llvm::BumpPtrAllocator& arena) : _arena(arena) {}

INoeud* StrategieLitteral::construire(std::vector<Token>& equation) {
    return new (_arena.Allocate(sizeof(NoeudLitteral), alignof(NoeudLitteral))) NoeudLitteral(equation[0]);
}
