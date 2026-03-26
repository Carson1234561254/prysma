#include "compiler/ast/nodes/node_instruction.h"
#include "compiler/ast/nodes/interfaces/i_node.h"
#include "compiler/visitor/interfaces/i_visitor.h"
#include "compiler/ast/ast_genere.h"

NodeInstruction::NodeInstruction()
= default;

void NodeInstruction::accept(IVisitor* visitor)
{
    visitor->visiter(this);
}

void NodeInstruction::addInstruction(INode* child)
{
    if (child != nullptr) {
        children.push_back(child);
    }
}

auto NodeInstruction::getGeneratedType() const -> NodeTypeGenerated
{
    return NodeTypeGenerated::CallFunction; 
}
