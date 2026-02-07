#ifndef DC6C556F_6309_4430_98EB_911BFF855216
#define DC6C556F_6309_4430_98EB_911BFF855216

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include <llvm-18/llvm/IR/Value.h>
#include <memory>
#include "Compilateur/Visiteur/AmisVisiteurs.h"

class NoeudReturn : public INoeud
{
    LISTE_DES_AMIS_VISITEURS
private:
    std::shared_ptr<INoeud> _valeurRetour;

public:
    explicit NoeudReturn(std::shared_ptr<INoeud> valeurRetour);
    ~NoeudReturn() = default;

    void accept(IVisiteur* visiteur) override;
};

#endif /* DC6C556F_6309_4430_98EB_911BFF855216 */
