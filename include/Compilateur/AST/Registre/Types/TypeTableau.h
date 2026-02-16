#ifndef B05A551C_2519_458F_BB1D_8E5EF8DB9B83
#define B05A551C_2519_458F_BB1D_8E5EF8DB9B83

#include "IType.h"
#include <memory>

class TypeTableau : public IType {
private:
    std::shared_ptr<IType> _typeEnfant;
    int _taille;

public:
    TypeTableau(std::shared_ptr<IType> typeEnfant, int taille);
    ~TypeTableau() override = default;

    llvm::Type* genererTypeLLVM(llvm::LLVMContext& context) override;

    std::shared_ptr<IType> getTypeEnfant() const { return _typeEnfant; }
    int getTaille() const { return _taille; }
};

#endif /* B05A551C_2519_458F_BB1D_8E5EF8DB9B83 */
