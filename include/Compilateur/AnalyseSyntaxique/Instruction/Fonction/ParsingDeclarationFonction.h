#ifndef DD335087_6EDE_4036_872C_8BD586E2625B
#define DD335087_6EDE_4036_872C_8BD586E2625B
#include "Compilateur/AnalyseSyntaxique/Interfaces/IParser.h"
#include "Compilateur/AnalyseSyntaxique/ParseurBase.h"
#include <memory>

class RegistreVariable;

class ParsingDeclarationFonction : public IParser, public ParseurBase
{

public:

    ParsingDeclarationFonction(TokenType token) {}
    ParsingDeclarationFonction();
    ~ParsingDeclarationFonction();

    std::shared_ptr<INoeud> parser(std::vector<Token>& tokens, int& index, ConstructeurArbreInstruction* constructeurArbreInstruction) override;
};

#endif /* DD335087_6EDE_4036_872C_8BD586E2625B */
