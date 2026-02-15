#ifndef D2F8710F_A58B_4559_B0C0_4D8569EB08B9
#define D2F8710F_A58B_4559_B0C0_4D8569EB08B9
#pragma once

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Lexer/Lexer.h"

class NoeudLitteral : public INoeud
{
private:
    Token _token;

public:
 
    explicit NoeudLitteral(const Token& token);

    ~NoeudLitteral() = default;

    void accept(IVisiteur* visiteur) override;

    const Token& getToken() const { return _token; }
};


#endif /* D2F8710F_A58B_4559_B0C0_4D8569EB08B9 */
