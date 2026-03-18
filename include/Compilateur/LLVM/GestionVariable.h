#ifndef D5B94044_819C_4C15_B528_AAE97CBCB264
#define D5B94044_819C_4C15_B528_AAE97CBCB264

#include "Compilateur/AST/Registre/ContextGenCode.h"
#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/IR/Value.h>
#include <string>

class ExtracteurTypeVariable {
protected:
    ContextGenCode* _context;
public:
    explicit ExtracteurTypeVariable(ContextGenCode* context);
    llvm::Type* extraire(llvm::Value* adresseMemoire);
};

class AdresseurVariable {
protected:
    ContextGenCode* _context;
public:
    explicit AdresseurVariable(ContextGenCode* context);
    Symbole recupererAdresse(const std::string& nomVariable);
};

class ChargeurVariable {
protected:
    ContextGenCode* _context;
    AdresseurVariable _adresseur;
    ExtracteurTypeVariable _extracteur;
public:
    explicit ChargeurVariable(ContextGenCode* context);
    Symbole charger(const std::string& nomVariable);
    Symbole chargerUnref(const std::string& nomVariable);
};

class AllocateurVariable {
protected:
    ContextGenCode* _context;
public:
    explicit AllocateurVariable(ContextGenCode* context);
    llvm::AllocaInst* allouer(llvm::Type* type, const std::string& nomVariable);
    void stocker(llvm::Value* valeur, llvm::AllocaInst* allocaInst);
};

class AffecteurVariable {
protected:
    ContextGenCode* _context;
    ExtracteurTypeVariable _extracteur;
public:
    explicit AffecteurVariable(ContextGenCode* context);
    void affecter(llvm::Value* variableExistante, llvm::Value* valeur, llvm::Type* typeVariableLLVM = nullptr);
};

#endif /* D5B94044_819C_4C15_B528_AAE97CBCB264 */
