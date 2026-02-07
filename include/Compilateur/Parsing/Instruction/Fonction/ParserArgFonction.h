#ifndef BDC43121_B136_4DA5_86FF_DCA70967CB37
#define BDC43121_B136_4DA5_86FF_DCA70967CB37
#include "Compilateur/Lexer/Lexer.h"
#include "Compilateur/Parsing/Interfaces/IParser.h"
#include "Compilateur/Parsing/ParserBase.h"

class ParserArgFonction : public IParser, public ParserBase
{
    
public: 

    ParserArgFonction();
    ~ParserArgFonction();
    
    std::shared_ptr<INoeud> parser(std::vector<Token>& tokens, int& index, ConstructeurArbreInstruction* constructeurArbreInstruction) override;

};

#endif /* BDC43121_B136_4DA5_86FF_DCA70967CB37 */
