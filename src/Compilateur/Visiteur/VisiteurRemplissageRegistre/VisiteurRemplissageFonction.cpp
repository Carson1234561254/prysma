#include "Compilateur/Visiteur/VisiteurRemplissageRegistre/VisiteurRemplissageRegistre.h"
#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/AST/Registre/RegistreFonction.h"
#include "Compilateur/AST/Registre/Types/IType.h"

void VisiteurRemplissageRegistre::visiter(NoeudDeclarationFonction* noeudDeclarationFonction)
{
    IType* typeRetour = noeudDeclarationFonction->getTypeRetour();
    std::string nomFonction = noeudDeclarationFonction->getNom();
    
    auto symboleFonction = std::make_unique<SymboleFonctionGlobale>();
    symboleFonction->typeRetour = typeRetour;
    symboleFonction->noeud = noeudDeclarationFonction;

    _contextGenCode->registreFonctionGlobale->enregistrer(nomFonction, std::move(symboleFonction));
}