fn bool testNewDeleteBoolTrue()
{
   dec string[] feature = "1.test_new_delete_bool_true : ";
   call print(ref feature);
   dec ptr p = new bool;
   aff p = true;
   dec bool value = unref p;
   delete p;
   if (value == true) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteBoolFalse()
{
   dec string[] feature = "2.test_new_delete_bool_fa/lse : ";
   call print(ref feature);
   dec ptr p = new bool;
   aff p = false;
   dec bool value = unref p;
   delete p;
   if (value == false) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteBoolReassignment()
{
   dec string[] feature = "3.test_new_delete_bool_reassignment : ";
   call print(ref feature);
   dec ptr p = new bool;
   aff p = true;
   aff p = false;
   dec bool value = unref p;
   delete p;
   if (value == false) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteBoolReassignmentInverse()
{
   dec string[] feature = "4.test_new_delete_bool_reassignment_inverse : ";
   call print(ref feature);
   dec ptr p = new bool;
   aff p = false;
   aff p = true;
   dec bool value = unref p;
   delete p;
   if (value == true) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn int32 testNewDeleteBool()
{
   call print(call testNewDeleteBoolTrue()); call backSlashN();
   call print(call testNewDeleteBoolFalse()); call backSlashN();
   call print(call testNewDeleteBoolReassignment()); call backSlashN();
   call print(call testNewDeleteBoolReassignmentInverse()); call backSlashN();

   return 1;
}
