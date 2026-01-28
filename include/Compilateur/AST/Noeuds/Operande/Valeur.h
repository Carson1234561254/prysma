#pragma once

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"

/**
 * @class Valeur
 * @brief Représente une valeur numérique constante
 */
class Valeur : public INoeud {
private:
    llvm::Value* _valeur;

public:
    /**
     * @brief Constructeur
     * @param valeur La valeur numérique
     */
    explicit Valeur(llvm::Value* valeur);
    
    /**
     * @brief Retourne la valeur stockée
     * @return La valeur
     */
    llvm::Value* genCode() override;
};
