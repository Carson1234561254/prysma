#include "compiler/ast/registry/stack/registry_variable.h"
#include "compiler/visitor/code_gen/visitor_general_gen_code.h"
#include "compiler/ast/ast_genere.h"

void GeneralVisitorGenCode::visiter([[maybe_unused]]NodeArgFunction* nodeArgFunction) 
{
    _contextGenCode->setTemporaryValue(Symbol(nullptr, _contextGenCode->getTemporaryValue().getType(), _contextGenCode->getTemporaryValue().getPointedElementType()));
}