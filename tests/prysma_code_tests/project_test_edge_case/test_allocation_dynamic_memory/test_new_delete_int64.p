fn bool testNewDeleteInt64Basic()
{
   dec string[] feature = "1.test_new_delete_int64_basic : ";
   call print(ref feature);
   dec ptr p = new int64;
   aff p = 100;
   dec int32 value = unref p;
   delete p;
   if (value == 100) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteInt64Zero()
{
   dec string[] feature = "2.test_new_delete_int64_zero : ";
   call print(ref feature);
   dec ptr p = new int64;
   aff p = 0;
   dec int32 value = unref p;
   delete p;
   if (value == 0) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteInt64Negative()
{
   dec string[] feature = "3.test_new_delete_int64_negative : ";
   call print(ref feature);
   dec ptr p = new int64;
   dec int32 valueToAssign = 0 - 500;
   aff p = valueToAssign;
   dec int32 value = unref p;
   delete p;
   if (value == valueToAssign) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteInt64LargeValue()
{
   dec string[] feature = "4.test_new_delete_int64_large_value : ";
   call print(ref feature);
   dec ptr p = new int64;
   aff p = 9999999;
   dec int32 value = unref p;
   delete p;
   if (value == 9999999) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteInt64Reassignment()
{
   dec string[] feature = "5.test_new_delete_int64_reassignment : ";
   call print(ref feature);
   dec ptr p = new int64;
   aff p = 1;
   aff p = 777;
   dec int32 value = unref p;
   delete p;
   if (value == 777) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn int32 testNewDeleteInt64()
{
   call print(call testNewDeleteInt64Basic()); call backSlashN();
   call print(call testNewDeleteInt64Zero()); call backSlashN();
   call print(call testNewDeleteInt64Negative()); call backSlashN();
   call print(call testNewDeleteInt64LargeValue()); call backSlashN();
   call print(call testNewDeleteInt64Reassignment()); call backSlashN();

   return 1;
}
