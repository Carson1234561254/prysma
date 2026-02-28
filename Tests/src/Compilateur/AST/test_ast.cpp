#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <llvm-18/llvm/Support/Allocator.h>
#include "Compilateur/Lexer/TokenType.h"
#include "catch.hpp"
#include "Compilateur/Lexer/Lexer.h"
#include "Compilateur/AST/ConstructeurArbreInstruction.h"
#include "Compilateur/AST/Registre/RegistreInstruction.h"
#include "Compilateur/AST/Registre/RegistreStrategieEquation.h"
#include "Compilateur/AST/Registre/RegistreType.h"
#include "Compilateur/Builder/Equation/ConstructeurEquationFlottante.h"
#include "Compilateur/AnalyseSyntaxique/ParseurType.h"
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/AST/Noeuds/Equation/NoeudOperation.h"
#include "Compilateur/AST/Noeuds/Operande/NoeudLitteral.h"
#include "Compilateur/AST/Noeuds/Condition/NoeudIf.h"
#include "Compilateur/AST/Noeuds/Boucle/NoeudWhile.h"

// Stratégies d'équation
#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieLitteral.h"
#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieIdentifiant.h"
#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieRef.h"
#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieUnRef.h"
#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieNegation.h"
#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieTableauInitialisation.h"
#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieString.h"
#include "Compilateur/AST/Noeuds/StrategieEquation/StrategieAppelFonction.h"

// Parseurs d'instructions
#include "Compilateur/AnalyseSyntaxique/Instruction/Fonction/ParseurDeclarationFonction.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Variable/ParseurAffectationVariable.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Variable/ParseurDeclarationVariable.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Variable/ParseurRefVariable.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Variable/ParseurUnRefVariable.h"
#include "Compilateur/AnalyseSyntaxique/Equation/ParseurInstructionAppel.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Fonction/ParseurRetour.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Fonction/ParseurArgFonction.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Condition/ParseurIf.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Boucle/ParseurWhile.h"
#include "Compilateur/AnalyseSyntaxique/Instruction/Include/ParseurInclude.h"

using namespace std;


struct EnvironnementAST {
    llvm::BumpPtrAllocator arena;
    std::unique_ptr<RegistreInstruction> registreInstruction;
    std::unique_ptr<RegistreStrategieEquation> registreStrategieEquation;
    std::unique_ptr<RegistreType> registreType;
    ConstructeurArbreInstruction* constructeurArbre = nullptr;
    ConstructeurEquationFlottante* constructeurEquation = nullptr;
    ParseurType* parseurType = nullptr;

