#ifndef A2837407_B466_49AE_8A29_4BFC0A5D0461
#define A2837407_B466_49AE_8A29_4BFC0A5D0461

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/AST/Registre/Types/IType.h"
#include <string>
#include <vector>

class NoeudArgFonction;
class NoeudScope;
class IVisiteur;

class NoeudDeclarationFonction : public INoeud
{
private:
    std::string _nom;
    IType* _typeRetour;
    std::vector<NoeudArgFonction*> _arguments;
    NoeudScope* _corps;

public:
    NoeudDeclarationFonction(
        std::string nom,
        IType* typeRetour,
        const std::vector<NoeudArgFonction*>& arguments,
        NoeudScope* corps
    );
    
    ~NoeudDeclarationFonction() = default;

    void accept(IVisiteur* visiteur) override;

    const std::string& getNom() const { return _nom; }
    IType* getTypeRetour() const { return _typeRetour; }

    const std::vector<NoeudArgFonction*>& getArguments() const { return _arguments; }
    NoeudScope* getCorps() const { return _corps; }
};

#endif /* A2837407_B466_49AE_8A29_4BFC0A5D0461 */
