import os
from generation.moteur_generation import MoteurGeneration

class GenerateurParseur(MoteurGeneration):
    def __init__(self, racine_projet):
        super().__init__(racine_projet)
        self._mapping_noeud_categorie = self._construire_mapping_noeud_categorie()
        self._dossier_squelettes = os.path.join(racine_projet, "src", "Compilateur", "AnalyseSyntaxique")
        self._mapping_special_parseurs = {
            "Equation": "Instruction",
            "Instruction": "Equation",
        }
 

    def generer(self):
        noeuds = list(self._charger_noeuds_yaml().keys()) + ["Instruction"] + ["Equation"]
        for nom in noeuds:
            chemin_sortie = self._resoudre_chemin_entete(nom)
            self._rendre_et_ecrire("Parseur.h.j2", chemin_sortie, nom=nom)
            self._generer_squelette_source_si_absent(nom)

    def _resoudre_chemin_entete(self, nom_noeud):
        categorie = self._resoudre_categorie_parseur(nom_noeud)
        return self._chemin_generation_include(
            self._chemin_depuis_categorie(categorie, f"Parseur{nom_noeud}.h")
        )

    def _resoudre_chemin_squelette(self, nom_noeud):
        categorie = self._resoudre_categorie_parseur(nom_noeud)
        if categorie == "AnalyseSyntaxique":
            return os.path.join(self._dossier_squelettes, f"Parseur{nom_noeud}.cpp")
        return os.path.join(self._dossier_squelettes, categorie, f"Parseur{nom_noeud}.cpp")

    def _generer_squelette_source_si_absent(self, nom_noeud):
        chemin_source = self._resoudre_chemin_squelette(nom_noeud)
        include_parseur = self._resoudre_include_parseur(nom_noeud)
        self._rendre_et_ecrire_si_absent(
            "Parseur.cpp.j2",
            chemin_source,
            nom=nom_noeud,
            include_parseur=include_parseur,
        )

    def _resoudre_include_parseur(self, nom_noeud):
        categorie = self._resoudre_categorie_parseur(nom_noeud)
        return "/".join([
            "Compilateur",
            categorie,
            f"Parseur{nom_noeud}.h",
        ])

    def _resoudre_categorie_parseur(self, nom_noeud):
        if nom_noeud in self._mapping_special_parseurs:
            return self._mapping_special_parseurs[nom_noeud]
        return self._mapping_noeud_categorie.get(nom_noeud, "AnalyseSyntaxique")

    