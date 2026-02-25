#ifndef B7E0ADAE_EE35_414F_A816_05C49AF1A5F3
#define B7E0ADAE_EE35_414F_A816_05C49AF1A5F3

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include <string>
class NoeudInclude : public INoeud
{
private:
    std::string _path; 
public:
    NoeudInclude(const std::string& path);
    ~NoeudInclude();
    void accept(IVisiteur* visiteur) override;
    std::string getPath() const { return _path; }
};

#endif /* B7E0ADAE_EE35_414F_A816_05C49AF1A5F3 */
