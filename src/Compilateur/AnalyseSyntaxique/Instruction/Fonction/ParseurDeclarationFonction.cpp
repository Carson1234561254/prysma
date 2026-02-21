#include "Compilateur/AST/Noeuds/Fonction/NoeudDeclarationFonction.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudArgFonction.h"
#include "Compilateur/AST/Noeuds/NoeudScope.h"
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/AST/Registre/Types/IType.h"
#include "Compilateur/Lexer/TokenType.h"
#include "Compilateur/Lexer/TokenCategories.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Fonction/ParseurDeclarationFonction.h"
#include "Compilateur/GestionnaireErreur.h"
#include <memory>
#include <utility>
#include <vector>

ParseurDeclarationFonction::ParseurDeclarationFonction(IConstructeurArbre* constructeurArbreInstruction, ParseurType* parseurType)
    : _constructeurArbreInstruction(constructeurArbreInstruction), _parseurType(parseurType)
{}

ParseurDeclarationFonction::~ParseurDeclarationFonction()
{
}

INoeud* ParseurDeclarationFonction::parser(std::vector<Token>& tokens, int& index)
{
    consommer(tokens, index, TOKEN_FONCTION, "Erreur: ce n'est pas le bon token ! 'fn'");

    Token tokenTypeRetour = tokens[index];
    IType* typeRetour = _parseurType->parser(tokens, index);
    
    Token tokenNomFonction = tokens[index];
    std::string nomFonction = tokenNomFonction.value;
    consommer(tokens, index, TOKEN_IDENTIFIANT, "Erreur: identifiant invalide, ce dois être un nom de fonction ");

    // Parser les arguments entre parenthèses
    consommer(tokens, index, TOKEN_PAREN_OUVERTE, "Erreur: ce n'est pas une parenthèse ouverte '('");
    
    std::vector<NoeudArgFonction*> arguments;
    while(index < (int)tokens.size() && tokens[index].type != TOKEN_PAREN_FERMEE)
    {
        if(tokens[index].type == TOKEN_VIRGULE)
        {
            index++;
            continue;
        }
        
        INoeud* enfant = _constructeurArbreInstruction->construire(tokens, index);
        NoeudArgFonction* argument = static_cast<NoeudArgFonction*>(enfant);
        arguments.push_back(argument);
    }

    consommer(tokens, index, TOKEN_PAREN_FERMEE, "Erreur: ce n'est pas une parenthèse fermée ')'");

    // Parser le corps dans un NoeudScope strict
    consommer(tokens, index, TOKEN_ACCOLADE_OUVERTE, "Erreur: ce n'est pas une accolade ouverte '{' ");

    NoeudScope* corps = _constructeurArbreInstruction->allouer<NoeudScope>();
    consommerEnfantCorps(tokens, index, corps, _constructeurArbreInstruction, TOKEN_ACCOLADE_FERMEE);

    consommer(tokens, index, TOKEN_ACCOLADE_FERMEE, "Erreur: ce n'est pas une accolade fermée '}'");

    NoeudDeclarationFonction* noeudFonction = 
        _constructeurArbreInstruction->allouer<NoeudDeclarationFonction>(nomFonction, typeRetour, arguments, corps);

    return noeudFonction; 
}