#ifndef A4D04758_FBF2_453B_91A4_1C143BCB5638
#define A4D04758_FBF2_453B_91A4_1C143BCB5638

#include "Compilateur/AST/Noeuds/StrategieEquation/IStrategieEquation.h"
#include "llvm/Support/Allocator.h"

class StrategieRef : public IStrategieEquation {
private:
    llvm::BumpPtrAllocator& _arena;
public:
    StrategieRef(llvm::BumpPtrAllocator& arena);
    ~StrategieRef() override = default;
    INoeud* construire(std::vector<Token>& equation) override;
};


#endif /* A4D04758_FBF2_453B_91A4_1C143BCB5638 */
