#include "Compilateur/AST/Noeuds/Operande/NoeudVariable.h"
#include <stdexcept>
#include <utility>
#include <llvm/IR/Instructions.h> 


NoeudVariable::NoeudVariable(const std::string& nomVariable)
    : _nomVariable(nomVariable)
{
}

NoeudVariable::~NoeudVariable()
{
}

void NoeudVariable::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}
