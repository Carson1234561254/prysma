#include "Compilateur/AST/Utils/OrchestrateurInclude/UniteCompilation.h"
#include "Compilateur/AST/Utils/ConstructeurEnvironnementRegistreFonction.h"
#include "Compilateur/AST/Utils/ConstructeurEnvironnementRegistreVariable.h"
#include "Compilateur/AST/Utils/OrchestrateurInclude/OrchestrateurInclude.h"
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
#include <filesystem>
#include <iostream>
#include <vector>

UniteCompilation::UniteCompilation(OrchestrateurInclude* orchestrateur, RegistreFichier* registre, std::string cheminFichier, RegistreFonctionGlobale* registreFonctionGlobale) 
    : _orchestrateur(orchestrateur), 
      _registreFichier(registre),
      _cheminFichierOriginal(std::move(cheminFichier)),
      _context(nullptr),
      _arbre(nullptr) 
{
    // Initialisation du contexte séparé (la bulle privée)
    _facadeConfigurationEnvironnement = std::make_unique<FacadeConfigurationEnvironnement>(registreFonctionGlobale, _registreFichier);
}

UniteCompilation::~UniteCompilation() 
{
    _arbre = nullptr; 
    _context = nullptr; 
}

void UniteCompilation::passe1() {
    // Résoudre le chemin absolu du fichier
    std::filesystem::path cheminAbsolu = std::filesystem::absolute(_cheminFichierOriginal);
    
    // Si le chemin est relatif et qu'on a un répertoire courant, résoudre par rapport à celui-ci
    if (!std::filesystem::exists(cheminAbsolu) && !_repertoireCourant.empty()) {
        cheminAbsolu = std::filesystem::path(_repertoireCourant) / _cheminFichierOriginal;
    }
    
    std::string cheminResolu = cheminAbsolu.string();
    
    // Sauvegarder le répertoire courant pour les includes imbriqués
    _ancienRepertoire = _repertoireCourant;
    _repertoireCourant = cheminAbsolu.parent_path().string();

    std::string pathProgramme = "programme/";
    
    _nomFichier = cheminResolu.substr(cheminResolu.find_last_of("/\\") + 1);
    _nomFichier = _nomFichier.substr(0, _nomFichier.find_last_of('.'));

    _registreFichier->ajouterFichier(pathProgramme + _nomFichier + ".ll");

    _facadeConfigurationEnvironnement->initialiser();

    _context = _facadeConfigurationEnvironnement->getContext();
    ConstructeurArbreInstruction* constructeurArbreInstruction = _facadeConfigurationEnvironnement->getConstructeurArbreInstruction();

    FichierLecture fichierLecture(cheminResolu);
    std::string document = fichierLecture.entrer();

    Lexer lexer;
    std::vector<Token> tokens = lexer.tokenizer(document);

    _arbre = constructeurArbreInstruction->construire(tokens);

    VisiteurRemplissageRegistre visiteurRemplissageRegistre(_context, _orchestrateur);
    _arbre->accept(&visiteurRemplissageRegistre);

    ConstructeurEnvironnementRegistreFonction constructeurEnvironnementRegistreFonction(_context);
    constructeurEnvironnementRegistreFonction.remplir();

    ConstructeurEnvironnementRegistreVariable constructeurEnvironnementRegistreVariable(_context);
    constructeurEnvironnementRegistreVariable.remplir();
}

void UniteCompilation::passe2() {
    std::string pathProgramme = "programme/";
    std::string pathGraphe = "graphe/";

    VisiteurGeneralGenCode visiteur(_context, _orchestrateur);
    _arbre->accept(&visiteur);

    SortieGrapheVisuelTexte sortieGrapheVisuel(pathGraphe + _nomFichier + ".dot");
    VisiteurGeneralGraphViz visiteurGraphViz(std::move(sortieGrapheVisuel));
    _arbre->accept(&visiteurGraphViz);
    visiteurGraphViz.generer();

    if (system(("dot -Tsvg " + pathGraphe + _nomFichier + ".dot -o " + pathGraphe + _nomFichier + ".svg").c_str()) != 0) {
        std::cerr << "Erreur lors de la génération du graphe." << std::endl;
    }

    // Supprimer le fichier .dot intermédiaire
    if (system(("rm " + pathGraphe + _nomFichier + ".dot").c_str()) != 0) {
        std::cerr << "Erreur lors de la suppression du fichier .dot." << std::endl;
    }

    LlvmSerializer serializer(_context->backend->getContext(), _context->backend->getModule());
    serializer.SauvegarderCodeLLVM(pathProgramme + _nomFichier + ".ll"); 

    // Restaurer le répertoire courant pour les includes au même niveau
    _repertoireCourant = _ancienRepertoire;
}