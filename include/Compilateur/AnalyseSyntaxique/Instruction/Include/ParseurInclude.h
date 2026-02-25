#ifndef B16A7368_E6A7_4E0E_A1BF_58D81BC08234
#define B16A7368_E6A7_4E0E_A1BF_58D81BC08234

#include "Compilateur/AnalyseSyntaxique/Interfaces/IParseur.h"
#include "Compilateur/AnalyseSyntaxique/ParseurBase.h"

class ParseurInclude : public IParseur, public ParseurBase
{
private:
    llvm::BumpPtrAllocator& _arena;

public:
    ParseurInclude(llvm::BumpPtrAllocator& arena);
    ~ParseurInclude();
    INoeud* parser(std::vector<Token>& tokens, int& index) override;
};

#endif /* B16A7368_E6A7_4E0E_A1BF_58D81BC08234 */
