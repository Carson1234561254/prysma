include "TestAllocationDynamiqueMemoire/TestNewDeleteInt32.p";
include "TestAllocationDynamiqueMemoire/TestNewDeleteInt64.p";
include "TestAllocationDynamiqueMemoire/TestNewDeleteFloat.p";
include "TestAllocationDynamiqueMemoire/TestNewDeleteBool.p";
include "TestAllocationDynamiqueMemoire/TestPassagePtrArgument.p";

fn int32 testMemoireDynamique()
{
   call testNewDeleteInt32();
   call testNewDeleteInt64();
   call testNewDeleteFloat();
   call testNewDeleteBool();
   call testPassagePtrArgument();

   return 1;
}
