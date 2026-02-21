#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Tableau/NoeudLectureTableau.h"
#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/Support/Casting.h>

void VisiteurGeneralGenCode::visiter(NoeudLectureTableau* noeudLectureTableau)
{
    // Récupération de l'adresse de base du tableau 
    Symbole symbole = _contextGenCode->registreVariable->recupererVariables(noeudLectureTableau->getNomTableau());
    llvm::Value* adresseTableau = symbole.adresse;

    // Faire une allocaInstance pour récupérer le type, on dyn cast le type llvm::Value 
    llvm::AllocaInst* allocaInst = llvm::dyn_cast<llvm::AllocaInst>(adresseTableau);
    llvm::Type* typeTableau = allocaInst->getAllocatedType();
    
    // Calculer l'index à partir de l'équation 
    noeudLectureTableau->getIndexEquation()->accept(this);
    
    // calculer le décalage avec GEP 
    llvm::Value* adresseElement = _contextGenCode->backend->getBuilder().CreateGEP(typeTableau, adresseTableau, 
        { 
            _contextGenCode->backend->getBuilder().getInt32(0), 
            _contextGenCode->valeurTemporaire.adresse 
        }, noeudLectureTableau->getNomTableau().value);
        
    // Lire la valeur de l'adresse de l'élément
    llvm::Value* valeurElement = _contextGenCode->backend->getBuilder().CreateLoad(typeTableau->getArrayElementType(),adresseElement,noeudLectureTableau->getNomTableau().value);

    _contextGenCode->valeurTemporaire.adresse = valeurElement;
} 

