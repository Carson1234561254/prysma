#ifndef FD83BD8A_F363_49DA_B571_00377736E3B4
#define FD83BD8A_F363_49DA_B571_00377736E3B4
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/AST/Registre/Pile/RegistreVariable.h"
#include "Compilateur/AST/Registre/RegistreArgument.h"
#include <memory>
class NoeudArgPassFonction : public INoeud
{
private: 
    std::shared_ptr<RegistreVariable> _registreVariable;
    Token _tokenVariable; 
    std::shared_ptr<RegistreArgument> _registreArgument;

public:
    NoeudArgPassFonction(std::shared_ptr<RegistreVariable> registreVariable, const Token& token, std::shared_ptr<RegistreArgument> registreArgument);
    ~NoeudArgPassFonction();

    void accept(IVisiteur* visiteur) override;
    llvm::Value* genCode() override;
};

#endif /* FD83BD8A_F363_49DA_B571_00377736E3B4 */
