#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieIdentifiant.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudUnRefVariable.h"
#include "Compilateur/AST/Noeuds/Operande/NoeudLitteral.h"
#include "Compilateur/AST/Noeuds/Tableau/NoeudLectureTableau.h" 
#include "Compilateur/Lexer/TokenType.h"
#include <vector>

StrategieIdentifiant::StrategieIdentifiant(IConstructeurArbre* constructeurArbre)
    : _constructeurArbre(constructeurArbre) {}

StrategieIdentifiant::~StrategieIdentifiant()
{}

INoeud* StrategieIdentifiant::construire(std::vector<Token>& equation) {
    bool isTableau = false;
    size_t indexCrochet = 0;
    std::vector<Token> EquationIndex;

    // Utilisation d'une technique de contexte, regarder en avant pour voir si il y a un []
    // Parcourir l'équation pour trouver le token crochet ouvrant
    for (size_t i = 0; i < equation.size(); i++) {
        if (equation[i].type == TOKEN_CROCHET_OUVERT) {
            indexCrochet = i;
            isTableau = true;
            break;
        }
    }

    if (isTableau) {
        // remplir le tableau de l'équation de l'index du crochet ouvrant jusqu'au crochet fermant correspondant
        for (size_t i = indexCrochet; i < equation.size(); i++) {
            if (equation[i].type == TOKEN_CROCHET_FERME) {
                break;
            }
            if (i != static_cast<size_t>(indexCrochet)) { // ne pas ajouter le crochet ouvrant
                EquationIndex.push_back(equation[i]);
            }
        }

        INoeud* indexEquation = _constructeurArbre->construire(EquationIndex);
        return _constructeurArbre->allouer<NoeudLectureTableau>(indexEquation, equation[0]);
    }
  
    return _constructeurArbre->allouer<NoeudLitteral>(equation[0]);
}