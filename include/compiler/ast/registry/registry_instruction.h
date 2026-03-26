#pragma once

#include "compiler/ast/registry/registry_generic.h"
#include "compiler/parser/interfaces/i_parser.h"
#include "compiler/lexer/token_type.h"

class RegistryInstruction : public RegistryGeneric<TokenType, IParser*> {
public:
    RegistryInstruction() = default;
    ~RegistryInstruction() override = default;

    RegistryInstruction(const RegistryInstruction&) = delete;
    auto operator=(const RegistryInstruction&) -> RegistryInstruction& = delete;
    RegistryInstruction(RegistryInstruction&&) = delete;
    auto operator=(RegistryInstruction&&) -> RegistryInstruction& = delete;
};
