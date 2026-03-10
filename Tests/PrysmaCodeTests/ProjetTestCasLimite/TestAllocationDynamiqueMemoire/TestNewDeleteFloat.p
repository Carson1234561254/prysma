
fn bool testNewDeleteFloatBasique()
{
   dec string[] fonctionnalite = "1.testNewDeleteFloatBasique : ";
   call print(ref fonctionnalite);
   dec ptr p = new float;
   aff p = 3.14;
   dec float val = unref p;
   delete p;
   if (val == 3.14) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteFloatZero()
{
   dec string[] fonctionnalite = "2.testNewDeleteFloatZero : ";
   call print(ref fonctionnalite);
   dec ptr p = new float;
   aff p = 0.0;
   dec float val = unref p;
   delete p;
   if (val == 0.0) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteFloatNegatif()
{
   dec string[] fonctionnalite = "3.testNewDeleteFloatNegatif : ";
   call print(ref fonctionnalite);
   dec ptr p = new float;
   dec float valeur = 0.0 - 99.9;
   aff p = valeur;
   dec float val = unref p;
   delete p;
   if (val == valeur) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteFloatPetiteValeur()
{
   dec string[] fonctionnalite = "4.testNewDeleteFloatPetiteValeur : ";
   call print(ref fonctionnalite);
   dec ptr p = new float;
   aff p = 0.001;
   dec float val = unref p;
   delete p;
   if (val == 0.001) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn bool testNewDeleteFloatReaffectation()
{
   dec string[] fonctionnalite = "5.testNewDeleteFloatReaffectation : ";
   call print(ref fonctionnalite);
   dec ptr p = new float;
   aff p = 1.1;
   aff p = 55.5;
   dec float val = unref p;
   delete p;
   if (val == 55.5) {
      return true;
   } else {
      return false;
   }
   return false;
}

fn int32 testNewDeleteFloat()
{
   call print(call testNewDeleteFloatBasique()); call backSlashN();
   call print(call testNewDeleteFloatZero()); call backSlashN();
   call print(call testNewDeleteFloatNegatif()); call backSlashN();
   call print(call testNewDeleteFloatPetiteValeur()); call backSlashN();
   call print(call testNewDeleteFloatReaffectation()); call backSlashN();

   return 1;
}
