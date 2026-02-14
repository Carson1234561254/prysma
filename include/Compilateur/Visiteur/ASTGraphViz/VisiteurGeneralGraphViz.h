#ifndef EF0EE0D7_D8CD_4A7D_BB3B_78249CA1F8AB
#define EF0EE0D7_D8CD_4A7D_BB3B_78249CA1F8AB

#include <llvm-18/llvm/IR/Value.h>
#include "Compilateur/AST/Registre/ContextGenCode.h"
#include "Compilateur/AST/Noeuds/Equation/NoeudOperation.h"
#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"
#include "Compilateur/Visiteur/MacroGenerationVisiteur.h"
#include "Compilateur/GrapheVisuel/SortieGrapheVisuelTexte.h"


//Outils 
CLASS_NOEUD

class VisiteurGeneralGraphViz : public IVisiteur
{ 
private:
 SortieGrapheVisuelTexte _sortieGrapheVisuel;
    
public:
    VisiteurGeneralGraphViz(SortieGrapheVisuelTexte sortieGrapheVisuel);
    ~VisiteurGeneralGraphViz();
        
    DECLARER_METHODES_VISITEUR
};

#endif /* FDDB5968_6DEF_49B0_AD11_8791D523278A */


