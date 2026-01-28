#pragma once

#include "Compilateur/AST/Noeuds/Interfaces/IExpression.h"
#include <functional>
#include <llvm-18/llvm/IR/Value.h>
#include <memory>

/**
 * @class Operation
 * @brief Représente une opération binaire entre deux expressions
 * Implémente le pattern Composite
 */
class Operation : public IExpression {
private:
    std::shared_ptr<INoeud> _droite;
    std::shared_ptr<INoeud> _gauche;
    std::function<llvm::Value*(llvm::Value*, llvm::Value*)> _operateur;

public:
    /**
     * @brief Constructeur
     * @param operateur Fonction binaire pour effectuer l'opération
     */
    explicit Operation(
        const std::function<llvm::Value*(llvm::Value*, llvm::Value*)>& operateur
    );
    /**
     * @brief Ajoute deux expressions comme opérandes
     * @param gauche Opérande gauche
     * @param droite Opérande droit
     * @return Référence au nœud courant
     */
    std::shared_ptr<IExpression> ajouterExpression(
        std::shared_ptr<INoeud> gauche, 
        std::shared_ptr<INoeud> droite
    ) override;
    
    /**
     * @brief Résout l'opération
     * @return Résultat de l'application de l'opérateur
     */
    llvm::Value* genCode() override;
};
