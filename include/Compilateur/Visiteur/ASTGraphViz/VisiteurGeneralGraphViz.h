#ifndef EF0EE0D7_D8CD_4A7D_BB3B_78249CA1F8AB
#define EF0EE0D7_D8CD_4A7D_BB3B_78249CA1F8AB

#include <llvm-18/llvm/IR/Value.h>
#include "Compilateur/GrapheVisuel/SortieGrapheVisuelTexte.h"
#include "Compilateur/Visiteur/VisiteurBaseGenerale.h"
#include "Compilateur/Visiteur/MacroGenerationVisiteur.h"

CLASS_NOEUD
class NoeudInclude;

class VisiteurGeneralGraphViz : public VisiteurBaseGenerale
{ 
private:
 SortieGrapheVisuelTexte _sortieGrapheVisuel;
 int _dernierId;
    
public:
    DECLARER_METHODES_VISITEUR
    void visiter(NoeudInclude* noeudInclude) override;  
    VisiteurGeneralGraphViz(SortieGrapheVisuelTexte sortieGrapheVisuel);
    ~VisiteurGeneralGraphViz();
    void generer();
        
};

#endif /* FDDB5968_6DEF_49B0_AD11_8791D523278A */


