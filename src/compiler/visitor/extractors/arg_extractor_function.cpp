#include "compiler/visitor/extractors/arg_extractor_function.h"
#include "compiler/ast/ast_genere.h"

void ArgExtractorFunction::visiter(NodeArgFunction* node) {
    arg = node;
}