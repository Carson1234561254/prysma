#include "Compilateur/AST/Noeuds/Variable/NoeudDeclarationVariable.h"
#include "Compilateur/Lexer/TokenType.h"

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>
#include <memory>
#include <utility>

NoeudDeclarationVariable::NoeudDeclarationVariable(const std::string& nom, std::shared_ptr<INoeud> expression, TokenType token)
    : _nom(nom), _arraySize(nullptr), _expression(std::move(expression)), _tokenType(token)
{
}

NoeudDeclarationVariable::~NoeudDeclarationVariable()
{
}

void NoeudDeclarationVariable::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}
