// fibonaci
scope {

   fn int tableauReturn()
   {
      dec int[5] tableau = [0, 1, 2, 3, 4];
      return tableau[2];
   }

   fn int main() {

      dec int tableau = call tableauReturn();

      dec int i = 0; 

      while(i < 5)
      {
         call printInt(tableau[i]);
         aff i = i + 1;
      }
   
      return 0;
   }
}