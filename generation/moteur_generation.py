import yaml
import os
from jinja2 import Environment, FileSystemLoader


class MoteurGeneration:

    def __init__(self, racine_projet):
        self._racine = racine_projet
        self._fichier_yaml = os.path.join(racine_projet, "include", "Compilateur", "AST", "YamelAST", "ast.yaml")
        self._generation_code = os.path.join(racine_projet, "build", "generationCode")
        self._generation_include = os.path.join(self._generation_code, "include")
        self._generation_src = os.path.join(self._generation_code, "src")
        self._env = Environment(
            loader=FileSystemLoader(os.path.join(racine_projet, "generation", "templates")),
            trim_blocks=True,
            lstrip_blocks=True
        )

    def _charger_noeuds_yaml(self):
        with open(self._fichier_yaml, "r", encoding="utf-8") as fichier:
            noeuds = yaml.safe_load(fichier).get("Noeud", {})
        return self._applatir_noeuds(noeuds)

    def _charger_noeuds_yaml_par_categories(self):
        with open(self._fichier_yaml, "r", encoding="utf-8") as fichier:
            return yaml.safe_load(fichier).get("Noeud", {})
        
    def _applatir_noeuds(self, noeuds):
        noeuds_applatir = {}
        for _, donnees in noeuds.items():
            noeuds_applatir.update(donnees)
           
        return noeuds_applatir
    
    def _rendre_et_ecrire(self, nom_template, chemin_sortie, **kwargs):
        contenu = self._env.get_template(nom_template).render(**kwargs)
        os.makedirs(os.path.dirname(chemin_sortie), exist_ok=True)
        with open(chemin_sortie, "w", encoding="utf-8") as fichier:
            fichier.write(contenu)

    def _rendre_et_ecrire_si_absent(self, nom_template, chemin_sortie, **kwargs):
        if os.path.exists(chemin_sortie):
            return False
        self._rendre_et_ecrire(nom_template, chemin_sortie, **kwargs)
        return True

    def _chemin_generation_include(self, *segments):
        return os.path.join(self._generation_include, *segments)

    def _chemin_generation_src(self, *segments):
        return os.path.join(self._generation_src, *segments)

    def _chemin_depuis_categorie(self, categorie, *segments):
        return os.path.join("Compilateur", categorie, *segments)

    def _construire_mapping_noeud_categorie(self):
        mapping = {}
        for categorie, noeuds in self._charger_noeuds_yaml_par_categories().items():
            for nom_noeud in (noeuds or {}).keys():
                mapping[nom_noeud] = categorie
        return mapping

    @staticmethod
    def _extraire_traversables(champs):
        resultats = []
        for nom_champ, type_champ in champs.items():
            if type_champ in ("INoeud*", "std::vector<INoeud*>"):
                getter = "get" + nom_champ[0].upper() + nom_champ[1:]
                resultats.append((getter, type_champ))
        return resultats
