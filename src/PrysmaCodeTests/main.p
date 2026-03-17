class Animal
{
   public:

      fn void Animal()
      {
      }

      fn void crier(arg string[] crie)
      {
         call print(crie);
      }
}

class Chien 
{ 
   private: 
     // dec ptr animal = new Animal();
      
      dec string[] crie = " ";

      fn void crierPriv()
      {
         call print("Woof!");
      }

   public:

      fn void Chien()
      {
         aff crie = "Woof!";
      }

      fn void crier()
      {
         //call animal.crier(crie);
      }
}

fn int32 main() 
{
   dec ptr chien = new Chien();

   call chien.crier();

   return 0;
}