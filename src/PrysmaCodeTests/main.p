scope {
   fn void test()
   {
      call printInt(1);
   }
 
   fn int main() {
      call test();
      return 0;
   }
}