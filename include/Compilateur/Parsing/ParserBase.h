#ifndef A1B2C3D4_E5F6G7H8_I9J0K1L2_M3N4O5P6
#define A1B2C3D4_E5F6G7H8_I9J0K1L2_M3N4O5P6

#include "Compilateur/Lexer/Lexer.h"
#include <vector>
#include <string>

class ParserBase
{
protected:
    Token consommer(std::vector<Token>& tokens, int& index, TokenType typeAttendu, const std::string& messageErreur);
};

#endif /* A1B2C3D4_E5F6G7H8_I9J0K1L2_M3N4O5P6 */
