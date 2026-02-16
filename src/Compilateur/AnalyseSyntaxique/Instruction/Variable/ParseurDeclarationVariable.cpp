#include "Compilateur/AnalyseSyntaxique/Instruction/Variable/ParseurDeclarationVariable.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudDeclarationVariable.h"
#include "Compilateur/Lexer/TokenType.h"
#include "Compilateur/AnalyseSyntaxique/Equation/ParseurEquation.h"
#include <memory>
#include <utility>

ParseurDeclarationVariable::ParseurDeclarationVariable(std::shared_ptr<ParseurType> parseurType)
    : _parseurType(std::move(parseurType))
{}

ParseurDeclarationVariable::~ParseurDeclarationVariable()
{
}

std::shared_ptr<INoeud> ParseurDeclarationVariable::parser(std::vector<Token>& tokens, int& index, IConstructeurArbre* constructeurArbre)
{
    consommer(tokens, index, TOKEN_DEC, "Erreur : type attendu 'dec");
    
    // Utiliser le ParseurType pour analyser le type (simple ou tableau)
    std::shared_ptr<IType> type = _parseurType->parser(tokens, index);
    
    Token nomToken = consommer(tokens, index, TOKEN_IDENTIFIANT, "Erreur : nom de variable attendu");
    std::string nomVariable = nomToken.value;
    
    consommer(tokens, index, TOKEN_EGAL, "Erreur : '=' attendu après le nom de variable");
    
    ParseurEquation parseurEquation{};
    std::shared_ptr<INoeud> expression = parseurEquation.parser(tokens, index, constructeurArbre);

    return std::make_shared<NoeudDeclarationVariable>(
        nomVariable,
        type,
        expression
    );
}
