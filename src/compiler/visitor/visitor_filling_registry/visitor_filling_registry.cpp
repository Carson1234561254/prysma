#include "compiler/ast/utils/orchestrator_include/orchestrator_include.h"
#include "compiler/visitor/visitor_filling_registry/visitor_filling_registry.h"

FillingVisitorRegistry::FillingVisitorRegistry(ContextGenCode* contextGenCode, OrchestratorInclude* orchestrator) 
    : _contextGenCode(contextGenCode), _orchestrator(orchestrator) {}

FillingVisitorRegistry::~FillingVisitorRegistry() = default;
