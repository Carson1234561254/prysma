#ifndef C2ADEE91_A0DA_4404_8AF5_5B1105A499EC
#define C2ADEE91_A0DA_4404_8AF5_5B1105A499EC

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/AST/Registre/Pile/RegistreVariable.h"
#include "Compilateur/AST/Registre/RegistreFonction.h"
#include <llvm-18/llvm/IR/DerivedTypes.h>
#include <llvm-18/llvm/IR/GlobalVariable.h>
#include <string>


struct Class
{
    RegistreFonctionLocale* registreFonctionLocale;
    RegistreVariable* registreVariable;

    llvm::GlobalVariable* vtable;
    
    // Pour calculer la taille automatique de l'objet avec llvm 
    llvm::StructType* structType;
    INoeud* parentHeritage;
};


class RegistreClass : public RegistreGeneric<std::string, Class*> 
{
public:
    RegistreClass() = default;
    virtual ~RegistreClass() = default;
};


#endif /* C2ADEE91_A0DA_4404_8AF5_5B1105A499EC */
