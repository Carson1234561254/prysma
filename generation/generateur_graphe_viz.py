import yaml
import os
import re


class GenerateurGrapheViz:

    LABELS = {
        "Include":              '"Include: " + noeud->getPath()',
        "DeclarationVariable":  '"Declaration: " + noeud->getNom()',
        "DeclarationFonction":  '"Declaration Fonction: " + noeud->getNom()',
        "ArgFonction":          '"Argument: " + noeud->getNom()',
        "AffectationVariable":  '"Affectation: " + noeud->getNom()',
        "AffectationTableau":   '"Affectation Tableau: " + noeud->getNom()',
        "Retour":               '"Retour"',
        "If":                   '"If"',
        "While":                '"While"',
        "Operation":            'noeud->getToken().value',
        "Litteral":             '"Litteral: " + noeud->getToken().value',
        "AppelFonction":        '"Appel Fonction: " + noeud->getNomFonction().value',
        "LectureTableau":       '"Lecture: " + noeud->getNomTableau().value',
        "TableauInitialisation": '"[...]"',
        "Negation":             '"!"',
        "RefVariable":          '"Ref: " + noeud->getNomVariable()',
        "UnRefVariable":        '"UnRef: " + noeud->getNomVariable()',
        "New":                  '"New " + noeud->getNomType().value',
    }

    ENFANTS_HERITES = {
        "AppelFonction": [("getEnfants", "std::vector<INoeud*>")],
    }

    def __init__(self, racine_projet):
        self._racine = racine_projet
        self._fichier_yaml = os.path.join(racine_projet, "include", "Compilateur", "AST", "YamelAST", "ast.yaml")
        self._dossier_sortie = os.path.join(racine_projet, "build", "generationCode", "Compilateur", "Visiteur", "ASTGraphViz")

    def generer(self):
        noeuds = self._charger_noeuds()
        self._generer_header(noeuds)
        self._generer_cpp(noeuds)

    def _charger_noeuds(self):
        with open(self._fichier_yaml, "r", encoding="utf-8") as f:
            return yaml.safe_load(f).get("Noeud", {})

    def _generer_header(self, noeuds):
        noms = list(noeuds.keys()) + ["Instruction"]
        contenu = "#ifndef VISITEUR_GENERAL_GRAPHVIZ_H\n"
        contenu += "#define VISITEUR_GENERAL_GRAPHVIZ_H\n\n"
        contenu += '#include "Compilateur/GrapheVisuel/SortieGrapheVisuelTexte.h"\n'
        contenu += '#include "Compilateur/Visiteur/VisiteurBaseGenerale.h"\n\n'
        for nom in noms:
            contenu += f"class Noeud{nom};\n"
        contenu += "\n"
        contenu += "class VisiteurGeneralGraphViz : public VisiteurBaseGenerale\n{\nprivate:\n"
        contenu += "    SortieGrapheVisuelTexte _sortieGrapheVisuel;\n"
        contenu += "    int _dernierId;\n\n"
        contenu += "public:\n"
        contenu += "    VisiteurGeneralGraphViz(SortieGrapheVisuelTexte sortieGrapheVisuel);\n"
        contenu += "    ~VisiteurGeneralGraphViz() override;\n"
        contenu += "    void generer();\n\n"
        for nom in noms:
            contenu += f"    void visiter(Noeud{nom}* noeud{nom}) override;\n"
        contenu += "};\n\n"
        contenu += "#endif\n"
        self._ecrire_fichier(os.path.join(self._dossier_sortie, "VisiteurGeneralGraphViz.h"), contenu)

    def _generer_cpp(self, noeuds):
        contenu = '#include "Compilateur/Visiteur/ASTGraphViz/VisiteurGeneralGraphViz.h"\n'
        contenu += '#include "Compilateur/AST/AST_Genere.h"\n'
        contenu += '#include "Compilateur/AST/Noeuds/NoeudInstruction.h"\n\n'
        contenu += "VisiteurGeneralGraphViz::VisiteurGeneralGraphViz(SortieGrapheVisuelTexte sortieGrapheVisuel)\n"
        contenu += "    : _sortieGrapheVisuel(std::move(sortieGrapheVisuel)), _dernierId(0)\n{}\n\n"
        contenu += "VisiteurGeneralGraphViz::~VisiteurGeneralGraphViz()\n{}\n\n"
        contenu += "void VisiteurGeneralGraphViz::generer()\n{\n    _sortieGrapheVisuel.generer();\n}\n\n"
        for nom, definition in noeuds.items():
            contenu += self._generer_methode_visiter(nom, definition)
        contenu += self._generer_methode_instruction()
        self._ecrire_fichier(os.path.join(self._dossier_sortie, "VisiteurGeneralGraphViz.cpp"), contenu)

    def _generer_methode_visiter(self, nom, definition):
        if definition is None:
            definition = {}
        classe = "Noeud" + nom
        label = self.LABELS.get(nom, f'"{nom}"')
        champs = definition.get("champs", {})
        traversables = self._extraire_traversables(champs)
        traversables += self.ENFANTS_HERITES.get(nom, [])

        if not traversables:
            return (
                f"void VisiteurGeneralGraphViz::visiter({classe}* noeud)\n"
                f"{{\n"
                f"    _dernierId = _sortieGrapheVisuel.ajouterNoeud({label});\n"
                f"}}\n\n"
            )

        contenu = f"void VisiteurGeneralGraphViz::visiter({classe}* noeud)\n{{\n"
        contenu += f"    int idNoeud = _sortieGrapheVisuel.ajouterNoeud({label});\n\n"
        for getter, type_champ in traversables:
            contenu += self._generer_visite_enfant(getter, type_champ)
        contenu += "    _dernierId = idNoeud;\n"
        contenu += "}\n\n"
        return contenu

    def _generer_visite_enfant(self, getter, type_champ):
        if type_champ == "std::vector<INoeud*>":
            contenu = f"    for (auto* element : noeud->{getter}())\n"
            contenu += "    {\n"
            contenu += "        element->accept(this);\n"
            contenu += "        _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);\n"
            contenu += "    }\n"
            return contenu
        contenu = f"    if (noeud->{getter}() != nullptr)\n"
        contenu += "    {\n"
        contenu += f"        noeud->{getter}()->accept(this);\n"
        contenu += "        _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);\n"
        contenu += "    }\n"
        return contenu

    @staticmethod
    def _generer_methode_instruction():
        contenu = "void VisiteurGeneralGraphViz::visiter(NoeudInstruction* noeud)\n{\n"
        contenu += '    int idNoeud = _sortieGrapheVisuel.ajouterNoeud("Instruction");\n\n'
        contenu += "    for (INoeud* enfant : noeud->getEnfants())\n"
        contenu += "    {\n"
        contenu += "        enfant->accept(this);\n"
        contenu += "        _sortieGrapheVisuel.ajouterArete(idNoeud, _dernierId);\n"
        contenu += "    }\n"
        contenu += "    _dernierId = idNoeud;\n"
        contenu += "}\n"
        return contenu

    @staticmethod
    def _extraire_traversables(champs):
        resultats = []
        for nom_champ, type_champ in champs.items():
            if type_champ in ("INoeud*", "std::vector<INoeud*>"):
                getter = "get" + nom_champ[0].upper() + nom_champ[1:]
                resultats.append((getter, type_champ))
        return resultats

    @staticmethod
    def _ecrire_fichier(chemin, contenu):
        os.makedirs(os.path.dirname(chemin), exist_ok=True)
        with open(chemin, "w", encoding="utf-8") as f:
            f.write(contenu)
