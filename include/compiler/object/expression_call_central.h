#ifndef EXPRESSION_CALLCENTRAL_H
#define EXPRESSION_CALLCENTRAL_H

#include "compiler/ast/nodes/expression/i_expression_engine.h"
#include "compiler/ast/nodes/interfaces/i_node.h"
#include "compiler/ast/registry/context_expression.h"
#include "compiler/lexer/lexer.h"
#include <vector>

class ExpressionCallCentral : public IExpressionEngine
{
private:
    ContextExpression& _context;

public:
    explicit ExpressionCallCentral(ContextExpression& expressionContext);
    ~ExpressionCallCentral() override;

    ExpressionCallCentral(const ExpressionCallCentral&) = delete;
    auto operator=(const ExpressionCallCentral&) -> ExpressionCallCentral& = delete;

    ExpressionCallCentral(ExpressionCallCentral&&) = delete;
    auto operator=(ExpressionCallCentral&&) -> ExpressionCallCentral& = delete;

    auto build(std::vector<Token>& equation) -> INode* override;
};

#endif /* EXPRESSION_CALLCENTRAL_H */