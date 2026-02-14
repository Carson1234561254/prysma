#ifndef F158F3CA_48BA_406A_A611_87940EE9E015
#define F158F3CA_48BA_406A_A611_87940EE9E015

#include "Compilateur/AST/Noeuds/NoeudInstruction.h"
#include <memory>

class INoeud;
class VisiteurGeneralGenCode;
class GestionFonction;

class NoeudWhile : public NoeudInstruction
{
private: 
    std::shared_ptr<INoeud> noeudCondition;
    std::shared_ptr<INoeud> noeudBlocWhile;
    std::shared_ptr<INoeud> noeudBlocFinWhile;

public: 
    NoeudWhile();
    NoeudWhile(std::shared_ptr<INoeud>&& condition, std::shared_ptr<INoeud>&& blocWhile, std::shared_ptr<INoeud>&& blocEndWhile);
    ~NoeudWhile();
    
    void accept(IVisiteur* visiteur) override;

    const std::shared_ptr<INoeud>& getNoeudCondition() const { return noeudCondition; }
    const std::shared_ptr<INoeud>& getNoeudBlocWhile() const { return noeudBlocWhile; }
    const std::shared_ptr<INoeud>& getNoeudBlocFinWhile() const { return noeudBlocFinWhile; }
};

#endif /* F158F3CA_48BA_406A_A611_87940EE9E015 */
