#include "Compilateur/Parsing/ParserBase.h"
#include <stdexcept>

Token ParserBase::consommer(std::vector<Token>& tokens, int& index, TokenType typeAttendu, const std::string& messageErreur)
{
    if (index < 0 || index >= static_cast<int>(tokens.size()) || tokens[index].type != typeAttendu) {
        throw std::runtime_error(messageErreur);
    }
    return tokens[index++];
}
