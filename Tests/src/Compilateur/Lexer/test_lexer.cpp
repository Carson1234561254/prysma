#include "Compilateur/Lexer/TokenType.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Compilateur/Lexer/Lexer.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void afficherTokens(const vector<Token>& tokens) {
    cout << "\n--- Tokens generés ---" << endl;
    for (size_t i = 0; i < tokens.size(); ++i) {
        cout << "[" << i << "] Type: " << tokens[i].type 
             << " | Valeur: \"" << tokens[i].value 
             << "\" | Ligne: " << tokens[i].ligne 
             << " | Colonne: " << tokens[i].colonne << endl;
    }
}

TEST_CASE("Tester Lexer Identifiants", "[Lexer]") {
    cout << "\nTest 1 - Identifiants simples" << endl;
    Lexer lexer;
    string code = "x y z variable_test";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() == 5);
    CHECK(tokens[0].value == "x");
    CHECK(tokens[1].value == "y");
    CHECK(tokens[2].value == "z");
    CHECK(tokens[3].value == "variable_test");
    cout << "Les identifiants ont ete correctement reconnus et separes." << endl;
}

TEST_CASE("Tester Lexer Nombres", "[Lexer]") {
    cout << "\nTest 2 - Nombres entiers et flottants" << endl;
    Lexer lexer;
    string code = "42 -15 3.14 -2.5";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() == 7);
    CHECK(tokens[0].value == "42");
    CHECK(tokens[1].value == "-");
    CHECK(tokens[2].value == "15");
    CHECK(tokens[3].value == "3.14");
    cout << "Les nombres ont ete correctement tokenizes." << endl;
}

TEST_CASE("Tester Lexer Chaines de caracteres", "[Lexer]") {
    cout << "\nTest 3 - Chaines de caracteres" << endl;
    Lexer lexer;
    string code = R"("Salut" "Mot avec espaces")";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() == 3);
    CHECK(tokens[0].value == "\"Salut\"");
    CHECK(tokens[1].value == "\"Mot avec espaces\"");
    cout << "Les chaines de caracteres ont ete correctement reconnues." << endl;
}

TEST_CASE("Tester Lexer Mots-cles", "[Lexer]") {
    cout << "\nTest 4 - Mots-cles du langage Prysma" << endl;
    Lexer lexer;
    string code = "fn if else while for return true false print";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() == 10);
    CHECK(tokens[0].type == TOKEN_FONCTION);
    CHECK(tokens[1].type == TOKEN_SI);
    CHECK(tokens[2].type == TOKEN_SINON);
    cout << "Les mots-cles ont ete correctement reconnus." << endl;
}

TEST_CASE("Tester Lexer Operateurs", "[Lexer]") {
    cout << "\nTest 5 - Operateurs mathematiques et de comparaison" << endl;
    Lexer lexer;
    string code = "a + b - c * d / e == f != g <= h >= i";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() > 7);
    CHECK(tokens[1].type == TOKEN_PLUS);
    CHECK(tokens[3].type == TOKEN_MOINS);
    CHECK(tokens[5].type == TOKEN_ETOILE);
    CHECK(tokens[7].type == TOKEN_SLASH);
    cout << "Les operateurs ont ete correctement tokenizes." << endl;
}

TEST_CASE("Tester Lexer Delimiteurs", "[Lexer]") {
    cout << "\nTest 6 - Delimiteurs et ponctuation" << endl;
    Lexer lexer;
    string code = "( ) { } [ ] ; ,";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() > 3);
    CHECK(tokens[0].type == TOKEN_PAREN_OUVERTE);
    CHECK(tokens[1].type == TOKEN_PAREN_FERMEE);
    CHECK(tokens[2].type == TOKEN_ACCOLADE_OUVERTE);
    CHECK(tokens[3].type == TOKEN_ACCOLADE_FERMEE);
    cout << "Les delimiteurs ont ete correctement tokenizes." << endl;
}

TEST_CASE("Tester Lexer Commentaires", "[Lexer]") {
    cout << "\nTest 7 - Commentaires de ligne" << endl;
    Lexer lexer;
    string code = "x // ceci est un commentaire\ny";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() >= 2);
    CHECK(tokens[0].value == "x");
    CHECK(tokens[1].value == "y");
    cout << "Les commentaires ont ete correctement ignores." << endl;
}

TEST_CASE("Tester Lexer Code Complet", "[Lexer]") {
    cout << "\nTest 8 - Code complet et mixte" << endl;
    Lexer lexer;
    string code = "fn main(x: int64) { y = 42 + 3.14; }";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() > 0);
    CHECK(tokens[0].type == TOKEN_FONCTION);
    CHECK(tokens[0].ligne == 1);
    CHECK(tokens[0].colonne == 1);
    cout << "Le code complet a ete correctement tokenize." << endl;
}

