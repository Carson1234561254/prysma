#ifndef NOEUD_MAIN_H
#define NOEUD_MAIN_H

#include "Compilateur/AST/Noeuds/Instruction.h"
#include <llvm/IR/Value.h>

class NoeudScope : public Instruction
{
public: 

    NoeudScope();
    ~NoeudScope();
    void accept(IVisiteur* visiteur) override;
};

#endif /* NOEUD_MAIN_H */
