scope 
{
    fn int main()
    {
        dec int a = 1230; 
        dec float b = 100*234*a+923+a+(23*234);
        dec int d = 100*234*a+923+a+(23*234);
        dec int c = b+1;
        aff c = 10;

        call printInt(pass c);
        call printFloat(pass b);
        
        return c;
    }
}
