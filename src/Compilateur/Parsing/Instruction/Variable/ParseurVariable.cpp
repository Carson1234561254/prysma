#include "Compilateur/Parsing/Instruction/Variable/ParseurVariable.h"
#include <memory>


std::shared_ptr<NoeudVariable> ParseurVariable::parser(std::vector<Token>& tokens, int& index)
{
    while(index)
    {

    }

    // Construire le noeud avec les bon paramètres. 
    std::string nom = "teste";
    llvm::Type* type = nullptr;
    llvm::AllocaInst* variableAssigner = nullptr; 
    llvm::Value* valeur = nullptr; 
    
    std::shared_ptr<NoeudVariable> noeudVariable = std::make_shared<NoeudVariable>(nom, type, variableAssigner, valeur); 

    return noeudVariable; 
}