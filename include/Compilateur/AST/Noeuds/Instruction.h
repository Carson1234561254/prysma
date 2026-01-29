#ifndef CE440E6B_95E4_4EC8_8C66_1916C9716A77
#define CE440E6B_95E4_4EC8_8C66_1916C9716A77
#include "Compilateur/AST/Noeuds/Interfaces/IInstruction.h"
#include <vector>


class Instruction: public IInstruction
{
private: 
    std::vector<INoeud> enfants; 
public: 

    Instruction();
    ~Instruction();

   void ajouterInstruction(const std::vector<std::shared_ptr<INoeud>>& enfants) override; 
};



#endif /* CE440E6B_95E4_4EC8_8C66_1916C9716A77 */
