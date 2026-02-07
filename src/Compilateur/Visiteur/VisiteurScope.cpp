#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"

void VisiteurGeneralGenCode::visiter(NoeudScope* NoeudScope)
{
     llvm::Value* resultat = nullptr;
    for (const auto& enfant : enfants) {
        enfant->accept(this);
    }
    this->_valeurTemporaire = resultat;
}