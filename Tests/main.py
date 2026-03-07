import subprocess
import sys
import os

# Ajouter le répertoire parent au chemin Python pour les imports
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from Tests.Orchestration import build_manager
import Orchestration.test_projet_prysma
import Orchestration.test_cpp_unittest

def main():

    tableau_tests_prysma = []

    #Compilation du compilateur (génère AST_Genere.h nécessaire aux tests)
    build_manager.BuildManager.executer_commande(["python3", "../build.py"])

    # Compilation des tests 
    build_manager.BuildManager.executer_commande(["cmake", "-S", ".", "-B", "build"])
    build_manager.BuildManager.executer_commande(["cmake", "--build", "build", "-j", str(os.cpu_count() or 1)])

    test_cpp = Orchestration.test_cpp_unittest.TestCppUnittest()
    ok_cpp = test_cpp.executer_tests()

    # Test 1: ProjetTestCasLimite
    print("ProjetTestCasLimite/main.p")
    test_prysma_1 = Orchestration.test_projet_prysma.TestProjetPrysma(
        build_dirname="build", 
        compiler_name="Prysma", 
        executable_name="main", 
        file="Tests/PrysmaCodeTests/ProjetTestCasLimite/main.p"
    )
    tableau_tests_prysma.append(test_prysma_1.executer_projet())

    # Test 2: ProjetTestMultiThreadCasLimiteFichier - TestInclude
    print("\nProjetTestMultiThreadCasLimiteFichier/TestInclude/main.p")
    test_prysma_2 = Orchestration.test_projet_prysma.TestProjetPrysma(
        build_dirname="build", 
        compiler_name="Prysma", 
        executable_name="main", 
        file="Tests/PrysmaCodeTests/ProjetTestMultiThreadCasLimiteFichier/TestInclude/main.p"
    )
    tableau_tests_prysma.append(test_prysma_2.executer_projet())

    # Test 3: ProjetTestMultiThreadCasLimiteFichier - TestProfondeur
    print("\nProjetTestMultiThreadCasLimiteFichier/TestProfondeur/main.p")
    test_prysma_3 = Orchestration.test_projet_prysma.TestProjetPrysma(
        build_dirname="build", 
        compiler_name="Prysma", 
        executable_name="main", 
        file="Tests/PrysmaCodeTests/ProjetTestMultiThreadCasLimiteFichier/TestProfondeur/main.p"
    )
    tableau_tests_prysma.append(test_prysma_3.executer_projet())

    all_ok = ok_cpp and all(tableau_tests_prysma)
    
    if not all_ok:
        print("\nArrêt du pipeline : Échec d'une étape.")
        sys.exit(1)

    print("\nTests terminés")
    sys.exit(0)

if __name__ == "__main__":
    main()