
fn bool testNewDeleteBoolVrai()
{
   dec string[] fonctionnalite = "1.testNewDeleteBoolVrai : ";
   call print(ref fonctionnalite);
   dec ptr p = new bool;
   aff p = true;
   dec bool val = unref p;
   delete p;
   if (val == true) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteBoolFaux()
{
   dec string[] fonctionnalite = "2.testNewDeleteBoolFaux : ";
   call print(ref fonctionnalite);
   dec ptr p = new bool;
   aff p = false;
   dec bool val = unref p;
   delete p;
   if (val == false) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteBoolReaffectation()
{
   dec string[] fonctionnalite = "3.testNewDeleteBoolReaffectation : ";
   call print(ref fonctionnalite);
   dec ptr p = new bool;
   aff p = true;
   aff p = false;
   dec bool val = unref p;
   delete p;
   if (val == false) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteBoolReaffectationInverse()
{
   dec string[] fonctionnalite = "4.testNewDeleteBoolReaffectationInverse : ";
   call print(ref fonctionnalite);
   dec ptr p = new bool;
   aff p = false;
   aff p = true;
   dec bool val = unref p;
   delete p;
   if (val == true) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn int32 testNewDeleteBool()
{
   call print(call testNewDeleteBoolVrai()); call backSlashN();
   call print(call testNewDeleteBoolFaux()); call backSlashN();
   call print(call testNewDeleteBoolReaffectation()); call backSlashN();
   call print(call testNewDeleteBoolReaffectationInverse()); call backSlashN();

   return 1;
}
