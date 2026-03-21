#include "Compilateur/AST/Registre/RegistreFonction.h"
#include "Compilateur/AST/Utils/OrchestrateurInclude/OrchestrateurInclude.h"
#include "Compilateur/AST/Utils/OrchestrateurInclude/UniteCompilation.h"
#include "Compilateur/GestionnaireErreur.h"
#include "Compilateur/TraitementFichier/FichierLecture.h"
#include "Compilateur/Visiteur/CodeGen/VisiteurGeneralGenCode.h"
#include "Compilateur/Visiteur/VisiteurRemplissageRegistre/VisiteurRemplissageRegistre.h"
#include <iostream>
#include <llvm-18/llvm/IR/DerivedTypes.h>
#include <llvm-18/llvm/IR/Instructions.h>
#include <llvm-18/llvm/IR/Value.h>
#include <cstdlib>

#include <llvm-18/llvm/Support/ThreadPool.h>
#include <memory>
#include <mutex>
#include <string>


OrchestrateurInclude::OrchestrateurInclude(RegistreFonctionGlobale* registreFonctionGlobale, RegistreFichier* registreFichier, std::mutex* mutex, bool activerGraphViz)
    : _mutex(mutex), _registreFonctionGlobale(registreFonctionGlobale), _registreFichier(registreFichier), _activerGraphViz(activerGraphViz)
{}

OrchestrateurInclude::~OrchestrateurInclude()
= default;

auto OrchestrateurInclude::estGraphVizActif() const -> bool {
    return _activerGraphViz;
}

auto OrchestrateurInclude::aDesErreurs() const -> bool {
    return _aDesErreurs;
}

void OrchestrateurInclude::compilerProjet(const std::string& cheminFichier) 
{
    inclureFichier(cheminFichier);
    _threads.wait(); // Attendre que tous les threads finissent la passe 1 


    for(const auto& unite : _unitesCompilation) {
        UniteCompilation* ptrUnite = unite.get();
        _threads.async([this, ptrUnite] {
            try {
                ptrUnite->passe2();
            } catch (const ErreurCompilation& e) {
                std::lock_guard<std::mutex> lock(*_mutex);
                _aDesErreurs = true;
                std::cerr << "Erreur dans le fichier '" << ptrUnite->getChemin() << "': " << e.what() << std::endl;
            }
        });
    }
    _threads.wait(); // Attendre que tous les threads finissent la passe 2
}

void OrchestrateurInclude::inclureFichier(const std::string& cheminAbsolu)
{
    std::lock_guard<std::mutex> lock(*_mutex);
    if (_fichiersDejaInclus.count(cheminAbsolu) > 0) {
        return; // Le fichier a déjà été inclus, on ignore pour éviter les inclusions multiples
    }
    _fichiersDejaInclus.insert(cheminAbsolu);

   // On remplis le vecteur d'unité de compilation 
    _unitesCompilation.push_back(std::make_unique<UniteCompilation>(this, _registreFichier, cheminAbsolu, _registreFonctionGlobale));
    auto *ptrUniteNouvelle = _unitesCompilation.back().get();

    // Remplissage du pool de thread 
    _threads.async([this, ptrUniteNouvelle, cheminAbsolu] {
        try {
            ptrUniteNouvelle->passe1();
        } catch (const ErreurCompilation& e) {
            std::lock_guard<std::mutex> lock(*_mutex);
            _aDesErreurs = true;
            std::cerr << "Erreur dans le fichier '" << cheminAbsolu << "': " << e.what() << std::endl;
        }
    });

}
