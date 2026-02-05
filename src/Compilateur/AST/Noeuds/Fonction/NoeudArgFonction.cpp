#include "Compilateur/AST/Noeuds/Fonction/NoeudArgFonction.h"

NoeudArgFonction::NoeudArgFonction(std::shared_ptr<RegistreType> registreType, TokenType nom, TokenType type)
{
    _registreType = std::move(registreType);
    this->nom = nom;
    this->type = type;
}

NoeudArgFonction::~NoeudArgFonction()
{
}

llvm::Value* NoeudArgFonction::genCode()
{
    return nullptr;
}