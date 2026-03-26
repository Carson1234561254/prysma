#include "compiler/parser/parser_base.h"
#include "compiler/ast/interfaces/i_builder_tree.h"
#include "compiler/ast/nodes/interfaces/i_instruction.h"
#include "compiler/ast/nodes/interfaces/i_node.h"
#include "compiler/lexer/lexer.h"
#include "compiler/lexer/token_type.h"
#include "compiler/manager_error.h"
#include <cstddef>
#include <string>
#include <vector>

auto ParserBase::consume(std::vector<Token>& tokens, int& index, TokenType expectedType, const std::string& errorMessage) -> Token
{
    if (index < 0 || index >= static_cast<int>(tokens.size()) || tokens[static_cast<size_t>(index)].type != expectedType) {
        if (index >= 0 && index < static_cast<int>(tokens.size())) {
            throw CompilationError(errorMessage, Line(tokens[static_cast<size_t>(index)].line), Column(tokens[static_cast<size_t>(index)].column));
        }
        throw CompilationError(errorMessage, Line(1), Column(1));
    }
    return tokens[static_cast<size_t>(index++)];
}

void ParserBase::consumeChildBody(std::vector<Token>& tokens, int& index , IInstruction* parent, IBuilderTree* builderTree, TokenType end)
{
    while(index < static_cast<int>(tokens.size()) && tokens[static_cast<size_t>(index)].type != end)
    {
        // Ignore commas between elements
        if(tokens[static_cast<size_t>(index)].type == TOKEN_COMMA)
        {
            index++;
            continue;
        }
        
        INode* child = builderTree->build(tokens, index);
        parent->addInstruction(child);
    }
}