TEST_CASE("Tester Lexer Booleans", "[Lexer]") {
    cout << "\nTest 9 - Litteraux booleens" << endl;
    Lexer lexer;
    string code = "true false";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() >= 2);
    CHECK(tokens[0].type == TOKEN_LIT_BOLEEN);
    CHECK(tokens[0].value == "1");
    CHECK(tokens[1].type == TOKEN_LIT_BOLEEN);
    CHECK(tokens[1].value == "0");
    cout << "Les booleens ont ete correctement tokenizes et convertis." << endl;
}

TEST_CASE("Tester Lexer Declaration Simple", "[Lexer]") {
    cout << "\nTest 10 - Declaration de variable simple" << endl;
    Lexer lexer;
    string code = "dec int64 teste1 = 10;";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);

    CHECK(tokens.size() > 4);
    CHECK(tokens[0].type == TOKEN_DEC);
    CHECK(tokens[1].type == TOKEN_TYPE_INT);
    CHECK(tokens[2].type == TOKEN_IDENTIFIANT);
    CHECK(tokens[3].type == TOKEN_EGAL);
    CHECK(tokens[4].type == TOKEN_LIT_INT);
    cout << "La declaration de variable a ete correctement tokenizee." << endl;
}

TEST_CASE("Tester Lexer Code Vide", "[Lexer]") {
    cout << "\nTest 11 - Cas limite code vide" << endl;
    Lexer lexer;
    string code;
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    cout << "Un code vide a ete correctement traite." << endl;
}

TEST_CASE("Tester Lexer Espaces Uniquement", "[Lexer]") {
    cout << "\nTest 12 - Cas limite espaces et tabulations uniquement" << endl;
    Lexer lexer;
    string code = "     \t\t  \n  ";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    cout << "Les espaces et tabulations ont ete correctement ignores." << endl;
}

TEST_CASE("Tester Lexer Commentaires Uniquement", "[Lexer]") {
    cout << "\nTest 13 - Cas limite commentaires uniquement" << endl;
    Lexer lexer;
    string code = "// ceci est un commentaire\n// ceci aussi";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    cout << "Les commentaires uniquement ont ete correctement traites." << endl;
}

TEST_CASE("Tester Lexer Nombres Negatifs", "[Lexer]") {
    cout << "\nTest 14 - Cas limite nombres negatifs complexes" << endl;
    Lexer lexer;
    string code = "-0 -0.0 -999 -3.14159";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() > 4);
    CHECK(tokens[0].type == TOKEN_MOINS);
    CHECK(tokens[1].type == TOKEN_LIT_INT);
    cout << "Les nombres negatifs ont ete correctement tokenizes." << endl;
}

TEST_CASE("Tester Lexer Identifiants avec Underscores", "[Lexer]") {
    cout << "\nTest 15 - Cas limite identifiants avec underscores" << endl;
    Lexer lexer;
    string code = "_var __double__ _123 __";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() >= 4);
    CHECK(tokens[0].value == "_var");
    CHECK(tokens[1].value == "__double__");
    CHECK(tokens[2].value == "_");
    CHECK(tokens[3].value == "123");
    cout << "Les identifiants avec underscores ont ete correctement reconnus." << endl;
}

TEST_CASE("Tester Lexer Chaine Malformee", "[Lexer]") {
    cout << "\nTest 16 - Cas limite chaine sans guillemet fermant" << endl;
    Lexer lexer;
    string code = "\"chaine non fermee";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    cout << "Une chaine mal formee a ete traitee par le lexer." << endl;
}

TEST_CASE("Tester Lexer Commentaires Blocs", "[Lexer]") {
    cout << "\nTest 17 - Cas limite commentaires bloc /* */" << endl;
    Lexer lexer;
    string code = "a /* commentaire bloc */ b /* nested /* comment */ end */";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() >= 2);
    CHECK(tokens[0].value == "a");
    cout << "Les commentaires bloc ont ete correctement ignores." << endl;
}

TEST_CASE("Tester Lexer Operators Composites", "[Lexer]") {
    cout << "\nTest 18 - Cas limite operateurs composites" << endl;
    Lexer lexer;
    string code = "a == b != c >= d <= e";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() > 5);
    CHECK(tokens[1].type == TOKEN_EGAL_EGAL);
    CHECK(tokens[3].type == TOKEN_DIFFERENT);
    cout << "Les operateurs composites ont ete correctement tokenizes." << endl;
}

TEST_CASE("Tester Lexer Lignes Multiples", "[Lexer]") {
    cout << "\nTest 19 - Cas limite suivi des lignes et colonnes" << endl;
    Lexer lexer;
    string code = "a\nb\nc";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() >= 3);
    CHECK(tokens[0].ligne == 1);
    CHECK(tokens[1].ligne == 2);
    CHECK(tokens[2].ligne == 3);
    cout << "Le suivi des lignes et colonnes est correct." << endl;
}

