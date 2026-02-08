#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Variable/NoeudDeclarationVariable.h"
#include <llvm-18/llvm/IR/Instructions.h>

void VisiteurGeneralGenCode::visiter(NoeudDeclarationVariable* noeudDeclarationVariable) 
{
    Token nomDeLaVariable;
    nomDeLaVariable.value = noeudDeclarationVariable->_nom;
    nomDeLaVariable.type = TOKEN_IDENTIFIANT;
    
    // C'est le bloc ou sera écrit le code 
    llvm::BasicBlock* insertBlock = _contextGenCode->backend->getBuilder().GetInsertBlock();
    _contextGenCode->backend->definirPointInsertionApresAllocation();

    // Initialiser un espace mémoire pour la variable
    llvm::AllocaInst* allocaInst = _contextGenCode->backend->getBuilder().CreateAlloca(_contextGenCode->registreType->recuperer( noeudDeclarationVariable->_tokenType), nullptr, nomDeLaVariable.value); 
    _contextGenCode->backend->getBuilder().SetInsertPoint(insertBlock);
    
    _contextGenCode->registreVariable->enregistrer(nomDeLaVariable, allocaInst);

    // Exemple : 45 * a + ( 234 )
    llvm::Value* valeurCalculee = evaluerExpression(noeudDeclarationVariable->_expression);

    // C'est l'endroit ou nous pouvons mettre les données
     _contextGenCode->backend->getBuilder().CreateStore(_contextGenCode->backend->creerAutoCast(valeurCalculee,_contextGenCode->registreType->recuperer(noeudDeclarationVariable->_tokenType)), allocaInst);
}

