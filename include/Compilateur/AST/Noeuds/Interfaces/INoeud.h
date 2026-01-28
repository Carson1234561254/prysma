#pragma once

/**
 * @interface INoeud
 * @brief Interface pour toute expression mathématique pouvant être résolue
 */
#include <llvm-18/llvm/IR/Value.h>
class INoeud {
public:
    virtual ~INoeud() = default;
    
    /**
     * @brief Résout l'expression et retourne le résultat
     * @return La valeur numérique de l'expression
     */
    virtual llvm::Value* genCode() = 0;
};
