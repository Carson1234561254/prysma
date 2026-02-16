#ifndef BFF76A14_E9C5_4CB2_820B_010F0D0924A1
#define BFF76A14_E9C5_4CB2_820B_010F0D0924A1

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>

class IType {
public:
    virtual ~IType() = default;

    virtual llvm::Type* genererTypeLLVM(llvm::LLVMContext& context) = 0;
};


#endif /* BFF76A14_E9C5_4CB2_820B_010F0D0924A1 */
