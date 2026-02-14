#ifndef C281C518_FA13_4CFD_B295_5CB41352DB27
#define C281C518_FA13_4CFD_B295_5CB41352DB27

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include <string>
class NoeudRefVariable : public INoeud
{
private:
    std::string _nomVariable;

public:
    explicit NoeudRefVariable(const std::string& nomVariable);
    ~NoeudRefVariable();

    void accept(IVisiteur* visiteur) override;

    const std::string& getNomVariable() const { return _nomVariable; }
};

#endif /* C281C518_FA13_4CFD_B295_5CB41352DB27 */
