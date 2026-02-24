#include "Compilateur/AST/Utils/ConstructeurEnvironnementRegistreFonction.h"
#include "Compilateur/AST/Registre/RegistreFonction.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudDeclarationFonction.h"
#include "Compilateur/AST/Noeuds/Fonction/NoeudArgFonction.h"

ConstructeurEnvironnementRegistreFonction::ConstructeurEnvironnementRegistreFonction(ContextGenCode* contextGenCode)
    : _contextGenCode(contextGenCode) {}

ConstructeurEnvironnementRegistreFonction::~ConstructeurEnvironnementRegistreFonction() {}

void ConstructeurEnvironnementRegistreFonction::remplir()
{   
    auto* nouveauRegistre = new (_contextGenCode->arena->Allocate<RegistreFonction>()) RegistreFonction();

    for(const auto& cle : _contextGenCode->registreFonction->obtenirCles())
    {
        auto ancienSymbole = _contextGenCode->registreFonction->recuperer(cle);
        
        if (ancienSymbole.noeud == nullptr) {
            nouveauRegistre->enregistrer(cle, ancienSymbole);
            continue;
        }

        llvm::Type* retType = ancienSymbole.typeRetour->genererTypeLLVM(_contextGenCode->backend->getContext());
        
        std::vector<llvm::Type*> paramTypes;
        for (auto* arg : ancienSymbole.noeud->getArguments()) {
            paramTypes.push_back(arg->getType()->genererTypeLLVM(_contextGenCode->backend->getContext()));
        }

        llvm::FunctionType* funcType = llvm::FunctionType::get(retType, paramTypes, false);
        
        llvm::Function* vraieFonction = llvm::Function::Create(
            funcType, 
            llvm::Function::ExternalLinkage, 
            cle,          
            _contextGenCode->backend->getModule()
        );

        SymboleFonction nouveauSymbole;
        nouveauSymbole.fonction = vraieFonction;
        nouveauSymbole.typeRetour = ancienSymbole.typeRetour;
        nouveauSymbole.noeud = ancienSymbole.noeud;
        
        nouveauRegistre->enregistrer(cle, nouveauSymbole);        
    }
    
    _contextGenCode->registreFonction = nouveauRegistre;
}