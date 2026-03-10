
fn bool testNewDeleteInt32Basique()
{
   dec string[] fonctionnalite = "1.testNewDeleteInt32Basique : ";
   call print(ref fonctionnalite);
   dec ptr p = new int32;
   aff p = 42;
   dec int32 val = unref p;
   delete p;
   if (val == 42) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteInt32Zero()
{
   dec string[] fonctionnalite = "2.testNewDeleteInt32Zero : ";
   call print(ref fonctionnalite);
   dec ptr p = new int32;
   aff p = 0;
   dec int32 val = unref p;
   delete p;
   if (val == 0) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteInt32Negatif()
{
   dec string[] fonctionnalite = "3.testNewDeleteInt32Negatif : ";
   call print(ref fonctionnalite);
   dec ptr p = new int32;
   dec int32 valeur = 0 - 100;
   aff p = valeur;
   dec int32 val = unref p;
   delete p;
   if (val == valeur) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteInt32GrandeValeur()
{
   dec string[] fonctionnalite = "4.testNewDeleteInt32GrandeValeur : ";
   call print(ref fonctionnalite);
   dec ptr p = new int32;
   aff p = 2147483;
   dec int32 val = unref p;
   delete p;
   if (val == 2147483) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteInt32Reaffectation()
{
   dec string[] fonctionnalite = "5.testNewDeleteInt32Reaffectation : ";
   call print(ref fonctionnalite);
   dec ptr p = new int32;
   aff p = 10;
   aff p = 99;
   dec int32 val = unref p;
   delete p;
   if (val == 99) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn int32 testNewDeleteInt32()
{
   call print(call testNewDeleteInt32Basique()); call backSlashN();
   call print(call testNewDeleteInt32Zero()); call backSlashN();
   call print(call testNewDeleteInt32Negatif()); call backSlashN();
   call print(call testNewDeleteInt32GrandeValeur()); call backSlashN();
   call print(call testNewDeleteInt32Reaffectation()); call backSlashN();

   return 1;
}