    EnvironnementAST() {
        registreInstruction = std::make_unique<RegistreInstruction>();
        registreStrategieEquation = std::make_unique<RegistreStrategieEquation>();
        registreType = std::make_unique<RegistreType>();

        // Constructeur d'arbre d'instruction 
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wmismatched-new-delete"
        constructeurArbre = new (arena) ConstructeurArbreInstruction(registreInstruction.get(), arena);
        #pragma GCC diagnostic pop

        //  Strategie d'équation 
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wmismatched-new-delete"
        constructeurEquation = new (arena) ConstructeurEquationFlottante(constructeurArbre, registreStrategieEquation.get(), arena);
        #pragma GCC diagnostic pop

        parseurType = new (arena.Allocate<ParseurType>()) ParseurType(registreType.get(), constructeurEquation->recupererConstructeurArbre());

        auto* stratLitInt = new (arena.Allocate<StrategieLitteral>()) StrategieLitteral(arena);
        registreStrategieEquation->enregistrer(TOKEN_LIT_INT, stratLitInt);

        auto* stratLitFloat = new (arena.Allocate<StrategieLitteral>()) StrategieLitteral(arena);
        registreStrategieEquation->enregistrer(TOKEN_LIT_FLOAT, stratLitFloat);

        auto* stratLitBool = new (arena.Allocate<StrategieLitteral>()) StrategieLitteral(arena);
        registreStrategieEquation->enregistrer(TOKEN_LIT_BOLEEN, stratLitBool);

        auto* stratIdent = new (arena.Allocate<StrategieIdentifiant>()) StrategieIdentifiant(constructeurEquation);
        registreStrategieEquation->enregistrer(TOKEN_IDENTIFIANT, stratIdent);

        auto* stratRef = new (arena.Allocate<StrategieRef>()) StrategieRef(arena);
        registreStrategieEquation->enregistrer(TOKEN_REF, stratRef);

        auto* stratUnRef = new (arena.Allocate<StrategieUnRef>()) StrategieUnRef(arena);
        registreStrategieEquation->enregistrer(TOKEN_UNREF, stratUnRef);

        auto* stratNeg = new (arena.Allocate<StrategieNegation>()) StrategieNegation(constructeurEquation);
        registreStrategieEquation->enregistrer(TOKEN_NON, stratNeg);

        auto* stratTab = new (arena.Allocate<StrategieTableauInitialisation>()) StrategieTableauInitialisation(constructeurEquation->recupererConstructeurArbre());
        registreStrategieEquation->enregistrer(TOKEN_CROCHET_OUVERT, stratTab);

        auto* stratString = new (arena.Allocate<StrategieString>()) StrategieString(arena);
        registreStrategieEquation->enregistrer(TOKEN_GUILLEMET, stratString);

        auto* stratCall = new (arena.Allocate<StrategieAppelFonction>()) StrategieAppelFonction(constructeurEquation->recupererConstructeurArbre());
        registreStrategieEquation->enregistrer(TOKEN_CALL, stratCall);

        // Parseurs d'instructions
        auto* parsFonc = new (arena.Allocate<ParseurDeclarationFonction>()) ParseurDeclarationFonction(constructeurArbre, parseurType);
        registreInstruction->enregistrer(TOKEN_FONCTION, parsFonc);

        // Note: backend, registreVariable, registreType passés à nullptr car non utilisés au parsing
        auto* parsAff = new (arena.Allocate<ParseurAffectationVariable>()) ParseurAffectationVariable(nullptr, nullptr, nullptr, constructeurEquation->recupererConstructeurArbre());
        registreInstruction->enregistrer(TOKEN_AFF, parsAff);

        auto* parsDec = new (arena.Allocate<ParseurDeclarationVariable>()) ParseurDeclarationVariable(parseurType, constructeurEquation->recupererConstructeurArbre());
        registreInstruction->enregistrer(TOKEN_DEC, parsDec);

        auto* parsCall = new (arena.Allocate<ParseurInstructionAppel>()) ParseurInstructionAppel(constructeurEquation->recupererConstructeurArbre());
        registreInstruction->enregistrer(TOKEN_CALL, parsCall);

        auto* parsRet = new (arena.Allocate<ParseurRetour>()) ParseurRetour(constructeurEquation->recupererConstructeurArbre());
        registreInstruction->enregistrer(TOKEN_RETOUR, parsRet);

        auto* parsArg = new (arena.Allocate<ParseurArgFonction>()) ParseurArgFonction(parseurType, arena);
        registreInstruction->enregistrer(TOKEN_ARG, parsArg);

        auto* parsUnRef = new (arena.Allocate<ParseurUnRefVariable>()) ParseurUnRefVariable(arena);
        registreInstruction->enregistrer(TOKEN_UNREF, parsUnRef);

        auto* parsRefVar = new (arena.Allocate<ParseurRefVariable>()) ParseurRefVariable(arena);
        registreInstruction->enregistrer(TOKEN_REF, parsRefVar);

        auto* parsIf = new (arena.Allocate<ParseurIf>()) ParseurIf(constructeurEquation->recupererConstructeurArbre(), constructeurArbre);
        registreInstruction->enregistrer(TOKEN_SI, parsIf);

        auto* parsWhile = new (arena.Allocate<ParseurWhile>()) ParseurWhile(constructeurEquation->recupererConstructeurArbre(), constructeurArbre);
        registreInstruction->enregistrer(TOKEN_TANT_QUE, parsWhile);

        auto* parsInclude = new (arena.Allocate<ParseurInclude>()) ParseurInclude(arena);
        registreInstruction->enregistrer(TOKEN_INCLUDE, parsInclude);
    }
};

/// Construit un arbre d'équation à partir d'une string de code source.
INoeud* construireEquationDepuisString(EnvironnementAST& env, const std::string& code) {
    Lexer lexer;
    std::vector<Token> tokens = lexer.tokenizer(code);

    // Retirer le token EOF ajouté par le Lexer
    if (!tokens.empty() && tokens.back().type == TOKEN_EOF) {
        tokens.pop_back();
    }

    return env.constructeurEquation->construire(tokens);
}

