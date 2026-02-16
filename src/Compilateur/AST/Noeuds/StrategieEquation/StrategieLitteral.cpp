#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieLitteral.h"
#include "Compilateur/AST/Noeuds/Operande/NoeudLitteral.h"

std::shared_ptr<INoeud> StrategieLitteral::construire(std::vector<Token>& equation, [[maybe_unused]] IConstructeurArbre* constructeurEquation, [[maybe_unused]] IConstructeurArbre* instructionBuilder) {
    return std::make_shared<NoeudLitteral>(equation[0]);
}
