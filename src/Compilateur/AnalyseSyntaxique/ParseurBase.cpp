#include "Compilateur/AnalyseSyntaxique/ParseurBase.h"
#include "Compilateur/Lexer/TokenType.h"
#include "Compilateur/GestionnaireErreur.h"

Token ParseurBase::consommer(std::vector<Token>& tokens, int& index, TokenType typeAttendu, const std::string& messageErreur)
{
    if (index < 0 || index >= static_cast<int>(tokens.size()) || tokens[static_cast<size_t>(index)].type != typeAttendu) {
        if (index >= 0 && index < static_cast<int>(tokens.size())) {
            throw ErreurCompilation(messageErreur, tokens[static_cast<size_t>(index)].ligne, tokens[static_cast<size_t>(index)].colonne);
        }
        throw ErreurCompilation(messageErreur, 1, 1);
    }
    return tokens[static_cast<size_t>(index++)];
}

void ParseurBase::consommerEnfantCorps(std::vector<Token>& tokens, int& index , IInstruction* parent, IConstructeurArbre* constructeurArbre,TokenType fin)
{
    while(index < static_cast<int>(tokens.size()) && tokens[static_cast<size_t>(index)].type != fin)
    {
        // Ignorer les virgules entre les éléments
        if(tokens[static_cast<size_t>(index)].type == TOKEN_VIRGULE)
        {
            index++;
            continue;
        }
        
        INoeud* enfant = constructeurArbre->construire(tokens, index);
        parent->ajouterInstruction(enfant);
    }
}
