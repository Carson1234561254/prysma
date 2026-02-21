#include "Compilateur/LLVM/GenerateurFonction.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudAppelFonction.h"
#include "Compilateur/AST/Registre/RegistreFonction.h"

void VisiteurGeneralGenCode::visiter(NoeudAppelFonction* noeudAppelFonction)
{
    std::string nomFonction = noeudAppelFonction->getNomFonction().value;
    SymboleFonction symbole = _contextGenCode->registreFonction->recuperer(nomFonction);
    
    GestionFonction gestionnaireFonction(_contextGenCode, symbole.noeud, this);
    gestionnaireFonction.genererAppelFonction(noeudAppelFonction);
}