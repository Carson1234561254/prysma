#include "Compilateur/AST/Noeuds/Condition/NoeudIf.h"
#include "Compilateur/AST/Noeuds/Condition/NoeudBlocElse.h"
#include "Compilateur/AST/Noeuds/Condition/NoeudBlocEndif.h"
#include "Compilateur/AST/Noeuds/Condition/NoeudBlocIf.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include <llvm-18/llvm/IR/Value.h>

void VisiteurGeneralGenCode::visiter(NoeudIf* noeudIf) 
{
    // Récupérer les blocs if, else et endif à partir du noeud if
    std::shared_ptr<NoeudBlocIf> noeudBlocIf = noeudIf->noeudBlocIf;
    std::shared_ptr<NoeudBlocElse> noeudBlocElse = noeudIf->noeudBlocElse;
    std::shared_ptr<NoeudBlocEndif> noeudBlocEndif = noeudIf->noeudBlocEndif;

    // Récupérer le registre cmp pour la condition 

   llvm::Value* cmp = _contextGenCode->valeurTemporaire; 

    llvm::Function* fonctionEnCours = _contextGenCode->backend->getBuilder().GetInsertBlock()->getParent();

    llvm::BasicBlock* blocThen = llvm::BasicBlock::Create(_contextGenCode->backend->getContext(), "if", fonctionEnCours);
    llvm::BasicBlock* blocElse = llvm::BasicBlock::Create(_contextGenCode->backend->getContext(), "else", fonctionEnCours);
    llvm::BasicBlock* blocFin = llvm::BasicBlock::Create(_contextGenCode->backend->getContext(), "endif", fonctionEnCours);

    // Générer le code de branchement conditionnel c'est la condition br qui jump au flag 
    _contextGenCode->backend->getBuilder().CreateCondBr(cmp, blocThen, blocElse);

    // Générer le code pour le bloc "if"
    _contextGenCode->backend->getBuilder().SetInsertPoint(blocThen);
    
    for (const auto& enfant : noeudBlocIf->getEnfants()) {
        enfant->accept(this);
    }
    
    // Brancher vers endif à la fin du bloc if
    _contextGenCode->backend->getBuilder().CreateBr(blocFin);

    // Générer le code pour le bloc "else"
    _contextGenCode->backend->getBuilder().SetInsertPoint(blocElse);
    
    // Traiter le bloc else s'il existe
    if (noeudBlocElse) {
        for(const auto& enfant : noeudBlocElse->getEnfants()) {
            enfant->accept(this);
        }
    }
    
    // Brancher vers endif à la fin du bloc else
    _contextGenCode->backend->getBuilder().CreateBr(blocFin);

    // Générer le code pour le bloc "endif"
    _contextGenCode->backend->getBuilder().SetInsertPoint(blocFin);
    
     // Car plus de noeud devrait traiter cette valeur temporaire après le if
    _contextGenCode->valeurTemporaire = nullptr;

}
