#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/AST/Noeuds/Equation/NoeudOperation.h"
#include <llvm/IR/Type.h>

void VisiteurGeneralGenCode::visiter(NoeudOperation* noeud)
{
    noeud->getGauche()->accept(this);
    llvm::Value* valGauche = _contextGenCode->valeurTemporaire;

    noeud->getDroite()->accept(this);
    llvm::Value* valDroite = _contextGenCode->valeurTemporaire;

    auto& builder = _contextGenCode->backend->getBuilder();
    llvm::Value* resultat = nullptr;

    bool estFlottant = valGauche->getType()->isFloatingPointTy() || 
                       valDroite->getType()->isFloatingPointTy();

    if (estFlottant) {
        llvm::Type* floatTy = llvm::Type::getFloatTy(_contextGenCode->backend->getContext());
        valGauche = _contextGenCode->backend->creerAutoCast(valGauche, floatTy);
        valDroite = _contextGenCode->backend->creerAutoCast(valDroite, floatTy);

        switch (noeud->getToken().type) {
            case TOKEN_PLUS:  resultat = builder.CreateFAdd(valGauche, valDroite, "fadd"); break;
            case TOKEN_MOINS: resultat = builder.CreateFSub(valGauche, valDroite, "fsub"); break;
            case TOKEN_ETOILE:resultat = builder.CreateFMul(valGauche, valDroite, "fmul"); break;
            case TOKEN_SLASH: resultat = builder.CreateFDiv(valGauche, valDroite, "fdiv"); break;
            case TOKEN_MODULO: resultat = builder.CreateFRem(valGauche, valDroite, "frem"); break;
            // Pour les comparaisons float, ça renvoie un i1 (bool)
            case TOKEN_PLUS_PETIT:      resultat = builder.CreateFCmpOLT(valGauche, valDroite, "fcmp_lt"); break;
            case TOKEN_PLUS_GRAND:      resultat = builder.CreateFCmpOGT(valGauche, valDroite, "fcmp_gt"); break;
            case TOKEN_PLUS_PETIT_EGAL: resultat = builder.CreateFCmpOLE(valGauche, valDroite, "fcmp_le"); break;
            case TOKEN_PLUS_GRAND_EGAL: resultat = builder.CreateFCmpOGE(valGauche, valDroite, "fcmp_ge"); break;
            case TOKEN_EGAL_EGAL:       resultat = builder.CreateFCmpOEQ(valGauche, valDroite, "fcmp_eq"); break;
            case TOKEN_DIFFERENT:       resultat = builder.CreateFCmpONE(valGauche, valDroite, "fcmp_ne"); break;
            default: break;
        }
    } 
    else {
        switch (noeud->getToken().type) {
            case TOKEN_PLUS:  resultat = builder.CreateAdd(valGauche, valDroite, "iadd"); break;
            case TOKEN_MOINS: resultat = builder.CreateSub(valGauche, valDroite, "isub"); break;
            case TOKEN_ETOILE:resultat = builder.CreateMul(valGauche, valDroite, "imul"); break;
            case TOKEN_SLASH: resultat = builder.CreateSDiv(valGauche, valDroite, "idiv"); break;
            case TOKEN_MODULO: resultat = builder.CreateSRem(valGauche, valDroite, "irem"); break;
            
            // Comparaisons ENTIERS (ICmp)
            case TOKEN_PLUS_PETIT:      resultat = builder.CreateICmpSLT(valGauche, valDroite, "icmp_lt"); break;
            case TOKEN_PLUS_GRAND:      resultat = builder.CreateICmpSGT(valGauche, valDroite, "icmp_gt"); break;
            case TOKEN_PLUS_PETIT_EGAL: resultat = builder.CreateICmpSLE(valGauche, valDroite, "icmp_le"); break;
            case TOKEN_PLUS_GRAND_EGAL: resultat = builder.CreateICmpSGE(valGauche, valDroite, "icmp_ge"); break;
            case TOKEN_EGAL_EGAL:       resultat = builder.CreateICmpEQ(valGauche, valDroite, "icmp_eq"); break;
            case TOKEN_DIFFERENT:       resultat = builder.CreateICmpNE(valGauche, valDroite, "icmp_ne"); break;
            case TOKEN_ET:              resultat = builder.CreateAnd(valGauche, valDroite, "and"); break;
            case TOKEN_OU:              resultat = builder.CreateOr(valGauche, valDroite, "or"); break;
            default: break;
        }
    }

    if (!resultat) throw std::runtime_error("Opération inconnue");

    _contextGenCode->valeurTemporaire = resultat;
}