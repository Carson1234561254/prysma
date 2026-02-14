#ifndef B9F8948B_23A4_4812_A098_C71C4D92373B
#define B9F8948B_23A4_4812_A098_C71C4D92373B
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/AST/Registre/RegistreType.h"
#include <memory>
#include <string>
class NoeudArgFonction: public INoeud
{
private:
     std::shared_ptr<RegistreType> _registreType; 
     std::string _nom;
     TokenType _type;

public: 
    NoeudArgFonction(std::shared_ptr<RegistreType> registreType, std::string nom, TokenType type);
    ~NoeudArgFonction();

    void accept(IVisiteur* visiteur) override;

    const std::shared_ptr<RegistreType>& getRegistreType() const { return _registreType; }
    const std::string& getNom() const { return _nom; }
    TokenType getType() const { return _type; }
};

#endif /* B9F8948B_23A4_4812_A098_C71C4D92373B */
