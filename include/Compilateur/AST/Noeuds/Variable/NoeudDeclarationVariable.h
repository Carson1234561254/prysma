#ifndef B18E8AB9_A311_4560_9FDD_5E2D3FAC0F14
#define B18E8AB9_A311_4560_9FDD_5E2D3FAC0F14

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Lexer/TokenType.h"
#include <llvm/IR/Instructions.h>
#include <memory>
#include "Compilateur/Visiteur/AmisVisiteurs.h"

class NoeudDeclarationVariable : public INoeud
{
    LISTE_DES_AMIS_VISITEURS
private:
    std::string _nom;
    llvm::Value* _arraySize;
    std::shared_ptr<INoeud> _expression;
    TokenType _token; 

    llvm::AllocaInst* allocation();
    llvm::AllocaInst* initialisation(llvm::AllocaInst* allocaInst, llvm::Value* valeur);

public:
    NoeudDeclarationVariable(const std::string& nom, std::shared_ptr<INoeud> expression, TokenType token);
    ~NoeudDeclarationVariable();

    void accept(IVisiteur* visiteur) override;
};

#endif /* B18E8AB9_A311_4560_9FDD_5E2D3FAC0F14 */
