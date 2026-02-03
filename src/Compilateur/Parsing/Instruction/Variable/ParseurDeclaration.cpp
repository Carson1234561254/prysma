#include "Compilateur/Parsing/Instruction/Variable/ParseurDeclaration.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudDeclaration.h"
#include "Compilateur/Lexer/TokenType.h"
#include "Compilateur/Parsing/Equation/ParseurEquation.h"
#include "Compilateur/AST/Registre/RegistreVariable.h"
#include <memory>
#include <iostream> 

ParseurDeclaration::ParseurDeclaration(std::shared_ptr<LLVMBackend> backend, std::shared_ptr<RegistreVariable> registreVariable, TokenType typeVariable)
    : _backend(std::move(backend)), _registreVariable(std::move(registreVariable)), _typeVariable(typeVariable)
{
}

ParseurDeclaration::~ParseurDeclaration()
{
}

std::shared_ptr<INoeud> ParseurDeclaration::parser(std::vector<Token>& tokens, int& index, ConstructeurArbreInstruction* constructeurArbreInstruction)
{
    consommer(tokens,index,TOKEN_DEC,"Erreur : type attendu 'dec");
    consommer(tokens, index, _typeVariable, "Erreur : type attendu après 'dec'");
    
    Token nomToken = consommer(tokens, index, TOKEN_IDENTIFIANT, "Erreur : nom de variable attendu");
    std::string nomVariable = nomToken.value;
    
    consommer(tokens, index, TOKEN_EGAL, "Erreur : '=' attendu après le nom de variable");
    
    ParseurEquation parseurEquation(_backend, _typeVariable, _registreVariable);
    std::shared_ptr<INoeud> expression = parseurEquation.parser(tokens, index, constructeurArbreInstruction);

    return std::make_shared<NoeudDeclaration>(
        _backend,
        _registreVariable,
        nomVariable,
        llvm::Type::getFloatTy(_backend->getContext()), 
        expression
    );
}
