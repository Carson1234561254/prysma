#ifndef C9126446_60DE_4831_AEE0_655AF47AE40D
#define C9126446_60DE_4831_AEE0_655AF47AE40D

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include <memory>
#include <string>
#include <llvm/IR/Value.h>
#include "Compilateur/Visiteur/AmisVisiteurs.h"

class NoeudVariable : public INoeud
{
    LISTE_DES_AMIS_VISITEURS
private:
    std::string _nomVariable;

public:

    NoeudVariable(const std::string& nomVariable);
    
    ~NoeudVariable();

    void accept(IVisiteur* visiteur) override;
};

#endif /* C9126446_60DE_4831_AEE0_655AF47AE40D */