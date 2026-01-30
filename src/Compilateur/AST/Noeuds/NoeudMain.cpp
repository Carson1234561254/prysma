#include "Compilateur/AST/Noeuds/NoeudMain.h"

NoeudMain::NoeudMain()
{
}

NoeudMain::~NoeudMain()
{
}

void NoeudMain::ajouterInstruction(const std::vector<std::shared_ptr<INoeud>>& enfantsParam)
{
    for (const auto& enfant : enfantsParam) {
        enfants.push_back(enfant);
    }
}

llvm::Value* NoeudMain::genCode()
{
    llvm::Value* resultat = nullptr;
    for (const auto& enfant : enfants) {
        resultat = enfant->genCode();
    }
    return resultat;
}
