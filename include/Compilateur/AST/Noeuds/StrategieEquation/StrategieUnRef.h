#ifndef EDC0875A_32FA_455F_B295_054142B09404
#define EDC0875A_32FA_455F_B295_054142B09404

#include "Compilateur/AST/Noeuds/StrategieEquation/IStrategieEquation.h"
#include "llvm/Support/Allocator.h"

class StrategieUnRef : public IStrategieEquation {
private:
    llvm::BumpPtrAllocator& _arena;
public:
    StrategieUnRef(llvm::BumpPtrAllocator& arena);
    ~StrategieUnRef() override = default;
    INoeud* construire(std::vector<Token>& equation) override;
};


#endif /* EDC0875A_32FA_455F_B295_054142B09404 */
