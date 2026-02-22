#include "Compilateur/AST/Noeuds/Operande/NoeudLitteral.h"
#include "Compilateur/Lexer/TokenType.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Registre/Types/TypeSimple.h"

void VisiteurGeneralGenCode::visiter(NoeudLitteral* noeudLitteral)
{
    // On récupère le contexte LLVM
    llvm::LLVMContext& context = _contextGenCode->backend->getContext();
    
    Token token = noeudLitteral->getToken();

    if (token.type == TOKEN_VRAI || token.type == TOKEN_FAUX) {
        bool valeur = (token.type == TOKEN_VRAI);
        _contextGenCode->valeurTemporaire.adresse = llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), valeur ? 1 : 0);
        _contextGenCode->valeurTemporaire.type = new (_contextGenCode->arena->Allocate<TypeSimple>()) TypeSimple(llvm::Type::getInt1Ty(context));
    }
    else if (token.type == TOKEN_LIT_BOLEEN) {
        int valeur = std::stoi(token.value); // "1" pour true, "0" pour false
        _contextGenCode->valeurTemporaire.adresse = llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), static_cast<uint64_t>(valeur));
        _contextGenCode->valeurTemporaire.type = new (_contextGenCode->arena->Allocate<TypeSimple>()) TypeSimple(llvm::Type::getInt1Ty(context));
    }
    else if (token.type == TOKEN_LIT_INT) { 
        int valeur = std::stoi(token.value); 
        _contextGenCode->valeurTemporaire.adresse = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), static_cast<uint64_t>(valeur));
        _contextGenCode->valeurTemporaire.type = new (_contextGenCode->arena->Allocate<TypeSimple>()) TypeSimple(llvm::Type::getInt32Ty(context));
    }
    else {
        float valeur = std::stof(token.value); 
        _contextGenCode->valeurTemporaire.adresse = llvm::ConstantFP::get(llvm::Type::getFloatTy(context), valeur);
        _contextGenCode->valeurTemporaire.type = new (_contextGenCode->arena->Allocate<TypeSimple>()) TypeSimple(llvm::Type::getFloatTy(context));
    }
}