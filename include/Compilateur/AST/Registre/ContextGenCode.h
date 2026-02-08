#ifndef C2537ED8_1CCF_4242_BDB0_B5ED5F2AD08F
#define C2537ED8_1CCF_4242_BDB0_B5ED5F2AD08F

#include <memory>
#include <iostream>
#include <stdexcept>
#include "RegistreInstruction.h"
#include "Pile/RegistreVariable.h"
#include "RegistreFonction.h"
#include "RegistreType.h"
#include "RegistreArgument.h"
#include "Pile/RetourContexteCompilation.h"
#include "../../LLVM/LlvmBackend.h"

struct ContextGenCode
{
    llvm::Value* valeurTemporaire;
    std::shared_ptr<LlvmBackend> backend;
    std::shared_ptr<RegistreInstruction> registreInstruction;
    std::shared_ptr<RegistreVariable> registreVariable;
    std::shared_ptr<RegistreFonction> registreFonction;
    std::shared_ptr<RegistreType> registreType;
    std::shared_ptr<RetourContexteCompilation> returnContextCompilation;
    std::shared_ptr<RegistreArgument> registreArgument;

    ContextGenCode(
        std::shared_ptr<LlvmBackend> backend,
        std::shared_ptr<RegistreInstruction> registreInstruction,
        std::shared_ptr<RegistreVariable> registreVariable,
        std::shared_ptr<RegistreFonction> registreFonction,
        std::shared_ptr<RegistreType> registreType,
        std::shared_ptr<RetourContexteCompilation> returnContextCompilation,
        std::shared_ptr<RegistreArgument> registreArgument,
        llvm::Value* valeurTemporaire
    ) 
    {
        try {
            if (!backend) {
                throw std::invalid_argument("Le backend LLVM ne peut pas être null");
            }
            if (!registreInstruction) {
                throw std::invalid_argument("Le registre d'instruction ne peut pas être null");
            }
            if (!registreVariable) {
                throw std::invalid_argument("Le registre de variable ne peut pas être null");
            }
            if (!registreFonction) {
                throw std::invalid_argument("Le registre de fonction ne peut pas être null");
            }
            if (!registreType) {
                throw std::invalid_argument("Le registre de type ne peut pas être null");
            }
            if (!returnContextCompilation) {
                throw std::invalid_argument("Le contexte de retour de compilation ne peut pas être null");
            }
            if (!registreArgument) {
                throw std::invalid_argument("Le registre d'argument ne peut pas être null");
            }

            this->valeurTemporaire = valeurTemporaire;
            this->backend = std::move(backend);
            this->registreInstruction = std::move(registreInstruction);
            this->registreVariable = std::move(registreVariable);
            this->registreFonction = std::move(registreFonction);
            this->registreType = std::move(registreType);
            this->returnContextCompilation = std::move(returnContextCompilation);
            this->registreArgument = std::move(registreArgument);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Erreur lors de l'initialisation du contexte de génération de code : " 
                      << e.what() << std::endl;
            throw;
        }
        catch (const std::exception& e) {
            std::cerr << "Erreur inattendue lors de l'initialisation du contexte : " 
                      << e.what() << std::endl;
            throw;
        }
    }
};

#endif /* C2537ED8_1CCF_4242_BDB0_B5ED5F2AD08F */
