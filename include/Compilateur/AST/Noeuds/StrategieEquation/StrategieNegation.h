#ifndef EDA0D60F_5385_4A1B_A8D1_DCBEC90DEC63
#define EDA0D60F_5385_4A1B_A8D1_DCBEC90DEC63

#include "Compilateur/AST/Noeuds/StrategieEquation/IStrategieEquation.h"
#include "Compilateur/AST/Interfaces/IConstructeurArbre.h"
#include "llvm/Support/Allocator.h"

class StrategieNegation : public IStrategieEquation {
private:
    IConstructeurArbre* _constructeurArbre;
public:
    StrategieNegation(IConstructeurArbre* constructeurArbre);
    ~StrategieNegation() override = default;
    INoeud* construire(std::vector<Token>& equation) override;
};


#endif /* EDA0D60F_5385_4A1B_A8D1_DCBEC90DEC63 */
