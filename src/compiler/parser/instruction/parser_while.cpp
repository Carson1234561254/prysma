#ifndef PARSER_WHILE_CPP
#define PARSER_WHILE_CPP

#include "compiler/instruction/parser_while.h"
#include "compiler/ast/ast_genere.h"
#include "compiler/ast/nodes/interfaces/i_instruction.h"
#include "compiler/ast/nodes/interfaces/i_node.h"
#include "compiler/ast/nodes/node_instruction.h"
#include "compiler/ast/registry/context_parser.h"
#include "compiler/lexer/lexer.h"
#include "compiler/lexer/token_type.h"
#include <vector>


ParserWhile::ParserWhile(ContextParser& contextParser) 
    : _contextParser(contextParser)
{}

ParserWhile::~ParserWhile() = default;

INode* ParserWhile::parse(std::vector<Token>& tokens, int& index)
{
    consume(tokens, index, TOKEN_WHILE, "Error, expected token 'while' ");

    consume(tokens, index, TOKEN_PAREN_OPEN, "Error, token is not '('! ");
    
    INode* condition = _contextParser.getBuilderTreeEquation()->build(tokens, index);

    consume(tokens, index, TOKEN_PAREN_CLOSE, "Error, token is not ')'! ");

    IInstruction* nodeBlockWhile = _contextParser.getBuilderTreeInstruction()->allocate<NodeInstruction>();
    consume(tokens, index, TOKEN_BRACE_OPEN, "Error, token is not '{'");
    consumeChildBody(tokens, index, nodeBlockWhile, _contextParser.getBuilderTreeInstruction(), TOKEN_BRACE_CLOSE);
    consume(tokens, index, TOKEN_BRACE_CLOSE, "Error, token is not '}'");

    IInstruction* nodeBlockEndWhile = _contextParser.getBuilderTreeInstruction()->allocate<NodeInstruction>();

    IInstruction* nodeWhile = _contextParser.getBuilderTreeInstruction()->allocate<NodeWhile>(condition, nodeBlockWhile, nodeBlockEndWhile);

    return nodeWhile;
}

#endif /* PARSER_WHILE_CPP */




