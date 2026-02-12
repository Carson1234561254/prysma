#ifndef B7984297_5521_450F_A453_2594C7FDFC7A
#define B7984297_5521_450F_A453_2594C7FDFC7A

#include "Compilateur/AST/Noeuds/NoeudInstruction.h"
#include "Compilateur/Visiteur/AmisVisiteurs.h"
#include <memory>

class NoeudBlocIf;
class NoeudBlocElse;
class NoeudBlocEndif;

class NoeudIf : public NoeudInstruction
{
    LISTE_DES_AMIS_VISITEURS
private: 
    std::shared_ptr<NoeudBlocIf> noeudBlocIf;
    std::shared_ptr<NoeudBlocElse> noeudBlocElse;
    std::shared_ptr<NoeudBlocEndif> noeudBlocEndif;

public: 
    NoeudIf();
    NoeudIf(std::shared_ptr<NoeudBlocIf>&& blocIf, std::shared_ptr<NoeudBlocElse>&& blocElse, std::shared_ptr<NoeudBlocEndif>&& blocEndif);
    ~NoeudIf();
    
    void accept(IVisiteur* visiteur) override;
};

#endif /* B7984297_5521_450F_A453_2594C7FDFC7A */