/// Construit un arbre d'instructions à partir d'une string de code source.
INoeud* construireArbreDepuisString(EnvironnementAST& env, const std::string& code) {
    Lexer lexer;
    std::vector<Token> tokens = lexer.tokenizer(code);
    return env.constructeurArbre->construire(tokens);
}

// C'est un fichier de test exclusif à l'arbre syntaxique abstrait première partie du test sera de vérifier la construction de l'arbre 
// d'equation et de tester des operations de base comme l'addition, la soustraction, la multiplication et la division.

TEST_CASE("Construction Arbre Equation Simple", "[AST]")
{
    cout<< "\nTest 1 - Construction d'un arbre pour l'equation '1 + 10 * 50'" << endl;
    
    EnvironnementAST env;
    INoeud* arbre = construireEquationDepuisString(env, "1 + 10 * 50");
    
    // 1. Vérifier que l'arbre n'est pas nul
    REQUIRE(arbre != nullptr);

    // 2. Vérifier la Racine (doit être une Addition)
    auto* racineOperation = dynamic_cast<NoeudOperation*>(arbre);
    REQUIRE(racineOperation != nullptr);
    REQUIRE(racineOperation->getToken().type == TOKEN_PLUS); 

    // 3. Vérifier l'enfant gauche de l'Addition (doit être le nombre 1)
    auto* valeurGauche = dynamic_cast<NoeudLitteral*>(racineOperation->getGauche());
    REQUIRE(valeurGauche != nullptr);
    REQUIRE(valeurGauche->getToken().value == "1");

    // 4. Vérifier l'enfant droit de l'Addition (doit être une Multiplication)
    auto* operationDroite = dynamic_cast<NoeudOperation*>(racineOperation->getDroite());
    REQUIRE(operationDroite != nullptr);
    REQUIRE(operationDroite->getToken().type == TOKEN_ETOILE);

    // 5. Vérifier les enfants de la Multiplication (doivent être 10 et 50)
    auto* multiplicateurGauche = dynamic_cast<NoeudLitteral*>(operationDroite->getGauche());
    REQUIRE(multiplicateurGauche != nullptr);
    REQUIRE(multiplicateurGauche->getToken().value == "10");

    auto* multiplicateurDroit = dynamic_cast<NoeudLitteral*>(operationDroite->getDroite());
    REQUIRE(multiplicateurDroit != nullptr);
    REQUIRE(multiplicateurDroit->getToken().value == "50");
}

TEST_CASE("Constructeur Arbre equation priorite", "[AST]")
{
    cout << "\nTest 2 - Construction d'un arbre avec les regles Prysma" << endl;
    EnvironnementAST env;
    INoeud* arbre = construireEquationDepuisString(env, "40 / 2 + 10 - 5 * 3");
    
    REQUIRE(arbre != nullptr);

    // 1. racine : addition (+)
    auto* noeudAddition = dynamic_cast<NoeudOperation*>(arbre);
    REQUIRE(noeudAddition != nullptr);
    REQUIRE(noeudAddition->getToken().type == TOKEN_PLUS); // 6 == 6 !

    // 2. branche gauche : division (40 / 2)
    auto* noeudDivision = dynamic_cast<NoeudOperation*>(noeudAddition->getGauche());
    REQUIRE(noeudDivision != nullptr);
    REQUIRE(noeudDivision->getToken().type == TOKEN_SLASH);

    auto* noeudLitteral40 = dynamic_cast<NoeudLitteral*>(noeudDivision->getGauche());
    REQUIRE(noeudLitteral40 != nullptr);
    REQUIRE(noeudLitteral40->getToken().value == "40");

    auto* noeudLitteral2 = dynamic_cast<NoeudLitteral*>(noeudDivision->getDroite());
    REQUIRE(noeudLitteral2 != nullptr);
    REQUIRE(noeudLitteral2->getToken().value == "2");

    // 3. branche droite : soustraction (10 - 5 * 3)
    auto* noeudSoustraction = dynamic_cast<NoeudOperation*>(noeudAddition->getDroite());
    REQUIRE(noeudSoustraction != nullptr);
    REQUIRE(noeudSoustraction->getToken().type == TOKEN_MOINS);

    auto* noeudLitteral10 = dynamic_cast<NoeudLitteral*>(noeudSoustraction->getGauche());
    REQUIRE(noeudLitteral10 != nullptr);
    REQUIRE(noeudLitteral10->getToken().value == "10");

    // 4. branche droite de la soustraction : multiplication (5 * 3)
    auto* noeudMultiplication = dynamic_cast<NoeudOperation*>(noeudSoustraction->getDroite());
    REQUIRE(noeudMultiplication != nullptr);
    REQUIRE(noeudMultiplication->getToken().type == TOKEN_ETOILE);

    auto* noeudLitteral5 = dynamic_cast<NoeudLitteral*>(noeudMultiplication->getGauche());
    REQUIRE(noeudLitteral5 != nullptr);
    REQUIRE(noeudLitteral5->getToken().value == "5");

    auto* noeudLitteral3 = dynamic_cast<NoeudLitteral*>(noeudMultiplication->getDroite());
    REQUIRE(noeudLitteral3 != nullptr);
    REQUIRE(noeudLitteral3->getToken().value == "3");
}

