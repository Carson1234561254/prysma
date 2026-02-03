#ifndef A2837407_B466_49AE_8A29_4BFC0A5D0461
#define A2837407_B466_49AE_8A29_4BFC0A5D0461

#include "Compilateur/AST/Noeuds/Instruction.h"
#include "Compilateur/Lexer/TokenType.h"
#include <string>
#include <memory>

class LLVMBackend;

class NoeudDeclarationFonction : public Instruction
{
private:
    std::shared_ptr<LLVMBackend> _backend;
    std::string _nom;
    TokenType _typeRetourToken;

public:
    NoeudDeclarationFonction(std::shared_ptr<LLVMBackend> backend, std::string nom, TokenType typeRetour);
    
    ~NoeudDeclarationFonction() = default;

    llvm::Value* genCode() override;

    std::string getNom() const { return _nom; }
    TokenType getTypeRetourToken() const { return _typeRetourToken; }
};

#endif /* A2837407_B466_49AE_8A29_4BFC0A5D0461 */
