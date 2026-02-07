#include "Compilateur/AST/Noeuds/NoeudScope.h"

NoeudScope::NoeudScope()
{
}

NoeudScope::~NoeudScope()
{
}

void NoeudScope::accept(IVisiteur* visiteur)
{
    visiteur->visiter(this);
}

llvm::Value* NoeudScope::genCode()
{
    llvm::Value* resultat = nullptr;
    for (const auto& enfant : enfants) {
        resultat = enfant->genCode();
    }
    return resultat;
}
