#include "Compilateur/LLVM/GenerateurFonction.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/AST/Registre/RegistreFonction.h"

void VisiteurGeneralGenCode::visiter(NoeudAppelFonction* noeudAppelFonction)
{
    std::string nomFonction = noeudAppelFonction->getNomFonction().value;
    
    // Récupérer le noeud depuis le registre global (thread safe, pas de llvm::Function*)
    const auto& symbolePtr = _contextGenCode->registreFonctionGlobale->recuperer(nomFonction);
    const auto* symbole = static_cast<const SymboleFonctionGlobale*>(symbolePtr.get());
    
    // Pour les fonctions externes (print, backSlashN...), noeud est nullptr
    NoeudDeclarationFonction* noeud = symbole->noeud;
    
    GestionFonction gestionnaireFonction(_contextGenCode, noeud, this);
    gestionnaireFonction.genererAppelFonction(noeudAppelFonction);
}