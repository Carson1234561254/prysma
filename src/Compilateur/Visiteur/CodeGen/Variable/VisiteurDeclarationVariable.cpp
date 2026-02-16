#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudDeclarationVariable.h"
#include "Compilateur/LLVM/GestionVariable.h"

void VisiteurGeneralGenCode::visiter(NoeudDeclarationVariable* noeudDeclarationVariable) 
{
    GestionVariable gestionVariable(_contextGenCode);

    // Générer le type LLVM via la hiérarchie IType
    llvm::Type* typeVariable = noeudDeclarationVariable->getType()->genererTypeLLVM(_contextGenCode->backend->getContext());
    llvm::AllocaInst* allocaInst = gestionVariable.allouerVariable(typeVariable, noeudDeclarationVariable->getNom());

    // Enregistrer la variable
    gestionVariable.enregistrerVariable(noeudDeclarationVariable->getNom(), allocaInst);

    // Évaluer l'expression d'initialisation
    llvm::Value* valeurCalculee = evaluerExpression(noeudDeclarationVariable->getExpression());

    // Stocker la valeur
    llvm::Value* valeurCastee = _contextGenCode->backend->creerAutoCast(valeurCalculee, typeVariable);
    gestionVariable.stockerVariable(valeurCastee, allocaInst);
}

