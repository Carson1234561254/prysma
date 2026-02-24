#include "Compilateur/AST/Utils/ConstructeurEnvironnementRegistreVariable.h"
#include "Compilateur/AST/Registre/Pile/RegistreVariable.h"
#include "Compilateur/AST/Registre/Types/IType.h"
#include "Compilateur/LLVM/LlvmBackend.h"
#include "llvm/IR/GlobalVariable.h"

ConstructeurEnvironnementRegistreVariable::ConstructeurEnvironnementRegistreVariable(ContextGenCode* contextGenCode)
    : _contextGenCode(contextGenCode) {}

ConstructeurEnvironnementRegistreVariable::~ConstructeurEnvironnementRegistreVariable() {}

// Actuellement inutilisée, c'est pour le future, un autre ittération de développement, elle existe pour le moment mais elle n'est pas encore testé
// Une fonctionnalité bonus 
// Cette classe a pour but de remplir le registre de variable global ce trouvant à l'extérieur d'une fonction 
// exemple : 
// scope {
//     dec int64 a = 10;
//     dec string b = "string";
//     fn void teste()
//     {
//     }
// }

void ConstructeurEnvironnementRegistreVariable::remplir()
{   
    auto variablesGlobalesPasse1 = _contextGenCode->registreVariable->getGlobalVariables();

    _contextGenCode->registreVariable->viderTop(); 

    for(auto const& [nom, symbole] : variablesGlobalesPasse1)
    {
        llvm::Type* typeLLVM = symbole.type->genererTypeLLVM(_contextGenCode->backend->getContext());
        
        auto* variableGlobale = new llvm::GlobalVariable(
            _contextGenCode->backend->getModule(),
            typeLLVM,
            false,
            llvm::GlobalValue::ExternalLinkage,
            nullptr,
            nom
        );

        Token token;
        token.value = nom;
        
        _contextGenCode->registreVariable->enregistrer(token, Symbole(variableGlobale, symbole.type));
    }
}