TEST_CASE("Constructeur Arbre equation profondeur parenthèse", "[AST]")
{
    cout << "\nTest 3 - Construction d'un arbre avec des parenthèses" << endl;
    EnvironnementAST env;
    INoeud* arbre = construireEquationDepuisString(env, "(((40/2 +10)+ 5 * 3)+10)");

    // 1. racine : addition (+)
    auto* noeudAddition1 = dynamic_cast<NoeudOperation*>(arbre);
    REQUIRE(noeudAddition1 != nullptr);
    REQUIRE(noeudAddition1->getToken().type == TOKEN_PLUS);

    auto* litteral10_1_droite = dynamic_cast<NoeudLitteral*>(noeudAddition1->getDroite());
    REQUIRE(litteral10_1_droite != nullptr);
    REQUIRE(litteral10_1_droite->getToken().value == "10");

    auto* noeudAdditionGauche = dynamic_cast<NoeudOperation*>(noeudAddition1->getGauche());
    REQUIRE(noeudAdditionGauche != nullptr);
    REQUIRE(noeudAdditionGauche->getToken().type == TOKEN_PLUS);

    // 2. branche gauche de la racine : addition ((40/2 +10) + 5 * 3)

    // 2a. droite de noeudAdditionGauche : multiplication (5 * 3)
    auto* noeudMultiplication = dynamic_cast<NoeudOperation*>(noeudAdditionGauche->getDroite());
    REQUIRE(noeudMultiplication != nullptr);
    REQUIRE(noeudMultiplication->getToken().type == TOKEN_ETOILE);

    auto* litteral5 = dynamic_cast<NoeudLitteral*>(noeudMultiplication->getGauche());
    REQUIRE(litteral5 != nullptr);
    REQUIRE(litteral5->getToken().value == "5");

    auto* litteral3 = dynamic_cast<NoeudLitteral*>(noeudMultiplication->getDroite());
    REQUIRE(litteral3 != nullptr);
    REQUIRE(litteral3->getToken().value == "3");

    // 2b. gauche de noeudAdditionGauche : addition (40/2 + 10)
    auto* noeudAddition2 = dynamic_cast<NoeudOperation*>(noeudAdditionGauche->getGauche());
    REQUIRE(noeudAddition2 != nullptr);
    REQUIRE(noeudAddition2->getToken().type == TOKEN_PLUS);

    auto* litteral10_2 = dynamic_cast<NoeudLitteral*>(noeudAddition2->getDroite());
    REQUIRE(litteral10_2 != nullptr);
    REQUIRE(litteral10_2->getToken().value == "10");

    // 2c. gauche de noeudAddition2 : division (40 / 2)
    auto* noeudDivision = dynamic_cast<NoeudOperation*>(noeudAddition2->getGauche());
    REQUIRE(noeudDivision != nullptr);
    REQUIRE(noeudDivision->getToken().type == TOKEN_SLASH);

    auto* litteral40 = dynamic_cast<NoeudLitteral*>(noeudDivision->getGauche());
    REQUIRE(litteral40 != nullptr);
    REQUIRE(litteral40->getToken().value == "40");

    auto* litteral2 = dynamic_cast<NoeudLitteral*>(noeudDivision->getDroite());
    REQUIRE(litteral2 != nullptr);
    REQUIRE(litteral2->getToken().value == "2");
}


// Début des tests pour l'arbre d'instruction 

