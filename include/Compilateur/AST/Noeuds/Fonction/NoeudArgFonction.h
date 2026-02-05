#ifndef B9F8948B_23A4_4812_A098_C71C4D92373B
#define B9F8948B_23A4_4812_A098_C71C4D92373B
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/AST/Registre/RegistreType.h"
#include <memory>

class NoeudArgFonction: public INoeud
{
private:
     std::shared_ptr<RegistreType> _registreType; 
     TokenType _nom;
     TokenType _type;

public: 
    NoeudArgFonction(std::shared_ptr<RegistreType> registreType, TokenType nom, TokenType type);
    ~NoeudArgFonction();

    llvm::Value* genCode() override;
};

#endif /* B9F8948B_23A4_4812_A098_C71C4D92373B */
