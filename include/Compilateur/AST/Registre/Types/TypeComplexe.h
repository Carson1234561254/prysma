#ifndef C747FE4B_9A53_40BA_A4BE_19C00508C8C4
#define C747FE4B_9A53_40BA_A4BE_19C00508C8C4

#include "IType.h"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>
#include <string>

class TypeComplexe : public IType {
private:
    std::string nomClasse;
public:
    TypeComplexe(const std::string& nom);
    
    llvm::Type* genererTypeLLVM(llvm::LLVMContext& context) override;
    
    bool estFlottant() const override;
    bool estBooleen() const override;
    bool estChaine() const override;
    bool estTableau() const override;
    bool estComplexe() const override;
    
    llvm::Type* getVTableType(llvm::LLVMContext& context) override;
    
    std::string getNomClasse() const;
};

#endif /* C747FE4B_9A53_40BA_A4BE_19C00508C8C4 */
