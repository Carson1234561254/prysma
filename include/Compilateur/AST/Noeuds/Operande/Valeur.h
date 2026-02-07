#pragma once

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"

class Valeur : public INoeud {
private:
    llvm::Value* _valeur;

public:

    explicit Valeur(llvm::Value* valeur);

    void accept(IVisiteur* visiteur) override;
};
