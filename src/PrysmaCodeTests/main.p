
fn void test(arg int32 test)
{
   call print(test);
}


fn int32 main() 
{
   dec ptr monPtr = new int32;

   aff monPtr = 120; 

   call test(monPtr);

   return 0;
}