// Test de branchement if simple avec else
TEST_CASE("Construction Arbre If simple avec else", "[AST][Branch]")
{
    cout << "\nTest 4 - Arbre if/else simple" << endl;
    EnvironnementAST env;

    // Code Prysma : if avec condition et deux branches
    INoeud* arbre = construireArbreDepuisString(env,
        "if (a > 5) { aff x = 1; } else { aff x = 2; }"
    );

    REQUIRE(arbre != nullptr);

    // 1. Racine = NoeudInstruction qui contient le if
    auto* racine = dynamic_cast<NoeudInstruction*>(arbre);
    REQUIRE(racine != nullptr);
    REQUIRE(racine->getEnfants().size() == 1);

    // 2. Premier enfant = NoeudIf
    auto* noeudIf = dynamic_cast<NoeudIf*>(racine->getEnfants()[0]);
    REQUIRE(noeudIf != nullptr);

    // 3. Condition pas nulle
    REQUIRE(noeudIf->getNoeudCondition() != nullptr);

    // 4. Vérifier condition : opération '>'
    auto* condition = dynamic_cast<NoeudOperation*>(noeudIf->getNoeudCondition());
    REQUIRE(condition != nullptr);
    REQUIRE(condition->getToken().type == TOKEN_PLUS_GRAND);

    // 5. Bloc if existe et contient 1 instruction
    auto* blocIf = dynamic_cast<NoeudInstruction*>(noeudIf->getNoeudBlocIf());
    REQUIRE(blocIf != nullptr);
    REQUIRE(blocIf->getEnfants().size() == 1);

    // 6. Bloc else existe et contient 1 instruction
    auto* blocElse = dynamic_cast<NoeudInstruction*>(noeudIf->getNoeudBlocElse());
    REQUIRE(blocElse != nullptr);
    REQUIRE(blocElse->getEnfants().size() == 1);

    // 7. Bloc endif existe (noeud de sortie)
    REQUIRE(noeudIf->getNoeudBlocEndif() != nullptr);
}

// Test if sans else
TEST_CASE("Construction Arbre If sans else", "[AST][Branch]")
{
    cout << "\nTest 5 - Arbre if sans else" << endl;
    EnvironnementAST env;

    INoeud* arbre = construireArbreDepuisString(env,
        "if (a == 10) { aff y = 42; }"
    );

    REQUIRE(arbre != nullptr);

    auto* racine = dynamic_cast<NoeudInstruction*>(arbre);
    REQUIRE(racine != nullptr);

    // 1. NoeudIf
    auto* noeudIf = dynamic_cast<NoeudIf*>(racine->getEnfants()[0]);
    REQUIRE(noeudIf != nullptr);

    // 2. Condition == 
    auto* condition = dynamic_cast<NoeudOperation*>(noeudIf->getNoeudCondition());
    REQUIRE(condition != nullptr);
    REQUIRE(condition->getToken().type == TOKEN_EGAL_EGAL);

    // 3. Bloc if a 1 enfant
    auto* blocIf = dynamic_cast<NoeudInstruction*>(noeudIf->getNoeudBlocIf());
    REQUIRE(blocIf != nullptr);
    REQUIRE(blocIf->getEnfants().size() == 1);

    // 4. Pas de else
    REQUIRE(noeudIf->getNoeudBlocElse() == nullptr);

    // 5. Endif existe quand même
    REQUIRE(noeudIf->getNoeudBlocEndif() != nullptr);
}

// Test if avec condition logique && 
TEST_CASE("Construction Arbre If condition logique ET", "[AST][Branch]")
{
    cout << "\nTest 6 - Arbre if avec &&" << endl;
    EnvironnementAST env;

    INoeud* arbre = construireArbreDepuisString(env,
        "if (a > 1 && b < 10) { aff z = 0; }"
    );

    REQUIRE(arbre != nullptr);

    auto* racine = dynamic_cast<NoeudInstruction*>(arbre);
    REQUIRE(racine != nullptr);

    auto* noeudIf = dynamic_cast<NoeudIf*>(racine->getEnfants()[0]);
    REQUIRE(noeudIf != nullptr);

    // Condition racine = &&
    auto* condition = dynamic_cast<NoeudOperation*>(noeudIf->getNoeudCondition());
    REQUIRE(condition != nullptr);
    REQUIRE(condition->getToken().type == TOKEN_ET);

    // Gauche du && = '>'
    auto* gauche = dynamic_cast<NoeudOperation*>(condition->getGauche());
    REQUIRE(gauche != nullptr);
    REQUIRE(gauche->getToken().type == TOKEN_PLUS_GRAND);

    // Droite du && = '<'
    auto* droite = dynamic_cast<NoeudOperation*>(condition->getDroite());
    REQUIRE(droite != nullptr);
    REQUIRE(droite->getToken().type == TOKEN_PLUS_PETIT);
}

