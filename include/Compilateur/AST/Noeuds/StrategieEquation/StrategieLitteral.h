#ifndef C0F69272_DFFB_405E_A894_789467563D41
#define C0F69272_DFFB_405E_A894_789467563D41

#include "Compilateur/AST/Noeuds/StrategieEquation/IStrategieEquation.h"
#include "llvm/Support/Allocator.h"

class StrategieLitteral : public IStrategieEquation {
private:
    llvm::BumpPtrAllocator& _arena;
public:
    StrategieLitteral(llvm::BumpPtrAllocator& arena);
    ~StrategieLitteral() override = default;
    INoeud* construire(std::vector<Token>& equation) override;
};


#endif /* C0F69272_DFFB_405E_A894_789467563D41 */
