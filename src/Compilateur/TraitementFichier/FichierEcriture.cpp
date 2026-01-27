#include "Compilateur/TraitementFichier/FichierEcriture.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

void FichierEcriture::sort(const std::string& data)
{
    std::ofstream fichier("sortie.txt", std::ios::out | std::ios::app);
    if (!fichier) {
        throw std::runtime_error("Erreur : impossible d'ouvrir sortie.txt pour écriture\n");
        return;
    }
    fichier << data;
    
    fichier.close();
}