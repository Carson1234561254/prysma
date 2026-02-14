#ifndef B7984297_5521_450F_A453_2594C7FDFC7A
#define B7984297_5521_450F_A453_2594C7FDFC7A

#include "Compilateur/AST/Noeuds/NoeudInstruction.h"
class NoeudIf : public NoeudInstruction
{
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

    const std::shared_ptr<INoeud>& getNoeudCondition() const { return noeudCondition; }
    const std::shared_ptr<INoeud>& getNoeudBlocIf() const { return noeudBlocIf; }
    const std::shared_ptr<INoeud>& getNoeudBlocElse() const { return noeudBlocElse; }
    const std::shared_ptr<INoeud>& getNoeudBlocEndif() const { return noeudBlocEndif; }
};

#endif /* B7984297_5521_450F_A453_2594C7FDFC7A */
