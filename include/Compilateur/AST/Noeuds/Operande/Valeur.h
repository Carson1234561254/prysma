#pragma once

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Visiteur/AmisVisiteurs.h"

class Valeur : public INoeud {
    LISTE_DES_AMIS_VISITEURS
private:
    llvm::Value* _valeur;

public:

    explicit Valeur(llvm::Value* valeur);

    void accept(IVisiteur* visiteur) override;
};
