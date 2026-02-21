#include "Compilateur/AST/Registre/Types/TypeSimple.h"

TypeSimple::TypeSimple(llvm::Type* typeLLVM)
    : _typeLLVM(typeLLVM)
{
}

llvm::Type* TypeSimple::genererTypeLLVM([[maybe_unused]]llvm::LLVMContext& context)
{
    return _typeLLVM;
}

bool TypeSimple::estFlottant() const
{
    return _typeLLVM->isFloatingPointTy();
}

bool TypeSimple::estBooleen() const
{
    return _typeLLVM->isIntegerTy(1);
}

bool TypeSimple::estChaine() const
{
    return _typeLLVM->isIntegerTy(8);
}
