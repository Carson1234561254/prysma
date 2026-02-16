#pragma once

#include "Compilateur/AST/Interfaces/IConstructeurArbre.h"
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/AST/Registre/RegistreSymbole.h"
#include "Compilateur/AST/Registre/RegistreStrategieEquation.h"
#include "Compilateur/Lexer/Lexer.h"
#include "Compilateur/AnalyseSyntaxique/Equation/ChaineResponsabilite.h"
#include "Compilateur/AnalyseSyntaxique/Equation/Interfaces/IGestionnaireParenthese.h"
#include <memory>
#include <vector>


class ConstructeurArbreEquation : public IConstructeurArbre
{
private:
    ChaineResponsabilite* _chaineResponsabilite;
    std::shared_ptr<RegistreSymbole> _registreSymbole;
    std::shared_ptr<RegistreStrategieEquation> _registreStrategieEquation;
    IGestionnaireParenthese* _gestionnaireParenthese;
    IConstructeurArbre* _instructionBuilder;

public:
  
    ConstructeurArbreEquation(
        ChaineResponsabilite* chaineResponsabilite,
        std::shared_ptr<RegistreSymbole> registreSymbole,
        std::shared_ptr<RegistreStrategieEquation> registreStrategieEquation,
        IGestionnaireParenthese* gestionnaireParenthese,
        IConstructeurArbre* instructionBuilder = nullptr
    );
    
    std::shared_ptr<INoeud> construire(std::vector<Token> &equation) override;
    std::shared_ptr<INoeud> construire(std::vector<Token>& tokens, int& index) override;
};
