#include "Compilateur/AST/Registre/Types/TypeSimple.h"
#include <llvm/IR/DerivedTypes.h>
#include <stdexcept>

TypeSimple::TypeSimple(llvm::Type* typeLLVM)
    : _typeLLVM(typeLLVM)
{
}

llvm::Type* TypeSimple::genererTypeLLVM(llvm::LLVMContext& context)
{
    if (&_typeLLVM->getContext() == &context) {
        return _typeLLVM;
    }

    switch (_typeLLVM->getTypeID()) {
        case llvm::Type::VoidTyID:   return llvm::Type::getVoidTy(context);
        case llvm::Type::FloatTyID:  return llvm::Type::getFloatTy(context);
        case llvm::Type::DoubleTyID: return llvm::Type::getDoubleTy(context);
        case llvm::Type::IntegerTyID:
            return llvm::IntegerType::get(context, _typeLLVM->getIntegerBitWidth());
        case llvm::Type::PointerTyID:
            return llvm::PointerType::get(context, _typeLLVM->getPointerAddressSpace());
        default:
            throw std::runtime_error("Type LLVM non supporté pour la migration entre contextes : "
                                      + std::to_string(_typeLLVM->getTypeID()));
    }
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
