// fibonaci
scope {
   fn int main() {
   
      dec int a = 0;
      dec int[4] tableau = [a, 2, 3, 4];
   
      aff tableau[0] = 1;
      dec int i = 0; 
      while(i<4) {
         call printInt(tableau[i]);
         aff i = i + 1;
      }

      return 0;
   }
}

// 