#ifndef D2577958_A8A8_4878_AFA0_2B3478129911
#define D2577958_A8A8_4878_AFA0_2B3478129911

#include "Compilateur/AST/Utils/OrchestrateurInclude/UniteCompilation.h"
#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <set>
#include <memory>
#include <llvm-18/llvm/Support/ThreadPool.h>

struct ContextGenCode;
class INoeud;
class RegistreFonctionGlobale;
class RegistreFichier;

class OrchestrateurInclude
{
private: 
   std::mutex* _mutex;
   RegistreFonctionGlobale* _registreFonctionGlobale;
   RegistreFichier* _registreFichier;
   llvm::ThreadPool _threads;
   std::vector<std::unique_ptr<UniteCompilation>> _unitesCompilation;
   
   // Un registre dédié aux fichiers sources (.p)
   std::set<std::string> _fichiersDejaInclus; 

   // Indicateur d'erreur thread-safe pour savoir si la compilation a échoué
   std::atomic<bool> _aDesErreurs{false};

   // Flag pour activer la génération du graphe AST
   bool _activerGraphViz;

public:
    OrchestrateurInclude(RegistreFonctionGlobale* registreFonctionGlobale, RegistreFichier* registreFichier, std::mutex* mutex, bool activerGraphViz = false);
    ~OrchestrateurInclude();

    OrchestrateurInclude(const OrchestrateurInclude&) = delete;
    auto operator=(const OrchestrateurInclude&) -> OrchestrateurInclude& = delete;
    OrchestrateurInclude(OrchestrateurInclude&&) = delete;
    auto operator=(OrchestrateurInclude&&) -> OrchestrateurInclude& = delete;
    
   void compilerProjet(const std::string& cheminFichier);
   void inclureFichier(const std::string& cheminAbsolu);
   static void attendreFinPass(llvm::ThreadPool& threads);
   [[nodiscard]] auto aDesErreurs() const -> bool;
   [[nodiscard]] auto estGraphVizActif() const -> bool;
};

#endif /* D2577958_A8A8_4878_AFA0_2B3478129911 */