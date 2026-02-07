#include "Compilateur/AST/Noeuds/Fonction/NoeudReturn.h"
#include <llvm-18/llvm/IR/Instructions.h>
#include <utility>

NoeudReturn::NoeudReturn(std::shared_ptr<INoeud> valeurRetour)
    : _valeurRetour(std::move(valeurRetour))
{
}

 // Implémentation sera géré par le parent 
void NoeudReturn::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}

