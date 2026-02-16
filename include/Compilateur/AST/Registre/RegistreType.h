#ifndef DD335087_6EDE_4036_872C_8BD586E26252
#define DD335087_6EDE_4036_872C_8BD586E26252

#include "Interfaces/IRegistreType.h"
#include "Compilateur/Lexer/TokenType.h"
#include <llvm/IR/Type.h>

class RegistreType : public IRegistreType
{

public:
    RegistreType() = default;
    virtual ~RegistreType() = default;

protected:
    
    [[nodiscard]] std::string genererMessageErreur(const TokenType& cle) const override {
        return RegistreGeneric::genererMessageErreur(cle);
    }
};

#endif /* DD335087_6EDE_4036_872C_8BD586E26252 */
