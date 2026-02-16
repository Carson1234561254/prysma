#include "Compilateur/AST/Registre/Types/TypeSimple.h"

TypeSimple::TypeSimple(llvm::Type* typeLLVM)
    : _typeLLVM(typeLLVM)
{
}

llvm::Type* TypeSimple::genererTypeLLVM([[maybe_unused]]llvm::LLVMContext& context)
{
    return _typeLLVM;
}
