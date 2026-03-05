#ifndef D2455535_F4FD_481C_AC4B_151349533737
#define D2455535_F4FD_481C_AC4B_151349533737

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Lexer/Lexer.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"


class NoeudNew : public INoeud
{
private:
    Token _nomType; 

public:
    NoeudNew(Token nomType);
    ~NoeudNew();
    
    void accept(IVisiteur* visiteur) override;
    
    [[nodiscard]] Token getNomType() const { return _nomType; }
};

#endif /* D2455535_F4FD_481C_AC4B_151349533737 */
