#include "Compilateur/AST/GestionnaireChargementVariable.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudAppelFonction.h"


void VisiteurGeneralGenCode::visiter(NoeudAppelFonction* noeudAppelFonction)
{
    
     _contextGenCode->registreArgument->vider();
    parcourirEnfant(noeudAppelFonction);
    llvm::Function* fonction = _contextGenCode->registreFonction->recuperer(noeudAppelFonction->_nomFonction.value);
    std::vector<llvm::Value*> args = *_contextGenCode->registreArgument->recuperer();
    std::vector<llvm::Value*> argsConvertieLecture; 

    GestionnaireChargementVariable gestionnaireChargementVariable(_contextGenCode->backend);

    for(size_t i = 0; i < args.size(); i++)
    {
        llvm::StringRef nom = args[i]->getName();
        std::string nomConvertieString(nom.begin(), nom.end());
        argsConvertieLecture.push_back(gestionnaireChargementVariable.chargerVariable(args[i], nomConvertieString));
    }

    _contextGenCode->valeurTemporaire = _contextGenCode->backend->getBuilder().CreateCall(fonction, argsConvertieLecture, "resultat_appel");
    
}