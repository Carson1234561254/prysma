fn bool testLogicalAnd()
{
   dec string[] feature = "1.test_logical_and : ";
   call print(ref feature);
   dec bool a = true && true; 

   if (a == true) {
      return true;
   } else {
      return false;
   }

   return false;
}

fn bool testLogicalOr()
{
   dec string[] feature = "2.test_logical_or : ";
   call print(ref feature);
   dec bool a = true || false; 

   if (a == true) {
      return true;
   } else {
      return false;
   }

   return false;
}

fn bool testLogicalNot()
{
   dec string[] feature = "3.test_logical_not : ";
   call print(ref feature);
   dec bool a = true; 
   dec bool b = !a; 

   if (b == false) {
      return true;
   } else {
      return false;
   }

   return false;
}

fn bool testLogicalNotFalse()
{
   dec string[] feature = "4.test_logical_not_fal/se : ";
   call print(ref feature);
   dec bool a = !false; 

   if (a == true) {
      return true;
   } else {
      return false;
   }

   return false;
}

fn bool testLogicalOrVariable()
{
   dec string[] feature = "5.test_logical_or_variable : ";
   call print(ref feature);
   dec bool a = true; 
   dec bool b = false;

   dec bool d = a || b;

   if (d == true) {
      return true;
   } else {
      return false;
   }

   return false;
}

fn bool testLogicalAndVariable()
{
   dec string[] feature = "6.test_logical_and_variable : ";
   call print(ref feature);
   dec bool a = true; 
   dec bool b = false;

   dec bool d = a && b;
  // temporary test
   if (d == false) {
      return true;
   } else {
      return false;
   }

   return false;
}

fn bool testLogicalNotAndVariable()
{
   dec string[] feature = "7.test_logical_not_and_variable : ";
   call print(ref feature);
   dec bool a = true; 
   dec bool b = false;

   dec bool d = !a && b;

   if (d == false) {
      return true;
   } else {
      return false;
   }

   return false;
}

fn int32 testFunctionalVariableBool()
{
   // Test bools
   call print(call testLogicalAnd()); call backSlashN();
   call print(call testLogicalOr()); call backSlashN();
   call print(call testLogicalNot()); call backSlashN();
   call print(call testLogicalNotFalse()); call backSlashN();
   call print(call testLogicalOrVariable()); call backSlashN();
   call print(call testLogicalAndVariable()); call backSlashN();
   call print(call testLogicalNotAndVariable()); call backSlashN();

   return 1;
}
