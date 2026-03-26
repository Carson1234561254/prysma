#ifndef PARSER_REFVARIABLE_CPP
#define PARSER_REFVARIABLE_CPP

#include "compiler/variable/parser_ref_variable.h"
#include "compiler/ast/ast_genere.h"
#include "compiler/ast/nodes/interfaces/i_node.h"
#include "compiler/ast/registry/context_parser.h"
#include "compiler/lexer/lexer.h"
#include "compiler/lexer/token_type.h"
#include <string>
#include <vector>


ParserRefVariable::ParserRefVariable(ContextParser& contextParser) 
    : _contextParser(contextParser)
{}

ParserRefVariable::~ParserRefVariable()
=default;

// Example: ref variable
auto ParserRefVariable::parse(std::vector<Token>& tokens, int& index) -> INode* 
{
    consume(tokens, index, TOKEN_REF, "Error: 'ref' expected");
    
    Token nameToken = consume(tokens, index, TOKEN_IDENTIFIER, "Error: variable name expected after 'ref'");
    std::string variableName = nameToken.value;
    
    return _contextParser.getBuilderTreeEquation()->allocate<NodeRefVariable>(variableName);
}

#endif /* PARSER_REFVARIABLE_CPP */




