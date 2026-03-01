#include "catch.hpp"
#include "Compilateur/AST/Registre/RegistreFonction.h"
#include <string>
#include <memory>

using namespace std;

TEST_CASE("Registre global vide existe retourne false", "[RegistreGlobal]") {
    RegistreFonctionGlobale registre;

    CHECK_FALSE(registre.existe("nimportequoi"));
}

TEST_CASE("Registre global vide recuperer lance exception", "[RegistreGlobal]") {
    RegistreFonctionGlobale registre;

    CHECK_THROWS_AS(registre.recuperer("absent"), std::invalid_argument);
}

TEST_CASE("Registre global ecraser ne change pas le nombre de cles", "[RegistreGlobal]") {
    RegistreFonctionGlobale registre;

    registre.enregistrer("fn", make_unique<SymboleFonctionGlobale>());
    registre.enregistrer("fn", make_unique<SymboleFonctionGlobale>());
    registre.enregistrer("fn", make_unique<SymboleFonctionGlobale>());

    auto cles = registre.obtenirCles();
    CHECK(cles.size() == 1);
}

TEST_CASE("Registre global cles similaires sont distinctes", "[RegistreGlobal]") {
    RegistreFonctionGlobale registre;

    registre.enregistrer("fn", make_unique<SymboleFonctionGlobale>());
    registre.enregistrer("Fn", make_unique<SymboleFonctionGlobale>());
    registre.enregistrer("FN", make_unique<SymboleFonctionGlobale>());

    CHECK(registre.obtenirCles().size() == 3);
    CHECK(registre.existe("fn"));
    CHECK(registre.existe("Fn"));
    CHECK(registre.existe("FN"));
}

TEST_CASE("Registre global message erreur contient la cle", "[RegistreGlobal]") {
    RegistreFonctionGlobale registre;

    try {
        registre.recuperer("fantome");
        FAIL("Exception attendue");
    } catch (const std::invalid_argument& e) {
        string msg = e.what();
        CHECK(msg.find("fantome") != string::npos);
    }
}

//  cas non fonctionnel sad test pour verifier que le registre global ne plante pas et termine correctement avec des acces concurrents a la meme cle

TEST_CASE("RegistreGlobal - Acces concurrent a la meme cle ne plante pas", "[RegistreGlobal][SadTest]") {
    RegistreFonctionGlobale registre;

    registre.enregistrer("fn", make_unique<SymboleFonctionGlobale>());

    CHECK_NOTHROW(registre.recuperer("fn"));
    CHECK_NOTHROW(registre.recuperer("fn"));
    CHECK_NOTHROW(registre.recuperer("fn"));

    registre.enregistrer("fn", make_unique<SymboleFonctionGlobale>());
    CHECK_NOTHROW(registre.recuperer("fn"));

    CHECK(registre.existe("fn"));
    auto cles = registre.obtenirCles();
    CHECK(cles.size() == 1);
    
    CHECK_THROWS_AS(registre.recuperer("cle_invalide"), std::invalid_argument);
}
