#ifndef E5CE13D3_6823_4DDE_BB20_5311A0E477B6
#define E5CE13D3_6823_4DDE_BB20_5311A0E477B6
#include "Compilateur/AST/Registre/ContextGenCode.h"
#include "Compilateur/Visiteur/VisiteurBaseGenerale.h"

class VisiteurRemplissageRegistre : public VisiteurBaseGenerale
{
private:
    ContextGenCode* _contextGenCode;

public:
    VisiteurRemplissageRegistre(ContextGenCode* contextGenCode);
    virtual ~VisiteurRemplissageRegistre();
};

#endif /* E5CE13D3_6823_4DDE_BB20_5311A0E477B6 */
