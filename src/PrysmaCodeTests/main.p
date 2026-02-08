scope 
{
   fn int teste(arg int a arg int b)
   {
      call printInt(unref a);
      call printInt(unref b);
      return 0;
   }

   fn int main()
   {
        dec int a = 10 + 10; 
        dec int b =  unref a + 10 + unref a ;
        dec float c = 1;
        dec bool d = 1; 
        dec int teste_var = ref a;
        aff a = 10;
        dec int e = 14;
        dec int f = 15; 
        call teste(unref e unref f);

        return unref a;
   }
}
