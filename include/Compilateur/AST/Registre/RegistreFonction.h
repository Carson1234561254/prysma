#ifndef F2141F07_2C85_4ADB_9BC9_A909EBD34394
#define F2141F07_2C85_4ADB_9BC9_A909EBD34394

#include "RegistreGeneric.h"
#include <llvm-18/llvm/IR/Function.h>
#include <map>
#include <string>

class RegistreFonction : public RegistreGeneric<llvm::Function*>
{
private:
    std::map<std::string, llvm::Function*> _fonctions;

public:
    RegistreFonction() = default;
    ~RegistreFonction() = default;

    void ajouter(const std::string& nom, llvm::Function* fonction) {
        _fonctions[nom] = fonction;
    }

    llvm::Function* obtenir(const std::string& nom) const {
        auto iter = _fonctions.find(nom);
        if (iter != _fonctions.end()) {
            return iter->second;
        }
        return nullptr;
    }

    bool existe(const std::string& nom) const {
        return _fonctions.find(nom) != _fonctions.end();
    }

    void supprimer(const std::string& nom) {
        _fonctions.erase(nom);
    }

    void vider() {
        _fonctions.clear();
    }
};

#endif /* F2141F07_2C85_4ADB_9BC9_A909EBD34394 */
