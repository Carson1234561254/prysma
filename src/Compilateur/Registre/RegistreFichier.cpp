#include "Compilateur/Registre/RegistreFichier.h"

void RegistreFichier::ajouterFichier(const std::string& cheminFichier) {
    std::lock_guard<std::mutex> lock(mtx);
    fichiersTraites.insert(cheminFichier);
}

bool RegistreFichier::verifierFichier(const std::string& cheminFichier) {
    std::lock_guard<std::mutex> lock(mtx);
    return fichiersTraites.count(cheminFichier) > 0;
}

std::vector<std::string> RegistreFichier::obtenirTousLesFichiers() {
    std::lock_guard<std::mutex> lock(mtx);
    return std::vector<std::string>(fichiersTraites.begin(), fichiersTraites.end());
}
