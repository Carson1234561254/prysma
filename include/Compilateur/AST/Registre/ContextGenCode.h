#ifndef C2537ED8_1CCF_4242_BDB0_B5ED5F2AD08F
#define C2537ED8_1CCF_4242_BDB0_B5ED5F2AD08F

#include <memory>
#include "RegistreInstruction.h"
#include "Pile/RegistreVariable.h"
#include "RegistreFonction.h"
#include "RegistreType.h"
#include "RegistreArgument.h"
#include "Pile/ReturnContextCompilation.h"
#include "../../LLVM/LLVMBackend.h"

struct ContextGenCode
{
    std::shared_ptr<LLVMBackend> backend;
    std::shared_ptr<RegistreInstruction> registreInstruction;
    std::shared_ptr<RegistreVariable> registreVariable;
    std::shared_ptr<RegistreFonction> registreFonction;
    std::shared_ptr<RegistreType> registreType;
    std::shared_ptr<ReturnContextCompilation> returnContextCompilation;
    std::shared_ptr<RegistreArgument> registreArgument;

    ContextGenCode(
        std::shared_ptr<LLVMBackend> backend_,
        std::shared_ptr<RegistreInstruction> registreInstruction_,
        std::shared_ptr<RegistreVariable> registreVariable_,
        std::shared_ptr<RegistreFonction> registreFonction_,
        std::shared_ptr<RegistreType> registreType_,
        std::shared_ptr<ReturnContextCompilation> returnContextCompilation_,
        std::shared_ptr<RegistreArgument> registreArgument_
    ) 
        : backend(std::move(backend_)),
          registreInstruction(std::move(registreInstruction_)),
          registreVariable(std::move(registreVariable_)),
          registreFonction(std::move(registreFonction_)),
          registreType(std::move(registreType_)),
          returnContextCompilation(std::move(returnContextCompilation_)),
          registreArgument(std::move(registreArgument_))
    {
    }
};

#endif /* C2537ED8_1CCF_4242_BDB0_B5ED5F2AD08F */
