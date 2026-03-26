import sys
import os

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from tests.orchestration import build_manager
from generation.generator_ast import GenerateurAST
from generation.generator_interface_visitor import GenerateurInterfaceVisitor
from generation.generator_visitor_base_general import GenerateurVisitorBaseGenerale
from generation.generator_graphe_viz import GenerateurGraphViz
import orchestration.test_project_prysma
import orchestration.test_cpp_unittest

def main():

    array_tests_prysma = []
    racine = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    GenerateurAST(racine).generatedr()
    GenerateurInterfaceVisitor(racine).generatedr()
    GenerateurVisitorBaseGenerale(racine).generatedr()
    GenerateurGraphViz(racine).generatedr()

    build_manager.BuildManager.executer_commande(["python3", "../debug.py"])

    # Compilation des tests 
    build_manager.BuildManager.executer_commande(["cmake", "-S", ".", "-B", "build"])
    build_manager.BuildManager.executer_commande(["cmake", "--build", "build", "-j", str(os.cpu_count() or 1)])

    test_cpp = orchestration.test_cpp_unittest.TestCppUnittest()
    ok_cpp = test_cpp.executer_tests()

    # Test 1: project_test_edge_case
    print("project_test_edge_case/main.p")
    test_prysma_1 = orchestration.test_project_prysma.TestProjectPrysma(
        build_dirname="build", 
        compiler_name="Prysma", 
        executable_name="main", 
        file="tests/prysma_code_tests/project_test_edge_case/main.p"
    )
    array_tests_prysma.append(test_prysma_1.executer_project())

    # Test 2: ProjectTestMultiThreadEdgeCaseFile - TestInclude
    print("\nproject_test_multi_thread_edge_case_file/test_include/main.p")
    test_prysma_2 = orchestration.test_project_prysma.TestProjectPrysma(
        build_dirname="build", 
        compiler_name="Prysma", 
        executable_name="main", 
        file="tests/prysma_code_tests/project_test_multi_thread_edge_case_file/test_include/main.p"
    )
    array_tests_prysma.append(test_prysma_2.executer_project())

    # Test 3: ProjectTestMultiThreadEdgeCaseFile - TestDepth
    print("\nproject_test_multi_thread_edge_case_file/test_depth/main.p")
    test_prysma_3 = orchestration.test_project_prysma.TestProjectPrysma(
        build_dirname="build", 
        compiler_name="Prysma", 
        executable_name="main", 
        file="tests/prysma_code_tests/project_test_multi_thread_edge_case_file/test_depth/main.p"
    )
    array_tests_prysma.append(test_prysma_3.executer_project())

    all_ok = ok_cpp and all(array_tests_prysma)
    
    if not all_ok:
        print("\nArrêt du pipeline : Échec d'une étape.")
        sys.exit(1)

    print("\nTests terminés")
    sys.exit(0)

if __name__ == "__main__":
    main()