// Dans le futur les tests pourront avoir une condition if, pour le moment je suis obligé de passer manuellement chaque test
// afin de déterminer si le résultat est bon 

scope {

   // Test 1 : Priorité standard (* gagne sur +)
   // Calcul : 10 + (2 * 5) = 20
   // Si la priorité est fausse (gauche vers droite) : (10 + 2) * 5 = 60
   fn bool testPrioriteSimple()
   {
      dec int a = 10;
      dec int b = 2;
      dec int c = 5;
      dec int d = a + b * c; 
      if (d == 20) {
         return true;
      } else {
         return false;
      }
      return false;
   }

   // Test 2 : Priorité complexe avec 4 variables
   // Calcul : (2 * 3) + (4 * 5) = 6 + 20 = 26
   // Si faux : 2 * 3 + 4 = 10, puis 10 * 5 = 50
   fn bool testPrioriteComplexe()
   {
      dec int a = 2;
      dec int b = 3;
      dec int c = 4;
      dec int d = 5;
      dec int resultat = a * b + c * d;


      if (resultat == 26) {
         return true;
      } else {
         return false;
      }
      return false;
   }

   // Test 3 : Vérification de la mise à jour d'état (aff) avant calcul
   // On initialise a à 1, puis on le change à 10 avant le calcul
   // Calcul : 10 + 5 = 15
   fn bool testMiseAJourEtat()
   {
      dec int a = 1;
      dec int b = 5;
      
      aff a = 10; 
      
      dec int c = a + b;
      if (c == 15) {
         return true;
      } else {
         return false;
      }
      
      return false;
   }

   // Test 4 : Vérifier que les arguments peuvent passer dans une fonction 
   fn bool testPassArgFonction(arg int a, arg float b)
   {  
      if (a == 10 && b == 25.5) {
         return true;
      } else {
         return false;
      }

      return false;
   }


   fn int main()
   {
      
      call printBool(call testPrioriteSimple());
      call printBool(call testPrioriteComplexe());
      call printBool(call testMiseAJourEtat());

      dec int a = 10; 
      dec float b = 25.5;
      call printBool(call testPassArgFonction(a,b)); 
      
      // Appeler la méthode de nouveau pour voir si le contexte n'a pas changé
      dec int d = 10; 
      dec float e = 25.5;
      call printBool(call testPassArgFonction(d,e));

      // call testPassArgFonction(1,1); une erreur ici je dois corriger ça plus tard, il n'y a que les variables qui passe. 
      return 1;
   }
}