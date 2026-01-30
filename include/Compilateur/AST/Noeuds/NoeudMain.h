#ifndef NOEUD_MAIN_H
#define NOEUD_MAIN_H

#include "Compilateur/AST/Noeuds/Interfaces/IInstruction.h"
#include <vector>
#include <memory>


class NoeudMain : public IInstruction
{
private: 
    std::vector<std::shared_ptr<INoeud>> enfants; 
public: 

    NoeudMain();
    ~NoeudMain();

    void ajouterInstruction(const std::vector<std::shared_ptr<INoeud>>& enfantsParam) override;
    llvm::Value* genCode() override;
};

#endif /* NOEUD_MAIN_H */
