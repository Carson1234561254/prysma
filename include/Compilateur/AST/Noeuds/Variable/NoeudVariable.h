#ifndef F89A7F51_AF50_45A0_8CAA_EAE593B67995
#define F89A7F51_AF50_45A0_8CAA_EAE593B67995

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/LLVM/LLVMBackend.h"
#include <llvm/IR/Instructions.h>
#include <memory>

class NoeudVariable : public INoeud
{
private:

    std::shared_ptr<LLVMBackend> _backend;

    std::string _nom; 
    llvm::Type * _type; 
    llvm::Value * _ArraySize = nullptr; 

    llvm::Value* _valeur; 
    
    // Autre variable utilisée pour faire une assignation. 
    llvm::AllocaInst* _variableAssigner;

    llvm::AllocaInst* allocation();
    llvm::AllocaInst* initialisation(llvm::AllocaInst* allocaInst); 
    void assignation(llvm::AllocaInst* allocaInst);
  
public:     
    NoeudVariable(const std::string& nom, llvm::Type* type, llvm::AllocaInst* variableAssigner, llvm::Value* valeur);
    ~NoeudVariable();

    llvm::Value* genCode() override; 
};

#endif /* F89A7F51_AF50_45A0_8CAA_EAE593B67995 */
