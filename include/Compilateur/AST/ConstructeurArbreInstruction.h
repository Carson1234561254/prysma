#ifndef BDC39C44_6952_4793_8198_C083B106A089
#define BDC39C44_6952_4793_8198_C083B106A089

#include "Compilateur/AST/Interfaces/IConstructeurArbre.h"
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Lexer/Lexer.h"
#include "Compilateur/AST/Registre/RegistreInstruction.h"

class ConstructeurArbreInstruction : public IConstructeurArbre
{
private: 
    RegistreInstruction* _registreInstructions;
    llvm::BumpPtrAllocator& _arena;
public: 

    ConstructeurArbreInstruction(RegistreInstruction* registreInstructions, llvm::BumpPtrAllocator& arena);
    ~ConstructeurArbreInstruction();

    INoeud* construire(std::vector<Token>& tokens) override;  
    INoeud* construire(std::vector<Token>& tokens, int& index) override;
    llvm::BumpPtrAllocator& getArena() override;

};

#endif /* BDC39C44_6952_4793_8198_C083B106A089 */
