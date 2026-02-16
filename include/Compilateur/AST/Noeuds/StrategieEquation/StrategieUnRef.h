#ifndef EDC0875A_32FA_455F_B295_054142B09404
#define EDC0875A_32FA_455F_B295_054142B09404

#include "Compilateur/AST/Noeuds/StrategieEquation/IStrategieEquation.h"

class StrategieUnRef : public IStrategieEquation {
public:
    StrategieUnRef() = default;
    ~StrategieUnRef() override = default;
    std::shared_ptr<INoeud> construire(std::vector<Token>& equation, IConstructeurArbre* constructeurEquation, IConstructeurArbre* instructionBuilder) override;
};


#endif /* EDC0875A_32FA_455F_B295_054142B09404 */
