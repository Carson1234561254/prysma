#ifndef D6E0732E_B57B_4C82_98E0_1A1FE461A1DC
#define D6E0732E_B57B_4C82_98E0_1A1FE461A1DC
#include "Compilateur/Parsing/Interfaces/IParser.h"
#include "Compilateur/Parsing/ParserBase.h"
class PaserArgPassFonction : public IParser, public ParserBase
{
private:

public:

    PaserArgPassFonction();
    ~PaserArgPassFonction();
    std::shared_ptr<INoeud> parser(std::vector<Token>& tokens, int& index, ConstructeurArbreInstruction* constructeurArbreInstruction) override;

};

#endif /* D6E0732E_B57B_4C82_98E0_1A1FE461A1DC */
