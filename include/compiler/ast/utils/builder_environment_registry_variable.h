#ifndef A1014A88_A2B2_4637_B4CD_3709FCBE042F
#define A1014A88_A2B2_4637_B4CD_3709FCBE042F

#include "compiler/ast/registry/context_gen_code.h"
#include "compiler/ast/utils/i_builder_environment_registry.h"

class BuilderEnvironmentRegistryVariable : public IBuilderEnvironmentRegistry
{
private:
    ContextGenCode* _contextGenCode;

public:
    explicit BuilderEnvironmentRegistryVariable(ContextGenCode* _contextGenCode);
    ~BuilderEnvironmentRegistryVariable() override;

    BuilderEnvironmentRegistryVariable(const BuilderEnvironmentRegistryVariable&) = delete;
    auto operator=(const BuilderEnvironmentRegistryVariable&) -> BuilderEnvironmentRegistryVariable& = delete;

    BuilderEnvironmentRegistryVariable(BuilderEnvironmentRegistryVariable&&) = delete;
    auto operator=(BuilderEnvironmentRegistryVariable&&) -> BuilderEnvironmentRegistryVariable& = delete;

    void fill() override;

};

#endif /* A1014A88_A2B2_4637_B4CD_3709FCBE042F */
