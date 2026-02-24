#include "Compilateur/Visiteur/VisiteurRemplissageRegistre/VisiteurRemplissageRegistre.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudDeclarationFonction.h"
#include "Compilateur/AST/Registre/RegistreFonction.h"
#include "Compilateur/AST/Registre/Types/IType.h"
#include "Compilateur/Lexer/Lexer.h"

void VisiteurRemplissageRegistre::visiter(NoeudDeclarationFonction* noeudDeclarationFonction)
{
    IType* typeRetour = noeudDeclarationFonction->getTypeRetour();
    Token token; 
    token.value = noeudDeclarationFonction->getNom();
    
    _contextGenCode->registreFonction->enregistrer(token.value, SymboleFonction(nullptr, typeRetour, noeudDeclarationFonction));
}