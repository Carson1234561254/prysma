#include "Compilateur/AST/Noeuds/Fonction/NoeudAppelFonction.h"
#include "Compilateur/AST/GestionnaireChargementVariable.h"
#include "Compilateur/LLVM/LLVMBackend.h"
#include "Compilateur/AST/Registre/RegistreArgument.h"


NoeudAppelFonction::NoeudAppelFonction(Token nomFonction, std::shared_ptr<RegistreFonction> registreFonction,std::shared_ptr<LLVMBackend> backend, std::shared_ptr<RegistreArgument> registreArgument)
{
    _nomFonction = std::move(nomFonction);
    _registreFonction = std::move(registreFonction);
    _backend = std::move(backend);
    _registreArgument = std::move(registreArgument);
}

NoeudAppelFonction::~NoeudAppelFonction()
{}

llvm::Value* NoeudAppelFonction::genCode()
{
    _registreArgument->vider();
    executerEnfants();
    llvm::Function* fonction = _registreFonction->recuperer(_nomFonction.value);
    std::vector<llvm::Value*> args = *_registreArgument->recuperer();
    std::vector<llvm::Value*> argsConvertieLecture; 

    GestionnaireChargementVariable gestionnaireChargementVariable(_backend);

    for(size_t i = 0; i < args.size(); i++)
    {
        llvm::StringRef nom = args[i]->getName();
        std::string nomConvertieString(nom.begin(), nom.end());
        argsConvertieLecture.push_back(gestionnaireChargementVariable.chargerVariable(args[i], nomConvertieString));
    }

    return _backend->getBuilder().CreateCall(fonction, argsConvertieLecture, "resultat_appel");
}