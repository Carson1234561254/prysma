#ifndef D8229B93_7089_41D9_9BA2_4433A4DF8D65
#define D8229B93_7089_41D9_9BA2_4433A4DF8D65

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Lexer/Lexer.h"



class NoeudNegation : public INoeud {
private:
    INoeud* operande;
    Token operateur;

public:
    explicit NoeudNegation(const Token& p_operateur, INoeud* p_expr)
        : operande(p_expr), operateur(p_operateur) {}

    void accept(IVisiteur* visiteur) override;

    INoeud* getOperande() const { return operande; }
    const Token& getOperateur() const { return operateur; }
};


#endif /* D8229B93_7089_41D9_9BA2_4433A4DF8D65 */
