#ifndef A6143133_47EE_4E86_9715_0D00D76F1DE5
#define A6143133_47EE_4E86_9715_0D00D76F1DE5
#include "Compilateur/AST/Noeuds/NoeudInstruction.h"
#include "Compilateur/Lexer/Lexer.h"
class NoeudAppelFonction : public NoeudInstruction
{
private: 
    Token _nomFonction;

public:
    NoeudAppelFonction(Token nomFonction);
    ~NoeudAppelFonction();
    void accept(IVisiteur* visiteur) override;
    const Token& getNomFonction() const { return _nomFonction; }
};

#endif /* A6143133_47EE_4E86_9715_0D00D76F1DE5 */
