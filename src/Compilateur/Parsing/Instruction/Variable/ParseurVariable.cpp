#include "Compilateur/Parsing/Instruction/Variable/ParseurVariable.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudDeclaration.h"
#include "Compilateur/Lexer/TokenType.h"
#include "Compilateur/Builder/Equation/FloatEquationBuilder.h"
#include "Compilateur/Parsing/Equation/ParseurEquation.h"
#include <cstddef>
#include <llvm-18/llvm/IR/Instructions.h>
#include <memory>
#include <utility>


ParseurVariable::ParseurVariable(std::shared_ptr<LLVMBackend> backend)
{
   _backend = std::move(backend);
}

ParseurVariable::~ParseurVariable()
{
}

// Exemple: var float teste = 34+435+4;
std::shared_ptr<INoeud> ParseurVariable::parser(std::vector<Token>& tokens, int& index, std::shared_ptr<ConstructeurArbreInstruction> constructeurArbreInstruction)
{
    consommer(tokens, index, TOKEN_VAR, "Erreur : 'var' attendu");
    consommer(tokens, index, TOKEN_TYPE_FLOAT, "Erreur : 'float' attendu après 'var'");
    
    Token nomToken = consommer(tokens, index, TOKEN_IDENTIFIANT, "Erreur : nom de variable attendu");
    std::string nomVariable = nomToken.value;
    
    consommer(tokens, index, TOKEN_EGAL, "Erreur : '=' attendu après le nom de variable");
    
    ParseurEquation parseurEquation(_backend);
    std::shared_ptr<INoeud> expression = parseurEquation.parser(tokens, index, constructeurArbreInstruction);

    shared_ptr<NoeudDeclaration> noeudDeclaration = std::make_shared<NoeudDeclaration>(
        _backend, 
        nomVariable, 
        _backend->getBuilder().getFloatTy(), 
        expression->genCode() 
    );

    return noeudDeclaration;
}