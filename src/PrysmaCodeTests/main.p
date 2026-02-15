scope {

   fn bool testPassArgFonction(arg int a)
   {  
      if (a<= 10) {
         return true;
      } else {
         return false;
      }

      return false;
   }

   fn int main()
   {
      dec int a = 10;
      call printBool(call testPassArgFonction(a));
 
      return 1;
   }
}