#include "Compilateur/AST/Noeuds/Operande/Valeur.h"

Valeur::Valeur(llvm::Value* valeur) : _valeur(valeur) {}

llvm::Value* Valeur::genCode() {
    return _valeur;
}
