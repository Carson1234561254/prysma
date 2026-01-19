#ifndef F2D02E97_AF62_409B_84AD_90905E9BE240
#define F2D02E97_AF62_409B_84AD_90905E9BE240
#include <map>
#include <string>
#include <vector>

using namespace std;
// lexer utilisée pour la tokenization du code source prysma
// filtre le code source en une liste de tokens identifier 
class Lexer {
    private: 

    string sourceCodeTeste = "def int maFonction(int a, float b) {\n"
                             "    if (a == 10) {\n"
                             "        return b + 5.0\n"
                             "    } else {\n"
                             "        return b - 5.0\n"
                             "    }\n"
                             "def int x = maFonction(10, 20.5);\n"
                             ""
                             "}\n";

        enum TokenType {
            // Fin de flux (Obligatoire)
            TOKEN_EOF,

            // Littéraux la valeur directe "string", 123, 12.34, true/false
            TOKEN_LIT_INT, 
            TOKEN_LIT_FLOAT,
            TOKEN_LIT_CHAINE,
            TOKEN_LIT_BOLEEN,

            TOKEN_IDENTIFIANT,  

            TOKEN_PLUS,         
            TOKEN_MOINS,        
            TOKEN_ETOILE,       
            TOKEN_SLASH,  
            TOKEN_PLUS_PETIT,
            TOKEN_PLUS_GRAND,      
 
            TOKEN_EGAL,         
            TOKEN_EGAL_EGAL,    

            // Structure
            TOKEN_PAREN_OUVERTE,
            TOKEN_PAREN_FERMEE,
            TOKEN_VIRGULE,      
            
            // Mots-clés (Mieux vaut être spécifique)
            TOKEN_FONCTION,    
            TOKEN_SI,          
            TOKEN_SINON,       
            TOKEN_TANT_QUE,     
            TOKEN_RETOUR,    

            // variable 
            TOKEN_TYPE_INT,
            TOKEN_TYPE_FLOAT,
            TOKEN_TYPE_STRING,
            TOKEN_TYPE_BOOL, 
            TOKEN_TYPE_VOID  
        };

    struct Token {
        TokenType type;
        string value;
    };

    vector<Token> tokens;

    // Dictionnaire pour les mots réservé du langage de programmation prysma
    // Permet de différencier les identifiants des mots-clés
    map<string, TokenType> motsCles = {
        {"def", TOKEN_FONCTION},
        {"if", TOKEN_SI},
        {"else", TOKEN_SINON},
        {"while", TOKEN_TANT_QUE},
        {"return", TOKEN_RETOUR},
        {"int", TOKEN_TYPE_INT},
        {"float", TOKEN_TYPE_FLOAT},
        {"string", TOKEN_TYPE_STRING},
        {"bool", TOKEN_TYPE_BOOL},
        {"void", TOKEN_TYPE_VOID},
        
    };

    
    public: 
        Lexer() {}
        ~Lexer() {}



};

#endif /* F2D02E97_AF62_409B_84AD_90905E9BE240 */
