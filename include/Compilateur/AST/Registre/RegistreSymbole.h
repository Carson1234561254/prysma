#pragma once

#include "Compilateur/AST/Registre/RegistreGeneric.h"
#include "Compilateur/AST/Registre/Interfaces/IRegistreSymbole.h"
#include <functional>
#include <memory>


class IExpression;

class RegistreSymbole : public RegistreGeneric<TokenType,std::function<std::shared_ptr<IExpression>(Token)>>,
                        public IRegistreSymbole {
public:
    RegistreSymbole() = default;
    virtual ~RegistreSymbole() = default;

  
    void enregistrer(
        TokenType symbole, 
        std::function<std::shared_ptr<IExpression>(Token)> fournisseur) override {
        RegistreGeneric::enregistrer(symbole, std::move(fournisseur));
    }


    std::shared_ptr<IExpression> recupererNoeud(Token token) override {
        std::function<std::shared_ptr<IExpression>(Token)> fournisseur = RegistreGeneric::recuperer(token.type);
        return fournisseur(token);
    }

  
    [[nodiscard]] bool estOperateur(TokenType symbole) const override {
        return existe(symbole);
    }

    [[nodiscard]] std::set<TokenType> obtenirSymboles() const override {
        return obtenirCles();
    }

protected:
   
    [[nodiscard]] std::string genererMessageErreur(TokenType cle) const  {
        return RegistreGeneric::genererMessageErreur(cle);
    }
};