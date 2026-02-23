#ifndef BC96CA6B_A1FB_4C4F_AE37_A5D105CD4D4E
#define BC96CA6B_A1FB_4C4F_AE37_A5D105CD4D4E

#include "Compilateur/AST/Registre/ContextGenCode.h"
#include "Compilateur/AST/Utils/IConstructeurEnvironnementRegistre.h"

class ConstructeurEnvironnementRegistreFonction : public IConstructeurEnvironnementRegistre
{
private:
    ContextGenCode* _contextGenCode; 

public:
    ConstructeurEnvironnementRegistreFonction(ContextGenCode* _contextGenCode);
    ~ConstructeurEnvironnementRegistreFonction();

    void remplir() override;
};

#endif /* BC96CA6B_A1FB_4C4F_AE37_A5D105CD4D4E */
