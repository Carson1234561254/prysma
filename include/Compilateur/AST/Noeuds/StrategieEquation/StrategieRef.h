#ifndef A4D04758_FBF2_453B_91A4_1C143BCB5638
#define A4D04758_FBF2_453B_91A4_1C143BCB5638

#include "Compilateur/AST/Noeuds/StrategieEquation/IStrategieEquation.h"

class StrategieRef : public IStrategieEquation {
public:
    StrategieRef() = default;
    ~StrategieRef() override = default;
    std::shared_ptr<INoeud> construire(std::vector<Token>& equation, IConstructeurArbre* constructeurEquation, IConstructeurArbre* instructionBuilder) override;
};


#endif /* A4D04758_FBF2_453B_91A4_1C143BCB5638 */
