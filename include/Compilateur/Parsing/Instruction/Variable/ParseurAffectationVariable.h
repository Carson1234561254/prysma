#ifndef E5F6G7H8_I9J0K1L2_M3N4O5P6_Q7R8S9T0
#define E5F6G7H8_I9J0K1L2_M3N4O5P6_Q7R8S9T0

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Lexer/Lexer.h"
#include "Compilateur/Parsing/Interfaces/IParser.h"
#include "Compilateur/Parsing/ParserBase.h"
#include <memory>

class RegistreVariable;

class ParseurAffectationVariable : public IParser, public ParserBase
{

public:

    ParseurAffectationVariable();
    ~ParseurAffectationVariable();

    std::shared_ptr<INoeud> parser(std::vector<Token>& tokens, int& index, ConstructeurArbreInstruction* constructeurArbreInstruction) override;
};

#endif /* E5F6G7H8_I9J0K1L2_M3N4O5P6_Q7R8S9T0 */
