#include "Compilateur/AST/Noeuds/Fonction/NoeudAppelFonction.h"


NoeudAppelFonction::NoeudAppelFonction(Token nomFonction, std::shared_ptr<RegistreFonction> registreFonction)
{
    _nomFonction = std::move(nomFonction);
    _registreFonction = std::move(registreFonction);
}

NoeudAppelFonction::~NoeudAppelFonction()
{}

llvm::Value* NoeudAppelFonction::genCode()
{
    return nullptr;
}