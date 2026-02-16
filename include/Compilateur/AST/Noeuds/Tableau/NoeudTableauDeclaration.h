#ifndef C29032C6_0D6D_4B1D_BA1A_B674F01BF0FD
#define C29032C6_0D6D_4B1D_BA1A_B674F01BF0FD

#include "Compilateur/AST/Noeuds/NoeudInstruction.h"
#include "Compilateur/Lexer/TokenType.h"

class NoeudTableauDeclaration : public NoeudInstruction 
{
private: 
    std::string _nomVariable; 
    int _taille; 
    TokenType _tokenType;

public:
    NoeudTableauDeclaration(std::string nomVariable, int taille, TokenType tokenType);
    ~NoeudTableauDeclaration();
    
    void accept(IVisiteur* visiteur) override;
    
    std::string getNomVariable() const { return _nomVariable; }
    int getTaille() const { return _taille; }
    TokenType getTokenType() const { return _tokenType; }
};


#endif /* C29032C6_0D6D_4B1D_BA1A_B674F01BF0FD */
