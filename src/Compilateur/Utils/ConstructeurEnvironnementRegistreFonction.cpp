#include "Compilateur/AST/Utils/ConstructeurEnvironnementRegistreFonction.h"
#include "Compilateur/AST/Registre/RegistreFonction.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudDeclarationFonction.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudArgFonction.h"

ConstructeurEnvironnementRegistreFonction::ConstructeurEnvironnementRegistreFonction(ContextGenCode* contextGenCode)
    : _contextGenCode(contextGenCode) {}

ConstructeurEnvironnementRegistreFonction::~ConstructeurEnvironnementRegistreFonction() {}


// Je vais jetter ça, plus besoins car je vais opter pour un système de stockage unique du noeud dans le registre global 
// multi thread, c'est les thread qui ce chargera de reconstruire les fonctions llvm à partir du noeud dans le registre global
void ConstructeurEnvironnementRegistreFonction::remplir()
{   
    for(const auto& cle : _contextGenCode->registreFonctionGlobale->obtenirCles())
    {
        const auto& ancienSymboleUniquePtr = _contextGenCode->registreFonctionGlobale->recuperer(cle);
        const auto* ancienSymbole = static_cast<const SymboleFonctionGlobale*>(ancienSymboleUniquePtr.get());
        
        if (ancienSymbole->noeud == nullptr) {
            // Ne devrait pas arriver avec la nouvelle logique, mais par sécurité
            continue;
        }

        llvm::Type* retType = ancienSymbole->typeRetour->genererTypeLLVM(_contextGenCode->backend->getContext());
        
        std::vector<llvm::Type*> paramTypes;
        for (auto* arg : ancienSymbole->noeud->getArguments()) {
            paramTypes.push_back(arg->getType()->genererTypeLLVM(_contextGenCode->backend->getContext()));
        }

        llvm::FunctionType* funcType = llvm::FunctionType::get(retType, paramTypes, false);
        
        llvm::Function* vraieFonction = llvm::Function::Create(
            funcType, 
            llvm::Function::ExternalLinkage, 
            cle,          
            _contextGenCode->backend->getModule()
        );

        auto nouveauSymbole = std::make_unique<SymboleFonctionLocale>();
        nouveauSymbole->fonction = vraieFonction;
        nouveauSymbole->typeRetour = ancienSymbole->typeRetour;
        nouveauSymbole->noeud = ancienSymbole->noeud;
        
        _contextGenCode->registreFonctionLocale->enregistrer(cle, std::move(nouveauSymbole));        
    }
}