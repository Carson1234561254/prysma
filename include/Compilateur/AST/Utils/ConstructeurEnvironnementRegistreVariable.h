#ifndef A1014A88_A2B2_4637_B4CD_3709FCBE042F
#define A1014A88_A2B2_4637_B4CD_3709FCBE042F

#include "Compilateur/AST/Registre/ContextGenCode.h"
#include "Compilateur/AST/Utils/IConstructeurEnvironnementRegistre.h"

class ConstructeurEnvironnementRegistreVariable : public IConstructeurEnvironnementRegistre
{
private:
    ContextGenCode* _contextGenCode;

public:
    ConstructeurEnvironnementRegistreVariable(ContextGenCode* _contextGenCode);
    ~ConstructeurEnvironnementRegistreVariable();

    void remplir() override;
};

#endif /* A1014A88_A2B2_4637_B4CD_3709FCBE042F */
