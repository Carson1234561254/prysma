#include "compiler/ast/builder_tree_instruction.h"
#include "compiler/ast/nodes/interfaces/i_node.h"
#include "compiler/ast/nodes/node_instruction.h"
#include "compiler/ast/registry/registry_instruction.h"
#include "compiler/parser/interfaces/i_parser.h"
#include "compiler/manager_error.h"
#include "compiler/lexer/lexer.h"
#include "compiler/lexer/token_type.h"
#include <cstddef>
#include <llvm/Support/Allocator.h>
#include <vector>

BuilderTreeInstruction::BuilderTreeInstruction(RegistryInstruction* registryInstructions, llvm::BumpPtrAllocator& arena)
    : _registryInstructions(registryInstructions), _arena(arena)
{
    
}

BuilderTreeInstruction::~BuilderTreeInstruction()
= default;

auto BuilderTreeInstruction::build(std::vector<Token>& tokens, int& index) -> INode*
{
    if (!_registryInstructions->exists(tokens[static_cast<size_t>(index)].type)) {
        throw CompilationError("Unknown instruction: '" + tokens[static_cast<size_t>(index)].value + "'", Line(tokens[static_cast<size_t>(index)].line), Column(tokens[static_cast<size_t>(index)].column));
    }
    IParser* parentNode = _registryInstructions->get(tokens[static_cast<size_t>(index)].type);
    INode* child = parentNode->parse(tokens, index);
   
    return child;
}


auto BuilderTreeInstruction::build(std::vector<Token>& tokens) -> INode*
{
    int index = 0; 
    // Create a global container for the whole file
    auto* globalProgram = allocate<NodeInstruction>();
    
    while (index < static_cast<int>(tokens.size()) && tokens[static_cast<size_t>(index)].type != TOKEN_EOF) {
        INode* child = build(tokens, index);
        if (child != nullptr) {
            globalProgram->addInstruction(child);
        }
    }
    return globalProgram;
}

auto BuilderTreeInstruction::getArena() -> llvm::BumpPtrAllocator&
{
    return _arena;
}