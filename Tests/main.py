# Execution séquentielle des tests du compilateur
# C'est l'orchestrateur qui lance tous les tests du compilateur
# Orchestrateur de tests pour le compilateur prysma, automatisation des tests unitaire 
import subprocess
import Orchestration.test_projet_prysma
import Orchestration.test_cpp_unittest
import Orchestration.build_manager


def main():

    # Initialiser le gestionnaire de construction (verbose=False pour masquer les sorties)
    builder = Orchestration.build_manager.BuildManager(verbose=False)
    
    builder.build_compilateur()
    builder.build_tests()

    # Lancer les tests unitaires C++
    test_cpp = Orchestration.test_cpp_unittest.TestCppUnittest()
    test_cpp.executer_tests()

    # Lancer les tests du compilateur 
    # Test 1: ProjetTestCasLimite
    print("ProjetTestCasLimite/main.p")
    test_prysma_1 = Orchestration.test_projet_prysma.TestProjetPrysma(
        build_dirname="build", 
        compiler_name="Prysma", 
        executable_name="main", 
        file="Tests/PrysmaCodeTests/ProjetTestCasLimite/main.p"
    )

    test_prysma_1.executer_projet()

    # Test 2: ProjetTestMultiThreadCasLimiteFichier - TestInclude
    print("\nProjetTestMultiThreadCasLimiteFichier/TestInclude/main.p")
    test_prysma_2 = Orchestration.test_projet_prysma.TestProjetPrysma(
        build_dirname="build", 
        compiler_name="Prysma", 
        executable_name="main", 
        file="Tests/PrysmaCodeTests/ProjetTestMultiThreadCasLimiteFichier/TestInclude/main.p"
    )
    test_prysma_2.executer_projet()

    # Test 3: ProjetTestMultiThreadCasLimiteFichier - TestProfondeur
    print("\nProjetTestMultiThreadCasLimiteFichier/TestProfondeur/main.p")
    test_prysma_3 = Orchestration.test_projet_prysma.TestProjetPrysma(
        build_dirname="build", 
        compiler_name="Prysma", 
        executable_name="main", 
        file="Tests/PrysmaCodeTests/ProjetTestMultiThreadCasLimiteFichier/TestProfondeur/main.p"
    )
    test_prysma_3.executer_projet()

    print("\nTests terminés")


if __name__ == "__main__":
    main()