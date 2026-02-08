#ifndef F39730D3_0913_46B1_91E5_676A85D4CABB
#define F39730D3_0913_46B1_91E5_676A85D4CABB

#include "Compilateur/AnalyseSyntaxique/Interfaces/IParser.h"
#include "Compilateur/AnalyseSyntaxique/ParseurBase.h"
#include <memory>

class ParsingReturn : public IParser, public ParseurBase
{

public:

    explicit ParsingReturn();
    
    ~ParsingReturn();

    std::shared_ptr<INoeud> parser(std::vector<Token>& tokens, int& index, ConstructeurArbreInstruction* constructeurArbreInstruction) override;
};

#endif /* F39730D3_0913_46B1_91E5_676A85D4CABB */
