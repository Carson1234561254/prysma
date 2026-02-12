#ifndef B7984297_5521_450F_A453_2594C7FDFC7A
#define B7984297_5521_450F_A453_2594C7FDFC7A

#include "Compilateur/AST/Noeuds/NoeudInstruction.h"
#include "Compilateur/Visiteur/AmisVisiteurs.h"
#include <memory>

class INoeud;

class NoeudIf : public NoeudInstruction
{
    LISTE_DES_AMIS_VISITEURS
private: 
    std::shared_ptr<INoeud> noeudCondition;
    std::shared_ptr<INoeud> noeudBlocIf;
    std::shared_ptr<INoeud> noeudBlocElse;
    std::shared_ptr<INoeud> noeudBlocEndif;

public: 
    NoeudIf();
    NoeudIf(std::shared_ptr<INoeud>&& condition, std::shared_ptr<INoeud>&& blocIf, std::shared_ptr<INoeud>&& blocElse, std::shared_ptr<INoeud>&& blocEndif);
    ~NoeudIf();
    
    void accept(IVisiteur* visiteur) override;
};

#endif /* B7984297_5521_450F_A453_2594C7FDFC7A */
