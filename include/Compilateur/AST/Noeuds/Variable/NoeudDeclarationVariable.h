#ifndef B18E8AB9_A311_4560_9FDD_5E2D3FAC0F14
#define B18E8AB9_A311_4560_9FDD_5E2D3FAC0F14

#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/AST/Registre/Types/IType.h"
#include <llvm/IR/Instructions.h>
#include <memory>
class NoeudDeclarationVariable : public INoeud
{
private:
    std::string _nom;
    std::shared_ptr<IType> _type;
    std::shared_ptr<INoeud> _expression;

public:
    NoeudDeclarationVariable(const std::string& nom, std::shared_ptr<IType> type, std::shared_ptr<INoeud> expression);
    ~NoeudDeclarationVariable();

    void accept(IVisiteur* visiteur) override;

    const std::string& getNom() const { return _nom; }
    std::shared_ptr<IType> getType() const { return _type; }
    std::shared_ptr<INoeud>& getExpression() { return _expression; }
};

#endif /* B18E8AB9_A311_4560_9FDD_5E2D3FAC0F14 */
