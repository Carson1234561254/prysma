#ifndef EXPRESSION_CALLFUNCTION_CPP
#define EXPRESSION_CALLFUNCTION_CPP

#include "compiler/function/expression_call_function.h"
#include "compiler/ast/nodes/interfaces/i_node.h"
#include "compiler/ast/registry/context_expression.h"
#include "compiler/function/parser_call_function.h"
#include "compiler/lexer/lexer.h"
#include <vector>

ExpressionCallFunction::ExpressionCallFunction(ContextExpression& expressionContext)
    : _context(expressionContext)
{}

ExpressionCallFunction::~ExpressionCallFunction()
= default;

auto ExpressionCallFunction::build(std::vector<Token>& equation) -> INode*
{
    ParserCallFunction parserCall(*_context.getContextParser());
    int indexZero = 0;
    return parserCall.parse(equation, indexZero);
}

#endif /* EXPRESSION_CALLFUNCTION_CPP */