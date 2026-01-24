# Makefile simple pour LLVMMethodeDoc

.PHONY: all build clean rebuild run help

# Répertoire de build
BUILD_DIR := build

# Cible par défaut
all: build

# Créer le répertoire build et compiler
build:
	@echo "Configuration et compilation du projet..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && make

# Nettoyer les fichiers de build
clean:
	@echo "Nettoyage des fichiers de build..."
	@rm -rf $(BUILD_DIR)

# Nettoyer et reconstruire
rebuild: clean build

# Exécuter le programme compilé
run: build
	@echo "Exécution du programme..."
	@./$(BUILD_DIR)/LLVMMethodeDoc

# Afficher l'aide
help:
	@echo "Commandes disponibles:"
	@echo "  make           - Configure et compile le projet"
	@echo "  make build     - Configure et compile le projet"
	@echo "  make clean     - Supprime tous les fichiers de build"
	@echo "  make rebuild   - Nettoie et recompile"
	@echo "  make run       - Compile et exécute le programme"
	@echo "  make help      - Affiche cette aide"
