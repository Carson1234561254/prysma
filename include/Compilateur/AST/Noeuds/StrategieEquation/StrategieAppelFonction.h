#ifndef A9AC423F_7A3A_4A2D_9B2F_FE9EA55D9D7A
#define A9AC423F_7A3A_4A2D_9B2F_FE9EA55D9D7A

#include "Compilateur/AST/Noeuds/StrategieEquation/IStrategieEquation.h"

class StrategieAppelFonction : public IStrategieEquation {
public:
    StrategieAppelFonction() = default;
    ~StrategieAppelFonction() override = default;
    std::shared_ptr<INoeud> construire(std::vector<Token>& equation, IConstructeurArbre* constructeurEquation, IConstructeurArbre* instructionBuilder) override;
};


#endif /* A9AC423F_7A3A_4A2D_9B2F_FE9EA55D9D7A */