// Test while simple
TEST_CASE("Construction Arbre While simple", "[AST][Branch]")
{
    cout << "\nTest 7 - Arbre while simple" << endl;
    EnvironnementAST env;

    INoeud* arbre = construireArbreDepuisString(env,
        "while (i < 10) { aff i = i + 1; }"
    );

    REQUIRE(arbre != nullptr);

    auto* racine = dynamic_cast<NoeudInstruction*>(arbre);
    REQUIRE(racine != nullptr);
    REQUIRE(racine->getEnfants().size() == 1);

    // 1. NoeudWhile
    auto* noeudWhile = dynamic_cast<NoeudWhile*>(racine->getEnfants()[0]);
    REQUIRE(noeudWhile != nullptr);

    // 2. Condition '<'
    auto* condition = dynamic_cast<NoeudOperation*>(noeudWhile->getNoeudCondition());
    REQUIRE(condition != nullptr);
    REQUIRE(condition->getToken().type == TOKEN_PLUS_PETIT);

    // 3. Bloc while a 1 instruction
    auto* blocWhile = dynamic_cast<NoeudInstruction*>(noeudWhile->getNoeudBlocWhile());
    REQUIRE(blocWhile != nullptr);
    REQUIRE(blocWhile->getEnfants().size() == 1);

    // 4. Bloc fin while existe
    REQUIRE(noeudWhile->getNoeudBlocFinWhile() != nullptr);
}

// Test while avec condition logique ||
TEST_CASE("Construction Arbre While condition OU", "[AST][Branch]")
{
    cout << "\nTest 8 - Arbre while avec ||" << endl;
    EnvironnementAST env;

    INoeud* arbre = construireArbreDepuisString(env,
        "while (x == 0 || y == 0) { aff x = 1; }"
    );

    REQUIRE(arbre != nullptr);

    auto* racine = dynamic_cast<NoeudInstruction*>(arbre);
    REQUIRE(racine != nullptr);

    auto* noeudWhile = dynamic_cast<NoeudWhile*>(racine->getEnfants()[0]);
    REQUIRE(noeudWhile != nullptr);

    // Condition racine = ||
    auto* condition = dynamic_cast<NoeudOperation*>(noeudWhile->getNoeudCondition());
    REQUIRE(condition != nullptr);
    REQUIRE(condition->getToken().type == TOKEN_OU);

    // Gauche du || = '=='
    auto* gauche = dynamic_cast<NoeudOperation*>(condition->getGauche());
    REQUIRE(gauche != nullptr);
    REQUIRE(gauche->getToken().type == TOKEN_EGAL_EGAL);

    // Droite du || = '=='
    auto* droite = dynamic_cast<NoeudOperation*>(condition->getDroite());
    REQUIRE(droite != nullptr);
    REQUIRE(droite->getToken().type == TOKEN_EGAL_EGAL);
}

// Test while avec plusieurs instructions dans le corps
TEST_CASE("Construction Arbre While plusieurs instructions", "[AST][Branch]")
{
    cout << "\nTest 9 - Arbre while avec plusieurs instructions" << endl;
    EnvironnementAST env;

    INoeud* arbre = construireArbreDepuisString(env,
        "while (i < 5) { aff a = 0; aff i = i + 1; }"
    );

    REQUIRE(arbre != nullptr);

    auto* racine = dynamic_cast<NoeudInstruction*>(arbre);
    REQUIRE(racine != nullptr);

    auto* noeudWhile = dynamic_cast<NoeudWhile*>(racine->getEnfants()[0]);
    REQUIRE(noeudWhile != nullptr);

    // Bloc while contient 2 instructions (aff + aff)
    auto* blocWhile = dynamic_cast<NoeudInstruction*>(noeudWhile->getNoeudBlocWhile());
    REQUIRE(blocWhile != nullptr);
    REQUIRE(blocWhile->getEnfants().size() == 2);
}