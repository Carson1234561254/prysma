#ifndef DDD959AA_55F6_46B7_A433_8E073A1EACCE
#define DDD959AA_55F6_46B7_A433_8E073A1EACCE

#include <memory>
#include "Compilateur/Lexer/Lexer.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudVariable.h"

class ParseurVariable
{

public: 
    static std::shared_ptr<NoeudVariable> parser(std::vector<Token>& tokens, int& index); 
};

#endif /* DDD959AA_55F6_46B7_A433_8E073A1EACCE */
