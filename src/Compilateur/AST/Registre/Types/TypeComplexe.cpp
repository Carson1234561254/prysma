#include "Compilateur/AST/Registre/Types/TypeComplexe.h"

TypeComplexe::TypeComplexe(const std::string& nom) : nomClasse(nom) {}

llvm::Type* TypeComplexe::genererTypeLLVM(llvm::LLVMContext& context) {
    return llvm::PointerType::getUnqual(context);
}

bool TypeComplexe::estFlottant() const { return false; }
bool TypeComplexe::estBooleen() const { return false; }
bool TypeComplexe::estChaine() const { return false; }
bool TypeComplexe::estTableau() const { return false; }
bool TypeComplexe::estComplexe() const { return true; }

llvm::Type* TypeComplexe::getVTableType(llvm::LLVMContext& context) {
    return llvm::PointerType::getUnqual(context);
}

std::string TypeComplexe::getNomClasse() const {
    return nomClasse;
}