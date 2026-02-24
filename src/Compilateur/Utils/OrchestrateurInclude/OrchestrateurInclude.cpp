#include "Compilateur/AST/Registre/RegistreFonction.h"
#include "Compilateur/AST/Utils/OrchestrateurInclude/FacadeConfigurationEnvironnement.h"
#include "Compilateur/AST/Utils/OrchestrateurInclude/OrchestrateurInclude.h"
#include "Compilateur/AST/Utils/ConstructeurEnvironnementRegistreFonction.h"
#include "Compilateur/AST/Utils/ConstructeurEnvironnementRegistreVariable.h"
#include "Compilateur/TraitementFichier/FichierLecture.h"
#include "Compilateur/Lexer/Lexer.h"
#include "Compilateur/GrapheVisuel/SortieGrapheVisuelTexte.h"
#include "Compilateur/LLVM/LlvmSerializer.h"
#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/Visiteur/VisiteurRemplissageRegistre/VisiteurRemplissageRegistre.h"
#include <llvm-18/llvm/IR/DerivedTypes.h>
#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/IR/Value.h>
#include <cstdlib>
#include <string>

OrchestrateurInclude::OrchestrateurInclude(FacadeConfigurationEnvironnement* facadeConfigurationEnvironnement, RegistreFonction* registreFonctionGlobale, RegistreFichier* registreFichier) : 
_facadeConfigurationEnvironnement(facadeConfigurationEnvironnement),
_registreFonctionGlobale(registreFonctionGlobale),
_registreFichier(registreFichier)
{}

OrchestrateurInclude::~OrchestrateurInclude()
{}

void OrchestrateurInclude::nouvelleInstance(const std::string& cheminFichier) {

    std::string pathProgramme = "programme/";
    std::string pathGraphe = "graphe/";
    
    std::string nomFichier = cheminFichier.substr(cheminFichier.find_last_of("/\\") + 1);
    nomFichier = nomFichier.substr(0, nomFichier.find_last_of('.'));

    _registreFichier->ajouterFichier(pathProgramme + nomFichier + ".ll");

    _facadeConfigurationEnvironnement->initialiser();

    ContextGenCode* context = _facadeConfigurationEnvironnement->getContext();
    ConstructeurArbreInstruction* constructeurArbreInstruction = _facadeConfigurationEnvironnement->getConstructeurArbreInstruction();

    FichierLecture fichierLecture(cheminFichier);
    std::string document = fichierLecture.entrer();

    Lexer lexer;
    vector<Token> tokens = lexer.tokenizer(document);

    INoeud* arbre = constructeurArbreInstruction->construire(tokens);

    VisiteurRemplissageRegistre visiteurRemplissageRegistre(context);
    arbre->accept(&visiteurRemplissageRegistre);

    ConstructeurEnvironnementRegistreFonction constructeurEnvironnementRegistreFonction(context);
    constructeurEnvironnementRegistreFonction.remplir();

    ConstructeurEnvironnementRegistreVariable constructeurEnvironnementRegistreVariable(context);
    constructeurEnvironnementRegistreVariable.remplir();

    VisiteurGeneralGenCode visiteur(context);
    arbre->accept(&visiteur);

    SortieGrapheVisuelTexte sortieGrapheVisuel(pathGraphe+nomFichier+".dot");
    VisiteurGeneralGraphViz visiteurGraphViz(std::move(sortieGrapheVisuel));
    arbre->accept(&visiteurGraphViz);
    visiteurGraphViz.generer();

    if (system(("dot -Tsvg " + pathGraphe + nomFichier + ".dot -o " + pathGraphe + nomFichier + ".svg").c_str()) != 0) {
        std::cerr << "Erreur lors de la génération du graphe." << std::endl;
    }

    // Supprimer le fichier .dot intermédiaire
    if (system(("rm " + pathGraphe + nomFichier + ".dot").c_str()) != 0) {
        std::cerr << "Erreur lors de la suppression du fichier .dot." << std::endl;
    }

    LlvmSerializer serializer(context->backend->getContext(), context->backend->getModule());
    serializer.SauvegarderCodeLLVM(pathProgramme + nomFichier + ".ll"); 
}
