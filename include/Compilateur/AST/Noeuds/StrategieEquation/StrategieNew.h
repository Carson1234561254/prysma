#ifndef F7A07B49_4C94_45DD_B6B1_D6B1BFC52ACC
#define F7A07B49_4C94_45DD_B6B1_D6B1BFC52ACC

#include "Compilateur/AST/Noeuds/StrategieEquation/IStrategieEquation.h"
#include "Compilateur/AnalyseSyntaxique/ParseurBase.h"
#include "llvm/Support/Allocator.h"

class StrategieNew : public IStrategieEquation, public ParseurBase {
private:
    llvm::BumpPtrAllocator& _arena;
public:
    StrategieNew(llvm::BumpPtrAllocator& arena);
    ~StrategieNew() override = default;
    INoeud* construire(std::vector<Token>& equation) override;
};

#endif /* F7A07B49_4C94_45DD_B6B1_D6B1BFC52ACC */



