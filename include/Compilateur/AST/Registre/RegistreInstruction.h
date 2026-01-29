#pragma once

#include "Compilateur/AST/Noeuds/Interfaces/IInstruction.h"
#include "Compilateur/Lexer/TokenType.h"
#include <map>
#include <memory>
#include <set>
#include <functional>

class RegistreInstruction {
private:
    std::map<TokenType, std::function<std::shared_ptr<IInstruction>()>> _instructions;

public:
    RegistreInstruction() = default;
    virtual ~RegistreInstruction() = default;

    void enregistrer(
        TokenType typeToken,
        std::function<std::shared_ptr<IInstruction>()> fournisseur
    );

    std::shared_ptr<IInstruction> recuperer(TokenType typeToken);

    bool estInstruction(TokenType typeToken) const;

    std::set<TokenType> obtenirTypesTokens() const;
};
