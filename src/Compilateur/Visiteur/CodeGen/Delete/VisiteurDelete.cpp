#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/AST_Genere.h"
#include <stdexcept>

void VisiteurGeneralGenCode::visiter(NoeudDelete* noeudDelete)
{
    auto& module = _contextGenCode->backend->getModule();
    auto& builder = _contextGenCode->backend->getBuilder();

    // Récupérer le token de la variable à supprimer
    const Token& tokenVariable = noeudDelete->getNomType();

    // Chercher la variable dans le registre de variables pour déterminer si elle existe
    Symbole symbole = _contextGenCode->registreVariable->recupererVariables(tokenVariable);

    if (symbole.adresse == nullptr) {
        throw std::runtime_error("Erreur: la variable '" + tokenVariable.value + "' n'existe pas!");
    }
    
    llvm::Value* adresseMemoire = symbole.adresse;
    llvm::Type* typeDonnee = adresseMemoire->getType();

    if (!typeDonnee->isPointerTy()) {
        throw std::runtime_error("Erreur: la variable '" + tokenVariable.value + "' n'est pas un pointeur. Delete ne peut s'appliquer qu'à des pointeurs.");
    }

    llvm::Value* adresseALiberer = builder.CreateLoad(
        typeDonnee,
        adresseMemoire,
        "pointeur_" + tokenVariable.value
    );

    // Récupérer la fonction prysma_free du module
    llvm::Function* freeFunc = module.getFunction("prysma_free");

    if (freeFunc == nullptr) {
        throw std::runtime_error("Erreur: la fonction prysma_free n'existe pas!");
    }

    // Appeler prysma_free avec l'adresse à libérer
    builder.CreateCall(freeFunc, {adresseALiberer});

    // Réinitialiser la valeur temporaire
    _contextGenCode->valeurTemporaire.adresse = nullptr;
}
