#include "Compilateur/LLVM/GenerateurFonction.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/AST_Genere.h"

#include <memory>

void VisiteurGeneralGenCode::visiter(NoeudDeclarationFonction* noeudDeclarationFonction) 
{
    GestionFonction generateurFonction(_contextGenCode,noeudDeclarationFonction,this);
    generateurFonction.declarerFonction();
}