#ifndef DD937933_DED1_40A8_819C_360C96A8F41C
#define DD937933_DED1_40A8_819C_360C96A8F41C

#include "Compilateur/AST/Registre/RegistreGeneric.h"
#include "Compilateur/Lexer/TokenType.h"
#include <llvm/IR/Type.h>

class IRegistreType : public RegistreGeneric<TokenType, llvm::Type*> {
public:
    virtual ~IRegistreType() = default;
};

#endif /* DD937933_DED1_40A8_819C_360C96A8F41C */
