#include "Compilateur/Parsing/Instruction/Variable/ParseurVariable.h"
#include "Compilateur/Parsing/Instruction/Variable/ParseurDeclaration.h"
#include "Compilateur/Parsing/Instruction/Variable/ParseurAffectation.h"
#include "Compilateur/Lexer/TokenType.h"
#include "Compilateur/AST/Registre/RegistreVariable.h"
#include <llvm-18/llvm/IR/Instructions.h>
#include <memory>
#include <utility>


ParseurVariable::ParseurVariable(std::shared_ptr<LLVMBackend> backend, std::shared_ptr<RegistreVariable> registreVariable)
    : _backend(std::move(backend)), _registreVariable(std::move(registreVariable))
{
}

ParseurVariable::~ParseurVariable()
{
}

// Exemple: var float teste = 34+435+4;
std::shared_ptr<INoeud> ParseurVariable::parser(std::vector<Token>& tokens, int& index, std::shared_ptr<ConstructeurArbreInstruction> constructeurArbreInstruction)
{
    consommer(tokens, index, TOKEN_VAR, "Erreur : 'var' attendu");
    
    if (index < static_cast<int>(tokens.size()) && tokens[index].type == TOKEN_TYPE_FLOAT) {
        ParseurDeclaration parseurDeclaration(_backend, _registreVariable, TOKEN_TYPE_FLOAT);
        return parseurDeclaration.parser(tokens, index, constructeurArbreInstruction);
    }

    ParseurAffectation parseurAffectation(_backend, _registreVariable, TOKEN_TYPE_FLOAT);
    return parseurAffectation.parser(tokens, index, constructeurArbreInstruction);
}