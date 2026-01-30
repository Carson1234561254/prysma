#ifndef B863FD2E_67EB_4E4F_BF6B_F5DEBEF317C9
#define B863FD2E_67EB_4E4F_BF6B_F5DEBEF317C9

#include "Compilateur/Parsing/Interfaces/IParser.h"
class ParserMain : public IParser
{
public:
    std::shared_ptr<INoeud> parser(std::vector<Token>& tokens, int& index, std::shared_ptr<ConstructeurArbreInstruction> constructeurArbreInstruction) override;

};

#endif /* B863FD2E_67EB_4E4F_BF6B_F5DEBEF317C9 */
