import yaml

FICHIER_YAML = "YamelAST/ast.yaml"
FICHIER_H = "AST_Genere.h"

def analyser_parametre(type_c):
    if "std::" in type_c or type_c == "Token":
        return type_c, "std::move({nom})"
    if "*" in type_c or type_c in ["int", "float", "double", "bool", "char", "TokenType"]:
        return type_c, "{nom}"
    return type_c, "{nom}"

def type_retour_getter(type_c):
    if "*" in type_c or type_c in ["int", "float", "double", "bool", "char", "TokenType"]:
        return type_c
    return f"const {type_c}&"

def extraire_donnees_noeud(data):
    if data is None: data = {}
    parent = data.get("parent", "INoeud")
    proprietes = data.get("champs", {})
    if not proprietes and "parent" not in data:
        proprietes = data
    return parent, proprietes

def ecrire_en_tete(fh):
    fh.write("#ifndef AST_GENERE_H\n")
    fh.write("#define AST_GENERE_H\n\n")
    fh.write('#include "Compilateur/AST/Noeuds/Interfaces/INoeud.h"\n')
    fh.write('#include "Compilateur/AST/Noeuds/Interfaces/IExpression.h"\n')
    fh.write('#include "Compilateur/AST/Noeuds/NoeudInstruction.h"\n')
    fh.write('#include "Compilateur/Visiteur/Interfaces/IVisiteur.h"\n')
    fh.write('#include "Compilateur/Lexer/Lexer.h"\n')
    fh.write('#include <string>\n')
    fh.write('#include <vector>\n')
    fh.write('#include <utility>\n')
    fh.write('#include "Compilateur/AST/Registre/Types/IType.h"\n\n')

def ecrire_forward_declarations(fh, noeuds):
    for nom_noeud in noeuds.keys():
        fh.write(f"class Noeud{nom_noeud};\n")
    fh.write("\n")

def ecrire_attributs_prives(fh, proprietes):
    fh.write("private:\n")
    for prop_nom, prop_type in proprietes.items():
        fh.write(f"    {prop_type} _{prop_nom};\n")
    fh.write("\n")

def ecrire_constructeurs(fh, nom_classe, proprietes):
    fh.write("public:\n")
    fh.write(f"    {nom_classe}() = default;\n")
    if proprietes:
        params, inits = [], []
        for prop_nom, prop_type in proprietes.items():
            type_param, format_init = analyser_parametre(prop_type)
            params.append(f"{type_param} {prop_nom}")
            inits.append(f"_{prop_nom}({format_init.format(nom=prop_nom)})")
        fh.write(f"    {nom_classe}({', '.join(params)}) : {', '.join(inits)} {{}}\n")

def ecrire_methodes(fh, nom_classe, parent, proprietes):
    fh.write(f"    ~{nom_classe}() override = default;\n\n")
    fh.write("    void accept(IVisiteur* visiteur) override {\n")
    fh.write("        visiteur->visiter(this);\n")
    fh.write("    }\n\n")
    if parent == "IExpression":
        fh.write("    IExpression* ajouterExpression(INoeud* gauche, INoeud* droite) override {\n")
        if "gauche" in proprietes:
            fh.write("        _gauche = gauche;\n")
        if "droite" in proprietes:
            fh.write("        _droite = droite;\n")
        fh.write("        return this;\n")
        fh.write("    }\n\n")

def ecrire_getters(fh, proprietes):
    for prop_nom, prop_type in proprietes.items():
        ret_type = type_retour_getter(prop_type)
        nom_maj = prop_nom[0].upper() + prop_nom[1:]
        fh.write(f"    {ret_type} get{nom_maj}() const {{ return _{prop_nom}; }}\n")

def generer_classe_noeud(fh, nom_noeud, data):
    parent, proprietes = extraire_donnees_noeud(data)
    nom_classe = f"Noeud{nom_noeud}"
    fh.write(f"class {nom_classe} : public {parent} {{\n")
    ecrire_attributs_prives(fh, proprietes)
    ecrire_constructeurs(fh, nom_classe, proprietes)
    ecrire_methodes(fh, nom_classe, parent, proprietes)
    ecrire_getters(fh, proprietes)
    fh.write("};\n\n")

def generer_ast():
    with open(FICHIER_YAML, "r", encoding="utf-8") as f:
        ast_data = yaml.safe_load(f)
    noeuds = ast_data.get("Noeud", {})
    with open(FICHIER_H, "w", encoding="utf-8") as fh:
        ecrire_en_tete(fh)
        ecrire_forward_declarations(fh, noeuds)
        for nom_noeud, data in noeuds.items():
            generer_classe_noeud(fh, nom_noeud, data)
        fh.write("#endif\n")

if __name__ == "__main__":
    generer_ast()