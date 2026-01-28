#include "Compilateur/AST/ConstructeurArbreEquation.h"
#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"
#include "Compilateur/Parsing/Equation/ChaineResponsabilite.h"
#include "Compilateur/Parsing/Equation/ServiceParenthese.h"
#include "Compilateur/Parsing/Equation/GestionnaireOperateur.h"
#include "Compilateur/AST/Noeuds/Operande/Operation.h"
#include <llvm-18/llvm/IR/IRBuilder.h>

class FloatEquationBuilder
{
    private:

    llvm::IRBuilder<> builder;

    std::shared_ptr<RegistreSymbole> registreSymboleFloat;

    ChaineResponsabilite* chaineResponsabilite;
 
    GestionnaireOperateur* gestionnaireAddition;
    GestionnaireOperateur* gestionnaireSoustraction;
    GestionnaireOperateur* gestionnaireMultiplication;
    GestionnaireOperateur* gestionnaireDivision;

    ServiceParenthese* serviceParenthese;
        
    ConstructeurArbreEquation* constructeurArbreEquation;
    
    void construireRegistreSymboleFloat();
  
    public: 

    FloatEquationBuilder(llvm::LLVMContext &context) : builder(context)
    {

       
        registreSymboleFloat = std::make_shared<RegistreSymbole>();

        serviceParenthese = new ServiceParenthese(registreSymboleFloat);

        gestionnaireAddition = new GestionnaireOperateur(TOKEN_PLUS);
        gestionnaireSoustraction = new GestionnaireOperateur(TOKEN_MOINS);
        gestionnaireMultiplication = new GestionnaireOperateur(TOKEN_ETOILE);
        gestionnaireDivision = new GestionnaireOperateur(TOKEN_SLASH);


        std::vector<GestionnaireOperateur*> operateurs = {
            gestionnaireAddition, gestionnaireSoustraction, 
            gestionnaireMultiplication, gestionnaireDivision
        };
                
        chaineResponsabilite = new ChaineResponsabilite(serviceParenthese, operateurs);
                        
        // ===== Construction de l'AST et Résolution =====
        constructeurArbreEquation = new ConstructeurArbreEquation(
            chaineResponsabilite, registreSymboleFloat, serviceParenthese, context
        );

        construireRegistreSymboleFloat();
    }
    
    ~FloatEquationBuilder()
    {
        delete constructeurArbreEquation;
        delete chaineResponsabilite;
        delete gestionnaireAddition; 
        delete gestionnaireSoustraction;
        delete gestionnaireMultiplication; 
        delete gestionnaireDivision;
        delete serviceParenthese;
    }
    
    shared_ptr<INoeud> builderArbreEquationFloat(vector<Token> &tokens);
};