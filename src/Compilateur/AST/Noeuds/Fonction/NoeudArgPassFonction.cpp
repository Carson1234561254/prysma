#include "Compilateur/AST/Noeuds/Fonction/NoeudArgPassFonction.h"
#include <llvm-18/llvm/IR/Value.h>
#include "Compilateur/AST/Registre/RegistreArgument.h"


NoeudArgPassFonction::NoeudArgPassFonction(std::shared_ptr<RegistreVariable> registreVariable,const Token& tokenVariable, std::shared_ptr<RegistreArgument> registreArgument)
{
    _registreVariable = std::move(registreVariable);
    _tokenVariable = tokenVariable;
    _registreArgument = std::move(registreArgument);
}

NoeudArgPassFonction::~NoeudArgPassFonction()
{}

void NoeudArgPassFonction::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}

  
llvm::Value* NoeudArgPassFonction::genCode() 
{
    llvm::Value* valeurVariable =  _registreVariable->recupererVariables(_tokenVariable);
    _registreArgument->ajouter(valeurVariable);
    return valeurVariable;
};