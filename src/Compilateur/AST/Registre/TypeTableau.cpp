#include "Compilateur/AST/Registre/Types/TypeTableau.h"
#include <llvm/IR/DerivedTypes.h>
#include <utility>

TypeTableau::TypeTableau(std::shared_ptr<IType> typeEnfant, int taille)
    : _typeEnfant(std::move(typeEnfant)), _taille(taille)
{
}

llvm::Type* TypeTableau::genererTypeLLVM(llvm::LLVMContext& context)
{
    llvm::Type* typeElement = _typeEnfant->genererTypeLLVM(context);
    return llvm::ArrayType::get(typeElement, static_cast<uint64_t>(_taille));
}
