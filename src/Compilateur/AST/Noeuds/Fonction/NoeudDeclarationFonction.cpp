#include "Compilateur/AST/Noeuds/Fonction/NoeudDeclarationFonction.h"
#include "Compilateur/Lexer/TokenType.h"
#include <llvm-18/llvm/IR/BasicBlock.h>
#include <llvm-18/llvm/IR/DerivedTypes.h>
#include <llvm-18/llvm/IR/Function.h>
#include <utility>

NoeudDeclarationFonction::NoeudDeclarationFonction(std::string nom, TokenType typeRetour)
    : _nom(std::move(nom)), _typeRetourToken(typeRetour)
{
}

void NoeudDeclarationFonction::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}
