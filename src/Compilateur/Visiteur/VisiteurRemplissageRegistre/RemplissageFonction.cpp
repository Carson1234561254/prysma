#include "Compilateur/AST/Registre/RegistreFonction.h"
#include "Compilateur/Visiteur/VisiteurRemplissageRegistre/VisiteurRemplissageRegistre.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudDeclarationFonction.h"

void VisiteurRemplissageRegistre::visiter(NoeudDeclarationFonction* noeudDeclarationFonction)
{
    IType* typeRetour = noeudDeclarationFonction->getTypeRetour();
    Token token; 
    token.value = noeudDeclarationFonction->getNom();
    
    SymboleFonction symboleFonction(nullptr, typeRetour, noeudDeclarationFonction);
}