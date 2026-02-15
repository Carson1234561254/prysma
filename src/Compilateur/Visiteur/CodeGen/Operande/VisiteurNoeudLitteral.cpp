#include "Compilateur/AST/Noeuds/Operande/NoeudLitteral.h"
#include "Compilateur/Lexer/TokenType.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"

void VisiteurGeneralGenCode::visiter(NoeudLitteral* noeudLitteral)
{
    // On récupère le contexte LLVM
    llvm::LLVMContext& context = _contextGenCode->backend->getContext();
    
    Token token = noeudLitteral->getToken();

    if (token.type == TOKEN_VRAI || token.type == TOKEN_FAUX) {
        bool valeur = (token.type == TOKEN_VRAI);
        _contextGenCode->valeurTemporaire = llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), valeur ? 1 : 0);
    }
    else if (token.type == TOKEN_LIT_BOLEEN) {
        int valeur = std::stoi(token.value); // "1" pour true, "0" pour false
        _contextGenCode->valeurTemporaire = llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), valeur);
    }
    else if (token.type == TOKEN_LIT_INT) { 
        int valeur = std::stoi(token.value); 
        _contextGenCode->valeurTemporaire = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), valeur);
    }
    else {
        float valeur = std::stof(token.value); 
        _contextGenCode->valeurTemporaire = llvm::ConstantFP::get(llvm::Type::getFloatTy(context), valeur);
    }
}