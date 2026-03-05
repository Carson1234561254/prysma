#include "Compilateur/AnalyseSyntaxique/Instruction/New/ParseurNew.h"
#include "Compilateur/AST/Noeuds/New/NoeudNew.h"
#include "Compilateur/Lexer/Lexer.h"
#include "Compilateur/Lexer/TokenCategories.h"
#include <cstddef>
#include <stdexcept>


ParseurNew::ParseurNew(llvm::BumpPtrAllocator& arena)  : _arena(arena)
{}

ParseurNew::~ParseurNew()
{}

// exemple : dec ptr nouveauPointeurInt = new int64; 

INoeud* ParseurNew::parser(std::vector<Token>& tokens, int& index)
{
    consommer(tokens,index,TOKEN_NEW,"Erreur: le token new est attendu ! ");
    Token nomType = tokens[static_cast<size_t>(index)];

    if(estType(tokens[static_cast<size_t>(index)].type))
    {

        index ++;
    }
    else {
        throw std::runtime_error("Erreur: aucun type valide pour l'objet créer avec le new! ");
    }

    return new (_arena.Allocate(sizeof(NoeudNew),alignof(NoeudNew))) NoeudNew(nomType);
}