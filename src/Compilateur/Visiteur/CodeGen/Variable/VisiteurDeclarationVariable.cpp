#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/AST_Genere.h"
#include "Compilateur/LLVM/GestionVariable.h"
#include "Compilateur/AST/Registre/Types/TypeTableau.h"
#include <llvm-18/llvm/IR/DerivedTypes.h>
#include <llvm/IR/Constants.h>

void VisiteurGeneralGenCode::visiter(NoeudDeclarationVariable* noeudDeclarationVariable) 
{
    GestionVariable gestionVariable(_contextGenCode);
    INoeud* expression = noeudDeclarationVariable->getExpression();
    
    // L'utilisation de dynamic_cast ici est un peu délicate, 
    // pour le moment je n'ai pas trouvé de solution optimal pour retirer ça, sinon je dois dépendre de llvm dans les INoeud, ce qui n'est pas idéal.
    // Le double dispatch est compliqué à mettre en place et ajouter une dépendance dans le context de génération du code 
    // Je dois trouver une solution pour éviter ce dynamic_cast, sans avoir c'est problème architectural. 
    // Sans doute utiliser un système de stratégie s'il y a plus de 2 types d'initialisation aussi. 
    // Beaucoup trop de static cast, je dois faire quelque chose pour éviter ça, c'est vraiment pas propre.
    
    // Vérifier si l'expression est une initialisation de tableau
    NoeudTableauInitialisation* tableauInit = dynamic_cast<NoeudTableauInitialisation*>(expression);
    
    llvm::AllocaInst* allocaCree = nullptr; 
    
    if (tableauInit != nullptr) {
        // Déterminer le type LLVM du tableau
        llvm::Type* typeVariable = nullptr;
        llvm::Type* typeElement = nullptr;
        
        TypeTableau* typeTableauDecl = dynamic_cast<TypeTableau*>(noeudDeclarationVariable->getType());
        
        if (typeTableauDecl != nullptr && typeTableauDecl->getTaille() == nullptr) {
            size_t tailleReelle = tableauInit->getElements().size();
            typeElement = typeTableauDecl->getTypeEnfant()->genererTypeLLVM(_contextGenCode->backend->getContext());
            typeVariable = llvm::ArrayType::get(typeElement, tailleReelle);
        } else {
            typeVariable = noeudDeclarationVariable->getType()->genererTypeLLVM(_contextGenCode->backend->getContext());
            if (typeVariable == nullptr) {
                throw std::runtime_error("Erreur : impossible de déterminer la taille du tableau");
            }
            auto* typeTableauLLVM = llvm::dyn_cast<llvm::ArrayType>(typeVariable);
            if (typeTableauLLVM == nullptr) {
                throw std::runtime_error("Erreur : le type de la variable n'est pas un tableau pour une initialisation de tableau");
            }
            typeElement = typeTableauLLVM->getElementType();
        }
        
        // Allouer et enregistrer le tableau
        llvm::AllocaInst* allocaInstTableau = gestionVariable.allouerVariable(typeVariable, noeudDeclarationVariable->getNom());
        
        allocaCree = allocaInstTableau;

        // Initialiser chaque élément du tableau
        auto* typeTableauLLVM = llvm::dyn_cast<llvm::ArrayType>(typeVariable);
        for (size_t i = 0; i < tableauInit->getElements().size(); ++i) {
            std::vector<llvm::Value*> indices = {
                _contextGenCode->backend->getBuilder().getInt32(0),
                _contextGenCode->backend->getBuilder().getInt32(static_cast<uint32_t>(i))
            }; 
            llvm::Value* ptrCase = _contextGenCode->backend->getBuilder().CreateGEP(typeTableauLLVM, allocaInstTableau, indices, "ptr_case");
            
            INoeud* element = tableauInit->getElements()[i];
            Symbole symboleElement = evaluerExpression(element);
            llvm::Value* valeurCastee = _contextGenCode->backend->creerAutoCast(symboleElement.adresse, typeElement);
            _contextGenCode->backend->getBuilder().CreateStore(valeurCastee, ptrCase);
        }
    } else {
        // Variable simple (non-tableau)
        llvm::Type* typeVariable = noeudDeclarationVariable->getType()->genererTypeLLVM(_contextGenCode->backend->getContext());
        llvm::AllocaInst* allocaInst = gestionVariable.allouerVariable(typeVariable, noeudDeclarationVariable->getNom());
        allocaCree = allocaInst;
        
        llvm::Value* valeurCalculee = evaluerExpression(expression).adresse;
        if (valeurCalculee == nullptr) {
            return;
        }

        llvm::Value* valeurCastee = _contextGenCode->backend->creerAutoCast(valeurCalculee, typeVariable);
        gestionVariable.stockerVariable(valeurCastee, allocaInst);
    }
    if (allocaCree != nullptr) {
        Token token;
        token.value = noeudDeclarationVariable->getNom();
        
        // Créer le symbole avec le type pointé si c'est un pointeur
        llvm::Type* typeVariable = noeudDeclarationVariable->getType()->genererTypeLLVM(_contextGenCode->backend->getContext());
        
        // Si on a un tableau avec taille dynamique (nullptr), on doit utiliser le type réel qu'on a calculé
        if (typeVariable == nullptr) {
            TypeTableau* typeTableauDecl = dynamic_cast<TypeTableau*>(noeudDeclarationVariable->getType());
            if (typeTableauDecl != nullptr && tableauInit != nullptr) {
                // On peut recalculer à partir de l'initialisation
                size_t tailleReelle = tableauInit->getElements().size();
                llvm::Type* typeElement = typeTableauDecl->getTypeEnfant()->genererTypeLLVM(_contextGenCode->backend->getContext());
                typeVariable = llvm::ArrayType::get(typeElement, tailleReelle);
            } else {
                throw std::runtime_error("Erreur : impossible de déterminer le type de la variable");
            }
        }
        
        llvm::Type* typePointeElement = nullptr;
        
        if (typeVariable->isPointerTy()) {
            // Pour un pointeur, on récupère le type pointé qui a été mémorisé lors de l'évaluation de l'expression (new)
            typePointeElement = _contextGenCode->valeurTemporaire.typePointeElement;
        }
        
        _contextGenCode->registreVariable->enregistrer(
            token, 
            Symbole(allocaCree, noeudDeclarationVariable->getType(), typePointeElement)
        );
    }
}