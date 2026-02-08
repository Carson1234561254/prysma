scope 
{
   fn int main()
   {
        dec int a = 10 + 10; 
        dec int b =  unref a + 10 + unref a ;
        dec float c = 1;
        dec bool d = 1; 
        dec int teste = ref a;
        aff a = 10;
        
        call printInt( unref teste ); 

        return unref a;
   }
}
