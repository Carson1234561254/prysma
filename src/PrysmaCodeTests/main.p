
class animal
{

   public:

      fn void animal()
      {

      }

      fn void crier(string[] crie)
      {
         call print(crie);
      }

   fin;
}

class Chien 
{ 
   private: 
      dec ptr animal = new animal();
      
      dec string[] crie = " ";

      fn void crierPriv()
      {
         call print("Woof!");
      }

   fin;

   public:

      fn void Chien()
      {
         aff crie = "Woof!";
      }

      fn void crier()
      {
         animal.crier(crie);
      }
   fin;
}



fn int32 main() 
{
   dec NomClasse objet = new NomClasse(42, "Hello");

   call objet.methodePrint();

   return 0;
}
