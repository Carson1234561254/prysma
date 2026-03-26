include "test_loop.p";
include "test_condition.p";
include "test_functional_variable_bool.p";
include "test_functional_variable_float.p";
include "test_functional_variable_int.p";
include "test_recursion.p";
include "test_array_bool.p";
include "test_array_float.p";
include "test_array_int.p";
include "test_memory_dynamic.p";


fn int64 main() 
{
    call testLoop();
    call testCondition();
    call testFunctionalVariableBool();
    call testFunctionalVariableFloat();
    call testFunctionalVariableInt();
    call testRecursion();
    call testArrayBool();
    call testArrayFloat();
    call testArrayInt();
    call testMemoryDynamic();
    
    return 0;
}