#include "Compilateur/AnalyseSyntaxique/Instruction/Include/ParseurInclude.h"
#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/Lexer/TokenType.h"

ParseurInclude::ParseurInclude(llvm::BumpPtrAllocator& arena) : _arena(arena)
{
}

ParseurInclude::~ParseurInclude()
{
}

// Exemple : include "path"
INoeud* ParseurInclude::parser(std::vector<Token>& tokens, int& index)
{
    consommer(tokens,index,TOKEN_INCLUDE, "Erreur : Instruction include doit commencer par le mot-clé 'include'");
    consommer(tokens,index,TOKEN_GUILLEMET, "Erreur : Instruction include doit être suivie d'une chaîne de caractères entre guillemets");
    Token tokenPath = consommer(tokens,index,TOKEN_IDENTIFIANT, "Erreur : Instruction include doit contenir un chemin de fichier");
    consommer(tokens,index,TOKEN_GUILLEMET, "Erreur : Instruction include doit être suivie d'une chaîne de caractères entre guillemets");
    consommer(tokens,index,TOKEN_POINT_VIRGULE, "Erreur : Instruction include doit se terminer par un point-virgule");

    return new (_arena.Allocate<NoeudInclude>()) NoeudInclude(tokenPath.value);
}