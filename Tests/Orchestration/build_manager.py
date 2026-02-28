import subprocess


class BuildManager:
    """Gestionnaire de construction du compilateur et des tests"""
    
    def __init__(self, verbose=False):
        """
        Initialise le gestionnaire de construction
        
        Args:
            verbose (bool): Si True, affiche la sortie complète des commandes
        """
        self.verbose = verbose
        # Code couleur ANSI
        self.VERT = "\033[92m"
        self.ROUGE = "\033[91m"
        self.RESET = "\033[0m"
        self.BOLD = "\033[1m"

    def executer_commande(self, command, description=""):
        """
        Exécute une commande shell
        
        Args:
            command (list): La commande à exécuter
            description (str): Description de la commande (optionnel)
        """
        try:
            result = subprocess.run(
                command,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
            )
            
            if result.returncode != 0:
                print(f"{self.ROUGE}{self.BOLD}Erreur: {description or ' '.join(command)}{self.RESET}")
                print(f"{self.ROUGE}Code de retour: {result.returncode}{self.RESET}")
                if result.stderr:
                    print(f"{self.ROUGE}Erreur: {result.stderr}{self.RESET}")
                return False
            else:
                if self.verbose:
                    print(f"{self.VERT}Succès: {description or ' '.join(command)}{self.RESET}")
                    if result.stdout:
                        print(f"Sortie: {result.stdout}")
                else:
                    print(f"{self.VERT}{description or 'Commande exécutée'}{self.RESET}")
                return True
                
        except Exception as e:
            print(f"{self.ROUGE}{self.BOLD}Exception: {str(e)}{self.RESET}")
            return False

    def build_compilateur(self):
        """Construit le compilateur principal"""
        
        # Configuration CMake
        success = self.executer_commande(
            ["cmake", "-S", "..", "-B", "../build", "-DCMAKE_BUILD_TYPE=Debug"],
            "Configuration CMake"
        )
        
        if not success:
            return False
        
        # Compilation avec bear
        commande = """cd .. && mkdir -p build && bear --output build/compile_commands.json -- make -j$(nproc) CXXFLAGS="-Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wnull-dereference -Wformat=2 -Werror" """
        success = self.executer_commande(
            ["bash", "-c", commande],
            "Compilation du compilateur"
        )
        
        return success

    def build_tests(self):
        """Construit les tests unitaires"""
        
        # Configuration CMake
        success = self.executer_commande(
            ["cmake", "-S", ".", "-B", "build", "-DCMAKE_BUILD_TYPE=Debug"],
            "Configuration CMake des tests"
        )
        
        if not success:
            return False
        
        # Compilation avec bear
        success = self.executer_commande(
            ["bash", "-c", "bear --output build/compile_commands.json -- cmake --build build -j$(nproc)"],
            "Compilation des tests"
        )
        
        return success
