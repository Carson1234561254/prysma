import os
import shutil
from tests.orchestration.build_manager import BuildManager
from generation.generator_ast import GenerateurAST
from generation.generator_interface_visitor import GenerateurInterfaceVisitor
from generation.generator_visitor_base_general import GenerateurVisitorBaseGenerale
from generation.generator_visitor_destruction import GenerateurVisitorDestruction
from generation.generator_graphe_viz import GenerateurGraphViz
from generation.generator_expression import GenerateurExpression
from generation.generator_parser import GenerateurParser

def main():
    dossier_script = os.path.dirname(os.path.abspath(__file__))
    os.chdir(dossier_script)

    GenerateurAST(dossier_script).generatedr()
    GenerateurInterfaceVisitor(dossier_script).generatedr()
    GenerateurVisitorBaseGenerale(dossier_script).generatedr()
    GenerateurVisitorDestruction(dossier_script).generatedr()
    GenerateurGraphViz(dossier_script).generatedr()
    GenerateurExpression(dossier_script).generatedr()
    GenerateurParser(dossier_script).generatedr()

    cxxflags_list = [
            "-O3",                  # Vitesse brute (optimisation maximale)
            "-march=native",        # Exploitation totale des instructions de ton CPU
            "-ffast-math",          # Calculs mathématiques agressifs
            "-fno-rtti",            # Zéro métadonnée d'exécution (RTTI off)
            "-fomit-frame-pointer", # Libération d'un registry CPU
            "-flto",                # Fusion et optimisation globale au linkage (LTO)
            "-DNDEBUG"              # Désactivation absolue des assertions
    ]
    
    ldflags_list = [
        "-flto",
        "-Wl,--gc-sections",
        "-Wl,-s",
        "-fuse-ld=lld"
    ]

    cxxflags = " ".join(cxxflags_list)
    ldflags = " ".join(ldflags_list)

    BuildManager.executer_commande([
        "cmake", "-S", ".", "-B", "build", 
        "-DCMAKE_BUILD_TYPE=Release",
        f"-DCMAKE_CXX_FLAGS={cxxflags}",
        f"-DCMAKE_EXE_LINKER_FLAGS={ldflags}", 
        f"-DCMAKE_MODULE_LINKER_FLAGS={ldflags}",
        f"-DCMAKE_SHARED_LINKER_FLAGS={ldflags}",
        "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
    ])

    os.makedirs("build", exist_ok=True)
    shutil.rmtree(os.path.join("build", "obj"), ignore_errors=True)

    nb_coeurs = str(os.cpu_count() or 1)

    BuildManager.executer_commande([
        "cmake", "--build", "build", "--parallel", nb_coeurs
    ])
    
if __name__ == "__main__":
    main()