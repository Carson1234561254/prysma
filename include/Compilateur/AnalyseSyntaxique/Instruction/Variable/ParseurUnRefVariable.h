#ifndef BA7CC6F6_C206_4FBD_9DFD_D7DD1803CDAD
#define BA7CC6F6_C206_4FBD_9DFD_D7DD1803CDAD
#include "Compilateur/AnalyseSyntaxique/Interfaces/IParseur.h"
#include "Compilateur/AnalyseSyntaxique/ParseurBase.h"
#include "llvm/Support/Allocator.h"

class ParseurUnRefVariable : public IParseur, ParseurBase
{
private:
    llvm::BumpPtrAllocator& _arena;
public: 
    ParseurUnRefVariable(llvm::BumpPtrAllocator& arena);
    ~ParseurUnRefVariable();
    
    INoeud* parser(std::vector<Token>& tokens, int& index) override;

};

#endif /* BA7CC6F6_C206_4FBD_9DFD_D7DD1803CDAD */
