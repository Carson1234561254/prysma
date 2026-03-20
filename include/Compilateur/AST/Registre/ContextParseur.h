#ifndef F4099BCE_4896_40B4_B34C_93B4827706C3
#define F4099BCE_4896_40B4_B34C_93B4827706C3

#include "Compilateur/AST/Interfaces/IConstructeurArbre.h"
#include "Compilateur/AST/Registre/Pile/RegistreVariable.h"
#include "Compilateur/AST/Registre/RegistreType.h"
#include "Compilateur/AnalyseSyntaxique/ParseurType.h"
#include <stdexcept>

struct ContextParseur
{
private:
    IConstructeurArbre* constructeurArbreEquation;
    IConstructeurArbre* constructeurArbreInstruction;
    ParseurType* parseurType;
    RegistreVariable* registreVariable;
    RegistreType* registreType;

public:
    struct Dependencies {
        IConstructeurArbre* constructeurArbreEquation;
        IConstructeurArbre* constructeurArbreInstruction;
        ParseurType* parseurType;
        RegistreVariable* registreVariable;
        RegistreType* registreType;
    };

    explicit ContextParseur(const Dependencies& deps)
        : constructeurArbreEquation(deps.constructeurArbreEquation),
          constructeurArbreInstruction(deps.constructeurArbreInstruction),
          parseurType(deps.parseurType),
          registreVariable(deps.registreVariable),
          registreType(deps.registreType)
    {
        if(constructeurArbreEquation == nullptr)
        {
            throw std::invalid_argument("constructeurArbreEquation ne peut pas être nul");
        }

        if(constructeurArbreInstruction == nullptr)
        {
            throw std::invalid_argument("constructeurArbreInstruction ne peut pas être nul");
        }

        if(parseurType == nullptr)
        {
            throw std::invalid_argument("parseurType ne peut pas être nul");
        }

        if(registreVariable == nullptr)
        {
            throw std::invalid_argument("registreVariable ne peut pas être nul");
        }

        if(registreType == nullptr)
        {
            throw std::invalid_argument("registreType ne peut pas être nul");
        }
    }    

    [[nodiscard]] auto getConstructeurArbreEquation() const -> IConstructeurArbre* { return constructeurArbreEquation; }
    [[nodiscard]] auto getConstructeurArbreInstruction() const -> IConstructeurArbre* { return constructeurArbreInstruction; }
    [[nodiscard]] auto getParseurType() const -> ParseurType* { return parseurType; }
    [[nodiscard]] auto getRegistreVariable() const -> RegistreVariable* { return registreVariable; }
    [[nodiscard]] auto getRegistreType() const -> RegistreType* { return registreType; }
};

#endif /* F4099BCE_4896_40B4_B34C_93B4827706C3 */
