sudo apt install llvm-dev llvm

cmake -S . -B build

sudo apt-get update && sudo apt-get install -y bear


# Option 1 : Commande directe (une seule fois)
bear --output build/compile_commands.json -- make

# Option 2 : Via le Makefile (recommandé)
make compile_commands