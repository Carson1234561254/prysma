#ifndef A3936496_9ECA_4884_AA42_A7A078E5B8B0
#define A3936496_9ECA_4884_AA42_A7A078E5B8B0

#include "Compilateur/AnalyseSyntaxique/Interfaces/IParseur.h"
#include "Compilateur/AnalyseSyntaxique/ParseurBase.h"

class ParseurNew : public IParseur, public ParseurBase
{
private:
    llvm::BumpPtrAllocator& _arena;

public:
    ParseurNew(llvm::BumpPtrAllocator& arena);
    ~ParseurNew();
    INoeud* parser(std::vector<Token>& tokens, int& index) override;

};

#endif /* A3936496_9ECA_4884_AA42_A7A078E5B8B0 */