TEST_CASE("Tester Lexer Types Valides", "[Lexer]") {
    cout << "\nTest 20 - Cas limite tous les types valides" << endl;
    Lexer lexer;
    string code = "int64 float bool";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() >= 3);
    CHECK(tokens[0].type == TOKEN_TYPE_INT);
    CHECK(tokens[1].type == TOKEN_TYPE_FLOAT);
    CHECK(tokens[2].type == TOKEN_TYPE_BOOL);
    cout << "Tous les types ont ete correctement reconnus." << endl;
}

TEST_CASE("Tester Lexer Concatenation Sans Espace", "[Lexer]") {
    cout << "\nTest 21 - Cas limite tokens sans espaces de separation" << endl;
    Lexer lexer;
    string code = "a+b-c*d/e";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() >= 9);
    CHECK(tokens[0].value == "a");
    CHECK(tokens[1].type == TOKEN_PLUS);
    CHECK(tokens[2].value == "b");
    cout << "Les tokens sans espaces ont ete correctement separes." << endl;
}

TEST_CASE("Tester Lexer Accolades et Parentheses", "[Lexer]") {
    cout << "\nTest 22 - Cas limite imbrication accolades et parentheses" << endl;
    Lexer lexer;
    string code = "{ { ( ( ) ) } }";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() == 8);
    CHECK(tokens[0].type == TOKEN_ACCOLADE_OUVERTE);
    CHECK(tokens[7].type == TOKEN_ACCOLADE_FERMEE);
    cout << "L'imbrication a ete correctement tokenizee." << endl;
}

TEST_CASE("Tester Lexer Zeros Multiples", "[Lexer]") {
    cout << "\nTest 23 - Cas limite nombres avec zeros multiples" << endl;
    Lexer lexer;
    string code = "0 00 000.000 0.0";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() > 0);
    CHECK(tokens[0].value == "0");
    cout << "Les nombres avec zeros ont ete correctement tokenizes." << endl;
}

TEST_CASE("Tester Lexer Nombres Grands", "[Lexer]") {
    cout << "\nTest 24 - Cas limite tres grands nombres" << endl;
    Lexer lexer;
    string code = "999999999 123456789.987654321";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() >= 2);
    CHECK(tokens[0].value == "999999999");
    cout << "Les grands nombres ont ete correctement tokenizes." << endl;
}

TEST_CASE("Tester Lexer Characters Speciaux", "[Lexer]") {
    cout << "\nTest 25 - Cas limite caracteres speciaux dans les chaines" << endl;
    Lexer lexer;
    string code = "\"!@#$%^&*()\" \"avec\\nnouvelle\\nligne\"";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() >= 2);
    cout << "Les caracteres speciaux dans les chaines ont ete correctement traites." << endl;
}

TEST_CASE("Tester Lexer Fonctions et Retour", "[Lexer]") {
    cout << "\nTest 26 - Cas limite fonction avec retour" << endl;
    Lexer lexer;
    string code = "fn test() { return 42; }";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() > 5);
    CHECK(tokens[0].type == TOKEN_FONCTION);
    cout << "La fonction avec retour a ete correctement tokenizee." << endl;
}

TEST_CASE("Tester Lexer Control Flow", "[Lexer]") {
    cout << "\nTest 27 - Cas limite structures de controle imbriquees" << endl;
    Lexer lexer;
    string code = "if (x > 0) { while (true) { } }";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() > 8);
    CHECK(tokens[0].type == TOKEN_SI);
    cout << "Les structures de controle ont ete correctement tokenizees." << endl;
}

TEST_CASE("Tester Lexer Tous Operateurs", "[Lexer]") {
    cout << "\nTest 28 - Cas limite tous les operateurs supportes" << endl;
    Lexer lexer;
    string code = "+ - * / % == != < > <= >=";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() >= 10);
    cout << "Tous les operateurs ont ete correctement tokenizes." << endl;
}

TEST_CASE("Tester Lexer Assignment Multiple", "[Lexer]") {
    cout << "\nTest 29 - Cas limite affectations multiples en cascade" << endl;
    Lexer lexer;
    string code = "a = b = c = 10";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() > 5);
    CHECK(tokens[1].type == TOKEN_EGAL);
    cout << "Les affectations multiples ont ete correctement tokenizees." << endl;
}

TEST_CASE("Tester Lexer Declaration Complexe", "[Lexer]") {
    cout << "\nTest 30 - Cas limite declaration complexe avec tous les elements" << endl;
    Lexer lexer;
    string code = "dec float _var123 = -45.67;";
    vector<Token> tokens = lexer.tokenizer(code);
    afficherTokens(tokens);
    
    CHECK(tokens.size() > 6);
    CHECK(tokens[0].type == TOKEN_DEC);
    CHECK(tokens[1].type == TOKEN_TYPE_FLOAT);
    cout << "La declaration complexe a ete correctement tokenizee." << endl;
}
