#ifndef NoeudScope_
#define NoeudScope_

#include "Compilateur/AST/Noeuds/NoeudInstruction.h"
#include <llvm/IR/Value.h>
class NoeudScope : public NoeudInstruction
{
public: 

    NoeudScope();
    ~NoeudScope();
    void accept(IVisiteur* visiteur) override;
};

#endif /* NoeudScope_ */
