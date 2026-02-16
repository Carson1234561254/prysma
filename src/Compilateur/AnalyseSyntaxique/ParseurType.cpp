#include "Compilateur/AnalyseSyntaxique/ParseurType.h"
#include "Compilateur/AST/Registre/Types/TypeSimple.h"
#include "Compilateur/AST/Registre/Types/TypeTableau.h"
#include "Compilateur/Lexer/TokenCategories.h"
#include "Compilateur/GestionnaireErreur.h"

ParseurType::ParseurType(std::shared_ptr<RegistreType> registreType)
    : _registreType(std::move(registreType))
{
}

std::shared_ptr<IType> ParseurType::parser(std::vector<Token>& tokens, int& index)
{
    // Vérifier que le token courant est un type valide
    if (TokenCategories::TYPES.find(tokens[index].type) == TokenCategories::TYPES.end()) {
        throw ErreurCompilation("Erreur : type attendu", tokens[index].ligne, tokens[index].colonne);
    }

    // Récupérer le type LLVM depuis le registre et créer un TypeSimple
    llvm::Type* typeLLVM = _registreType->recuperer(tokens[index].type);
    std::shared_ptr<IType> type = std::make_shared<TypeSimple>(typeLLVM);
    index++;

    while (index < static_cast<int>(tokens.size()) && tokens[index].type == TOKEN_CROCHET_OUVERT) {
        index++; // consommer '['

        if (index >= static_cast<int>(tokens.size()) || tokens[index].type != TOKEN_LIT_INT) {
            throw ErreurCompilation("Erreur : taille du tableau attendue (entier)", tokens[index].ligne, tokens[index].colonne);
        }
        int taille = std::stoi(tokens[index].value);
        index++; // consommer le littéral entier

        // Consommer ']'
        if (index >= static_cast<int>(tokens.size()) || tokens[index].type != TOKEN_CROCHET_FERME) {
            throw ErreurCompilation("Erreur : ']' attendu", tokens[index].ligne, tokens[index].colonne);
        }
        index++; // consommer ']'

        type = std::make_shared<TypeTableau>(type, taille);
    }

    return type;
}
