scope {

   fn int64 main() 
   {
      dec int64 a = 10; 

      dec string[] tableau = "a, b, c, d, e, f, g, h, i, j";

      call print(ref tableau);
      call print(10);
      call print(a);
      call print(true);
    
      return 0;
   }
}