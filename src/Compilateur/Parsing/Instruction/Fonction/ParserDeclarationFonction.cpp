#include "Compilateur/AST/ConstructeurArbreInstruction.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudDeclarationFonction.h"
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Lexer/TokenType.h"
#include "Compilateur/Parsing/Instruction/Fonction/ParsingDeclarationFonction.h"
#include <memory>
#include <vector>

ParsingDeclarationFonction::ParsingDeclarationFonction(std::shared_ptr<LLVMBackend> backend, std::shared_ptr<RegistreFonction> registreFonction, TokenType typeFonction)
    : _backend(std::move(backend)), _registreFonction(std::move(registreFonction)), _typeFonction(typeFonction)
{
}

ParsingDeclarationFonction::~ParsingDeclarationFonction()
{
}

std::shared_ptr<INoeud> ParsingDeclarationFonction::parser(std::vector<Token>& tokens, int& index, ConstructeurArbreInstruction* constructeurArbreInstruction)
{
    if (constructeurArbreInstruction == nullptr) {
        throw std::runtime_error("Erreur : ConstructeurArbreInstruction est null dans ParsingDeclarationFonction");
    }
    
    consommer(tokens, index, TOKEN_FONCTION, "Erreur: ce n'est pas le bon token ! 'def'");

    Token tokenTypeRetour = tokens[index];
    TokenType typeRetour = tokenTypeRetour.type;
    
    if (tokenTypeRetour.type == TOKEN_TYPE_INT || 
        tokenTypeRetour.type == TOKEN_TYPE_FLOAT || 
        tokenTypeRetour.type == TOKEN_TYPE_BOOL || 
        tokenTypeRetour.type == TOKEN_TYPE_VOID) {
        
        index++; 
    } else {
        throw std::runtime_error("Erreur: Type de retour attendu (int, float, void...)");
    }

    Token tokenNomFonction = tokens[index];
    std::string nomFonction = tokenNomFonction.value;
    consommer(tokens, index, TOKEN_IDENTIFIANT, "Erreur: identifiant invalide, ce dois être un nom de fonction ");

    std::shared_ptr<NoeudDeclarationFonction> parent = std::make_shared<NoeudDeclarationFonction>(_backend, nomFonction, typeRetour);

    // Manger les parenthèses ouvertes
    consommer(tokens, index, TOKEN_PAREN_OUVERTE, "Erreur: ce n'est pas une parenthèse ouverte '('");
    
    // Manger tout les paramètres
    while(index < (int)tokens.size() && tokens[index].type != TOKEN_PAREN_FERMEE)
    {
        index++;
    }

    consommer(tokens, index, TOKEN_PAREN_FERMEE, "Erreur: ce n'est pas une parenthèse fermée ')'");
    
    // Manger tout ce qui ce trouve dans les accolades
    consommer(tokens, index, TOKEN_ACCOLADE_OUVERTE, "Erreur: ce n'est pas une accolade ouverte '{' ");
    while(index < (int)tokens.size() && tokens[index].type != TOKEN_ACCOLADE_FERMEE)
    {
        std::shared_ptr<INoeud> enfant = constructeurArbreInstruction->construire(tokens, index);
        parent->ajouterInstruction(enfant);
    }
    
    consommer(tokens, index, TOKEN_ACCOLADE_FERMEE, "Erreur: ce n'est pas une accolade fermée '}'");

    return parent; 
}