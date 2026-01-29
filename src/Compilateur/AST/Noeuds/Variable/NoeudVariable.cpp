#include "Compilateur/AST/Noeuds/Variable/NoeudVariable.h"

#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/IR/Value.h>

NoeudVariable::NoeudVariable(const std::string& nom, llvm::Type* type, llvm::AllocaInst* variableAssigner,llvm::Value* valeur)
{
    _nom = nom; 
    _type = type; 
    _variableAssigner = variableAssigner;
    _valeur = valeur;
}

NoeudVariable::~NoeudVariable()
{

}

llvm::Value* NoeudVariable::genCode()
{
    // Signifie qu'aucune variable n'est à assignée 
    if(_variableAssigner == nullptr)
    {
        
    }

    llvm::AllocaInst* allocaInst = allocation();
    initialisation(allocaInst);

    return nullptr; 
}

llvm::AllocaInst* NoeudVariable::allocation()
{
      return _backend->getBuilder().CreateAlloca(_type, _ArraySize, _nom);
}

void NoeudVariable::assignation(llvm::AllocaInst* allocaInst)
{
    // Assigner une valeur à une variable existante (A = B)
    if(_valeur != nullptr && allocaInst != nullptr)
    {
        _backend->getBuilder().CreateStore(_valeur, allocaInst);
    }
}

llvm::AllocaInst* NoeudVariable::initialisation(llvm::AllocaInst* allocaInst)
{
      _backend->getBuilder().CreateStore(_valeur, allocaInst);
      return allocaInst; 
}   
