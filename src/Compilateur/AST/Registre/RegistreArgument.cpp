#include "Compilateur/AST/Registre/RegistreArgument.h"

RegistreArgument::RegistreArgument()
{
    _vecArg = std::make_shared<std::vector<llvm::Value*>>();
}

void RegistreArgument::ajouter(llvm::Value* arg)
{
    _vecArg->push_back(arg);
}

std::shared_ptr<std::vector<llvm::Value*>> RegistreArgument::recuperer()
{
    return _vecArg;
}

void RegistreArgument::vider()
{
    _vecArg->clear();
}



