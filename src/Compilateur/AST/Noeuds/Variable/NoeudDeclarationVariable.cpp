#include "Compilateur/AST/Noeuds/Variable/NoeudDeclarationVariable.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>
#include <memory>
#include <utility>

NoeudDeclarationVariable::NoeudDeclarationVariable(const std::string& nom, std::shared_ptr<IType> type, std::shared_ptr<INoeud> expression)
    : _nom(nom), _type(std::move(type)), _expression(std::move(expression))
{
}

NoeudDeclarationVariable::~NoeudDeclarationVariable()
{
}

void NoeudDeclarationVariable::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}
