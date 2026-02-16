#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieAppelFonction.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Fonction/ParseurAppelFonction.h"

std::shared_ptr<INoeud> StrategieAppelFonction::construire(std::vector<Token>& equation, [[maybe_unused]] IConstructeurArbre* constructeurEquation, IConstructeurArbre* instructionBuilder) {
    ParseurAppelFonction parseurAppel;
    int indexZero = 0;
    std::vector<Token> equationAvecIndex = equation;
    return parseurAppel.parser(equationAvecIndex, indexZero, instructionBuilder);
}
