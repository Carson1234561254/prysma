#include "Compilateur/AST/Noeuds/Fonction/NoeudArgFonction.h"

NoeudArgFonction::NoeudArgFonction(std::shared_ptr<RegistreType> registreType, TokenType nom, TokenType type)
{
    _registreType = std::move(registreType);
    _nom = nom;
    _type = type;
}

NoeudArgFonction::~NoeudArgFonction()
{
}

llvm::Value* NoeudArgFonction::genCode()
{
    return nullptr;
}