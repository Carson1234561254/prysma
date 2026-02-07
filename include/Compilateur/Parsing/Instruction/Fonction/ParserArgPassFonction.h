#ifndef D6E0732E_B57B_4C82_98E0_1A1FE461A1DC
#define D6E0732E_B57B_4C82_98E0_1A1FE461A1DC
#include "Compilateur/Parsing/Interfaces/IParser.h"
#include "Compilateur/Parsing/ParserBase.h"
#include <memory>
class ParserArgPassFonction : public IParser, public ParserBase
{

public:

    ParserArgPassFonction();
    ~ParserArgPassFonction();
    std::shared_ptr<INoeud> parser(std::vector<Token>& tokens, int& index, ConstructeurArbreInstruction* constructeurArbreInstruction) override;

};

#endif /* D6E0732E_B57B_4C82_98E0_1A1FE461A1DC */
