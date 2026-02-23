#ifndef F2141F07_2C85_4ADB_9BC9_A909EBD34394
#define F2141F07_2C85_4ADB_9BC9_A909EBD34394

#include "RegistreGeneric.h"
#include <llvm-18/llvm/IR/Function.h>
#include <string>

class IType;
class NoeudDeclarationFonction;

struct SymboleFonction {
    llvm::Function* fonction;
    IType* typeRetour;
    NoeudDeclarationFonction* noeud;

    SymboleFonction() : fonction(nullptr), typeRetour(nullptr), noeud(nullptr) {}

    SymboleFonction(llvm::Function* fonction, IType* typeRetour, NoeudDeclarationFonction* noeud)
        : fonction(fonction), typeRetour(typeRetour), noeud(noeud) {}
};

class RegistreFonction : public RegistreGeneric<std::string, SymboleFonction>
{
public:
    RegistreFonction() = default;
    ~RegistreFonction() = default;
};

#endif /* F2141F07_2C85_4ADB_9BC9_A909EBD34394 */
