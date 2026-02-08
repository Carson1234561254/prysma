#include "Compilateur/AST/Noeuds/Fonction/NoeudRetour.h"
#include <llvm-18/llvm/IR/Instructions.h>
#include <utility>

NoeudRetour::NoeudRetour(std::shared_ptr<INoeud> valeurRetour)
    : _valeurRetour(std::move(valeurRetour))
{
}

 // Implémentation sera géré par le parent 
void NoeudRetour::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}

