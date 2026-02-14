#ifndef DC6C556F_6309_4430_98EB_911BFF855216
#define DC6C556F_6309_4430_98EB_911BFF855216

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include <llvm-18/llvm/IR/Value.h>
#include <memory>
class NoeudRetour : public INoeud
{
private:
    std::shared_ptr<INoeud> _valeurRetour;

public:
    explicit NoeudRetour(std::shared_ptr<INoeud> valeurRetour);
    ~NoeudRetour() = default;

    void accept(IVisiteur* visiteur) override;

    const std::shared_ptr<INoeud>& getValeurRetour() const { return _valeurRetour; }
};

#endif /* DC6C556F_6309_4430_98EB_911BFF855216 */
