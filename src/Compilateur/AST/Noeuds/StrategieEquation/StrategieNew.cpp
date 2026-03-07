#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieNew.h"
#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/GestionnaireErreur.h"
#include "Compilateur/Lexer/TokenCategories.h"
#include "Compilateur/Lexer/TokenType.h"

StrategieNew::StrategieNew(llvm::BumpPtrAllocator& arena) : _arena(arena) {}

INoeud* StrategieNew::construire(std::vector<Token>& equation) {
    int index = 0;
    consommer(equation, index, TOKEN_NEW, "Erreur: le token 'new' est attendu");

    Token nomType = consommer(equation, index, equation[static_cast<size_t>(index)].type,
        "Erreur: aucun type valide pour l'objet créé avec 'new'");

    if (!estType(nomType.type)) {
        throw ErreurCompilation("Erreur: aucun type valide pour l'objet créé avec 'new'", nomType.ligne, nomType.colonne);
    }

    return new (_arena.Allocate(sizeof(NoeudNew), alignof(NoeudNew))) NoeudNew(nomType);
}
