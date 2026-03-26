include "test_allocation_dynamic_memory/test_new_delete_int32.p";
include "test_allocation_dynamic_memory/test_new_delete_int64.p";
include "test_allocation_dynamic_memory/test_new_delete_float.p";
include "test_allocation_dynamic_memory/test_new_delete_bool.p";
include "test_allocation_dynamic_memory/test_passage_ptr_argument.p";

fn int32 testMemoryDynamic()
{
   call testNewDeleteInt32();
   call testNewDeleteInt64();
   call testNewDeleteFloat();
   call testNewDeleteBool();
   call testPassPtrArgument();

   return 1;
}
