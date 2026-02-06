#ifndef FD83BD8A_F363_49DA_B571_00377736E3B4
#define FD83BD8A_F363_49DA_B571_00377736E3B4
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
class NoeudArgPassFonction : public INoeud
{
private: 


public:
    NoeudArgPassFonction();
    ~NoeudArgPassFonction();

    llvm::Value* genCode() override;
};

#endif /* FD83BD8A_F363_49DA_B571_00377736E3B4 */
