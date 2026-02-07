#ifndef F529C0E5_B051_4DF3_9DB0_8987D960AAF6
#define F529C0E5_B051_4DF3_9DB0_8987D960AAF6

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Lexer/Lexer.h"
#include <llvm/IR/Instructions.h>
#include <memory>

class NoeudAffectationVariable : public INoeud
{
private:
    std::string _nom;
    std::shared_ptr<INoeud> _expression;
    Token _token; 

    void assignation(llvm::AllocaInst* allocaInst, llvm::Value* valeur);
    llvm::AllocaInst* recupererVariable();

public:
    NoeudAffectationVariable(const std::string& nom, std::shared_ptr<INoeud> expression, Token token);
    ~NoeudAffectationVariable();

    void accept(IVisiteur* visiteur) override;
};

#endif /* F529C0E5_B051_4DF3_9DB0_8987D960AAF6 */
