#pragma once

#include "Compilateur/AST/Registre/RegistreGeneric.h"
#include "Compilateur/AnalyseSyntaxique/Interfaces/IParseur.h"
#include <memory>
#include <set>
#include "Compilateur/Lexer/TokenType.h"

class RegistreInstruction : public RegistreGeneric<TokenType, std::shared_ptr<IParseur>> {
public:
    RegistreInstruction() = default;
    virtual ~RegistreInstruction() = default;


    void enregistrer(TokenType typeToken, std::shared_ptr<IParseur> fournisseur) {
        RegistreGeneric::enregistrer(typeToken, std::move(fournisseur));
    }
  
    std::shared_ptr<IParseur> recuperer(TokenType typeToken) {
        return RegistreGeneric::recuperer(typeToken);
    }


    [[nodiscard]] bool estInstruction(TokenType typeToken) const {
        return existe(typeToken);
    }

    [[nodiscard]] std::set<TokenType> obtenirTypesTokens() const {
        return obtenirCles();
    }
};
