#ifndef D2577958_A8A8_4878_AFA0_2B3478129911
#define D2577958_A8A8_4878_AFA0_2B3478129911

#include "Compilateur/AST/Utils/OrchestrateurInclude/FacadeConfigurationEnvironnement.h"
#include "Compilateur/Registre/RegistreFichier.h"


class OrchestrateurInclude
{
private: 
   FacadeConfigurationEnvironnement* _facadeConfigurationEnvironnement;
   RegistreFonction* _registreFonctionGlobale;
   RegistreFichier* _registreFichier;

public:
    OrchestrateurInclude(FacadeConfigurationEnvironnement* facadeConfigurationEnvironnement, RegistreFonction* registreFonctionGlobale, RegistreFichier* registreFichier);
    ~OrchestrateurInclude();

   void nouvelleInstance(const std::string& cheminFichier);
};

#endif /* D2577958_A8A8_4878_AFA0_2B3478129911 */
