#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudAppelFonction.h"


void VisiteurGeneralGenCode::visiter(NoeudAppelFonction* noeudAppelFonction)
{
    
     _contextGenCode->registreArgument->vider();
    parcourirEnfant(noeudAppelFonction);
    llvm::Function* fonction = _contextGenCode->registreFonction->recuperer(noeudAppelFonction->_nomFonction.value);
    std::vector<llvm::Value*> args = *_contextGenCode->registreArgument->recuperer();

    _contextGenCode->valeurTemporaire = _contextGenCode->backend->getBuilder().CreateCall(fonction, args, "resultat_appel");
    
}