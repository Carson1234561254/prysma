#include "Compilateur/AST/ConstructeurArbreInstruction.h"
#include "Compilateur/LLVM/LLVMBackend.h"
#include "Compilateur/Lexer/Lexer.h"
#include "Compilateur/Lexer/TokenType.h"
#include "Compilateur/Parsing/Instruction/Variable/ParseurAffectation.h"
#include "Compilateur/Parsing/Instruction/Variable/ParseurDeclaration.h"
#include "Compilateur/TraitementFichier/FichierLecture.h"
#include "Compilateur/AST/Registre/RegistreVariable.h"
#include "Compilateur/AST/Registre/RegistreFonction.h"
#include <iostream>
#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/IR/Value.h>
#include <memory>
#include "Compilateur/AST/Registre/RegistreInstruction.h"
#include "Compilateur/Parsing/Instruction/ParserMain.h"
#include "Compilateur/Parsing/Instruction/Fonction/ParsingDeclarationFonction.h"
#include "Compilateur/Parsing/Instruction/Return/ParsingReturn.h"

using namespace std;

int main() {
    try {
        shared_ptr<LLVMBackend> backend = std::make_shared<LLVMBackend>();

        std::string document;
        FichierLecture fichierLecture("../src/PrysmaCodeTests/main.prysma");
        document = fichierLecture.entrer();
  
        Lexer lexer;
        vector<Token> tokens = lexer.tokenizer(document);

        std::shared_ptr<RegistreInstruction> registreInstruction = std::make_shared<RegistreInstruction>();
        std::shared_ptr<RegistreVariable> registreVariable = std::make_shared<RegistreVariable>();
        std::shared_ptr<RegistreFonction> registreFonction = std::make_shared<RegistreFonction>();
        
        registreInstruction->enregistrer(TOKEN_SCOPE, std::make_shared<ParserMain>());
        registreInstruction->enregistrer(TOKEN_FONCTION, std::make_shared<ParsingDeclarationFonction>(backend, registreFonction, TOKEN_FONCTION));
        registreInstruction->enregistrer(TOKEN_AFF, std::make_shared<ParseurAffectation>(backend, registreVariable,TOKEN_TYPE_FLOAT));
        registreInstruction->enregistrer(TOKEN_DEC,std::make_shared<ParseurDeclaration>(backend, registreVariable,TOKEN_TYPE_FLOAT));
        registreInstruction->enregistrer(TOKEN_RETOUR, std::make_shared<ParsingReturn>(backend));

        ConstructeurArbreInstruction constructeurArbreInstruction(registreInstruction);

        std::shared_ptr<INoeud> arbre = constructeurArbreInstruction.construire(tokens);

        arbre->genCode();

        backend->sauvegarderCodeLLVM("output.ll");

        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << std::endl;
        return 1;
    }
}