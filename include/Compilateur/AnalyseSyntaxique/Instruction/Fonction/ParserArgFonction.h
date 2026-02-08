#ifndef BDC43121_B136_4DA5_86FF_DCA70967CB37
#define BDC43121_B136_4DA5_86FF_DCA70967CB37
#include "Compilateur/Lexer/Lexer.h"
#include "Compilateur/AnalyseSyntaxique/Interfaces/IParser.h"
#include "Compilateur/AnalyseSyntaxique/ParseurBase.h"

class ParserArgFonction : public IParser, public ParseurBase
{
    
public: 

    ParserArgFonction();
    ~ParserArgFonction();
    
    std::shared_ptr<INoeud> parser(std::vector<Token>& tokens, int& index, ConstructeurArbreInstruction* constructeurArbreInstruction) override;

};

#endif /* BDC43121_B136_4DA5_86FF_DCA70967CB37 */
