#include "Compilateur/AST/Noeuds/Condition/NoeudIf.h"
#include "Compilateur/AST/Noeuds/Condition/NoeudBlocIf.h"
#include "Compilateur/AST/Noeuds/Condition/NoeudBlocElse.h"
#include "Compilateur/AST/Noeuds/Condition/NoeudBlocEndif.h"

NoeudIf::NoeudIf()
    = default;

NoeudIf::NoeudIf(std::shared_ptr<NoeudBlocIf>&& blocIf, std::shared_ptr<NoeudBlocElse>&& blocElse, std::shared_ptr<NoeudBlocEndif>&& blocEndif)
    : noeudBlocIf(std::move(blocIf)), noeudBlocElse(std::move(blocElse)), noeudBlocEndif(std::move(blocEndif))
{
}

NoeudIf::~NoeudIf()
 {}
 
 void NoeudIf::accept(IVisiteur* visiteur) 
 {
    visiteur->visiter(this);
 }