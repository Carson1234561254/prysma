import subprocess
import os
from Tests.Orchestration.build_manager import BuildManager


def main():
    # Obtenir le répertoire racine du projet
    script_dir = os.path.dirname(os.path.abspath(__file__))
    os.chdir(script_dir)
    
    BuildManager.executer_commande(["cmake", "-S", ".", "-B", "build"])
    os.makedirs("build", exist_ok=True)

    ast_path = os.path.join(script_dir, "include", "Compilateur", "AST")
    os.chdir(ast_path)
    BuildManager.executer_commande(["python3", "GenerationAST.py"])
    os.chdir(script_dir)

    nb_coeurs = str(os.cpu_count() or 1)
    cxxflags = "-Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wnull-dereference -Wformat=2 -Werror"

    BuildManager.executer_commande([
        "bear", "--output", "build/compile_commands.json", "--", 
        "make", f"-j{nb_coeurs}", 
        f"CXXFLAGS={cxxflags}"
    ])
    
if __name__ == "__main__":
    main()