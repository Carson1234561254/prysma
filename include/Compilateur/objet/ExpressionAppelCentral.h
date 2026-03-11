#ifndef EXPRESSION_APPELCENTRAL_H
#define EXPRESSION_APPELCENTRAL_H

#include "Compilateur/AST/Noeuds/Expression/IExpressionMoteur.h"
#include "Compilateur/AST/Registre/ContexteExpression.h"

class ExpressionAppelCentral : public IExpressionMoteur
{
private:
    ContexteExpression& _contexteExpression;

public:
    explicit ExpressionAppelCentral(ContexteExpression& contexteExpression);
    ~ExpressionAppelCentral() override;

    INoeud* construire(std::vector<Token>& equation) override;
};

#endif /* EXPRESSION_APPELCENTRAL_H */