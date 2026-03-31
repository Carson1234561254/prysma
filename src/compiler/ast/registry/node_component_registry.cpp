#include "compiler/ast/registry/node_component_registry.h"

decltype(auto)
NodeComponentRegistry::mapper<NODEGEN_TYPE_COMPONENT_TAG>::get(NodeComponentRegistry& reg) {
    // return reg.nodegen_types;

    return reg.nodegen_types;
}

decltype(auto)
NodeComponentRegistry::mapper<NAME_COMPONENT_TAG>::get(NodeComponentRegistry& reg) {
    // return reg.names;

    return reg.names;
}

decltype(auto)
NodeComponentRegistry::mapper<CHILD_COMPONENT_TAG>::get(NodeComponentRegistry& reg) {
    // return reg.children;

    return reg.children;
}