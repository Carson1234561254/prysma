#ifndef D6C839EF_D128_402F_BE44_4C7AB3B74703
#define D6C839EF_D128_402F_BE44_4C7AB3B74703
#include "Compilateur/Parsing/Interfaces/IParser.h"
#include "Compilateur/Parsing/ParserBase.h"
#include <memory>

class ParserAppelFonction : public IParser, ParserBase
{

public:

    ParserAppelFonction();
    ~ParserAppelFonction();
    std::shared_ptr<INoeud> parser(std::vector<Token>& tokens, int& index, ConstructeurArbreInstruction* constructeurArbreInstruction) override;

};

#endif /* D6C839EF_D128_402F_BE44_4C7AB3B74703 */
