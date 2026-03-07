#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Lexer/TokenType.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Fonction/ParseurRetour.h"
#include <vector>

ParseurRetour::ParseurRetour(IConstructeurArbre* constructeurEquation)
    : _constructeurEquation(constructeurEquation)
{
}

ParseurRetour::~ParseurRetour()
{
}

INoeud* ParseurRetour::parser(std::vector<Token>& tokens, int& index)
{
    consommer(tokens, index, TOKEN_RETOUR, "Erreur: ce n'est pas le bon token ! 'return'");

    INoeud* valeurRetour = nullptr;

    if (index < static_cast<int>(tokens.size()) && tokens[static_cast<size_t>(index)].type != TOKEN_POINT_VIRGULE) {
        valeurRetour = _constructeurEquation->construire(tokens, index);
    } else {
        consommer(tokens, index, TOKEN_POINT_VIRGULE, "Erreur: point-virgule attendu après return");
        return _constructeurEquation->allouer<NoeudRetour>(valeurRetour);
    }
    
    consommer(tokens, index, TOKEN_POINT_VIRGULE, "Erreur : ';' attendu à la fin du return");

    return _constructeurEquation->allouer<NoeudRetour>(valeurRetour);
}
