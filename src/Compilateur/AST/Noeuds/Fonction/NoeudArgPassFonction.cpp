#include "Compilateur/AST/Noeuds/Fonction/NoeudArgPassFonction.h"
#include <llvm-18/llvm/IR/Value.h>


NoeudArgPassFonction::NoeudArgPassFonction(const Token& tokenVariable)
{
    _tokenVariable = tokenVariable;
}

NoeudArgPassFonction::~NoeudArgPassFonction()
{}

void NoeudArgPassFonction::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}

