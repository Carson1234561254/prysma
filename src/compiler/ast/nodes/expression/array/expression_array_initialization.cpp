#ifndef EXPRESSION_ARRAYINITIALIZATION_CPP
#define EXPRESSION_ARRAYINITIALIZATION_CPP

#include "compiler/array/expression_array_initialization.h"
#include "compiler/ast/ast_genere.h"
#include "compiler/ast/nodes/interfaces/i_node.h"
#include "compiler/ast/registry/context_expression.h"
#include "compiler/lexer/lexer.h"
#include "compiler/lexer/token_type.h"
#include <cstddef>
#include <vector>

ExpressionArrayInitialization::ExpressionArrayInitialization(ContextExpression& expressionContext)
    : _context(expressionContext)
{}

ExpressionArrayInitialization::~ExpressionArrayInitialization()
= default;

auto ExpressionArrayInitialization::build(std::vector<Token>& equation) -> INode*
{
    std::vector<INode*> arrayElements;
    std::vector<Token> subEquation;
    size_t index = 1;

    while (index < equation.size() && equation[index].type != TOKEN_BRACKET_CLOSE) {
        if (equation[index].type == TOKEN_COMMA) {
            index++;
            INode* element = _context.getBuilderTreeEquation()->build(subEquation);
            if (element != nullptr) {
                arrayElements.push_back(element);
            }
            subEquation.clear();
            continue;
        }

        subEquation.push_back(equation[index]);
        index++;
    }

    if (!subEquation.empty()) {
        INode* element = _context.getBuilderTreeEquation()->build(subEquation);
        if (element != nullptr) {
            arrayElements.push_back(element);
        }
    }

    return _context.getBuilderTreeEquation()->allocate<NodeArrayInitialization>(arrayElements);
}

#endif /* EXPRESSION_ARRAYINITIALIZATION_CPP */