import subprocess
import os

class TestProjetPrysma:
    
    def __init__(self, build_dirname, compiler_name, executable_name, file):
        # Chemins relatifs à l'emplacement du script
        self.script_dir = os.path.dirname(os.path.abspath(__file__))
        self.project_root = os.path.abspath(os.path.join(self.script_dir, "../../"))
        self.build_dir = os.path.join(self.project_root, build_dirname)
        self.compiler_path = os.path.join(self.build_dir, compiler_name)
        self.executable_path = os.path.join(self.build_dir, executable_name)
        self.file  = file 

    # Récupérer que les resultats false pour afficher uniquement les échecs des tests
    def __parse_result_false(self, result):
        lines = result.stdout.splitlines()
        if not lines:
            return False
        return lines[-1] == "false"
        
    def executer_projet(self):
            
        print("--- Lancement des tests (seuls les échecs sont affichés) ---")

        # commande pour executer le compilateur sur le fichier de test 

        file_path = os.path.join(self.project_root, self.file)
        command = [self.compiler_path, file_path]
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        
        self.__afficher_resultats(result, command)

    def __afficher_resultats(self, result, command):
        """Affiche les résultats avec couleurs"""
        
        # Code couleur ANSI
        VERT = "\033[92m"
        ROUGE = "\033[91m"
        RESET = "\033[0m"
        BOLD = "\033[1m"

        if result.returncode != 0:
            print(f"{ROUGE}{BOLD}Erreur lors de l'exécution{RESET}")
            print(f"{ROUGE}Commande: {' '.join(command)}{RESET}")
            print(f"{ROUGE}Code de retour: {result.returncode}{RESET}")
            if result.stderr:
                print(f"{ROUGE}Erreur: {result.stderr}{RESET}")
        else:
            if self.__parse_result_false(result):
                print(f"{ROUGE}{BOLD}Test échoué{RESET}")
                print(f"{ROUGE}Sortie: {result.stdout}{RESET}")
            else:
                print(f"{VERT}{BOLD}Test réussi{RESET}")
