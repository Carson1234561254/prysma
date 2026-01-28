#ifndef BDC39C44_6952_4793_8198_C083B106A089
#define BDC39C44_6952_4793_8198_C083B106A089

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Lexer/Lexer.h"

class ConstructeurArbreInstruction
{
private: 
    int avancerFinInstruction(int indexActuel);
    std::vector<INoeud> obtenirTouteInstructionEnfant(const std::vector<Token>& tokensIntervalle);
    

public: 

    ConstructeurArbreInstruction();
    ~ConstructeurArbreInstruction();

    INoeud construireArbreSyntaxique(const std::vector<Token>& tokens);



};

#endif /* BDC39C44_6952_4793_8198_C083B106A089 */
