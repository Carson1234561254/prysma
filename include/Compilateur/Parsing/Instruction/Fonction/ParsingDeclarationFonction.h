#ifndef DD335087_6EDE_4036_872C_8BD586E2625B
#define DD335087_6EDE_4036_872C_8BD586E2625B

#include "Compilateur/AST/Registre/RegistreFonction.h"
#include "Compilateur/LLVM/LLVMBackend.h"
#include "Compilateur/Parsing/Interfaces/IParser.h"
#include "Compilateur/Parsing/ParserBase.h"
#include <memory>

class RegistreVariable;

class ParsingDeclarationFonction : public IParser, public ParserBase
{
private:
    std::shared_ptr<LLVMBackend> _backend; 
    std::shared_ptr<RegistreFonction> _registreFonction;
    std::shared_ptr<RegistreVariable> _registreVariable;
    TokenType _typeFonction; 

public:
    ParsingDeclarationFonction(std::shared_ptr<LLVMBackend> backend, std::shared_ptr<RegistreFonction> registreFonction, std::shared_ptr<RegistreVariable> registreVariable, TokenType typeFonction);
    ~ParsingDeclarationFonction();

    std::shared_ptr<INoeud> parser(std::vector<Token>& tokens, int& index, ConstructeurArbreInstruction* constructeurArbreInstruction) override;
};

#endif /* DD335087_6EDE_4036_872C_8BD586E2625B */
