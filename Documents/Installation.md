## Installation de LLVM 
sudo apt install llvm-dev llvm

## Commande pour faire le fichier build de compilation 
cmake -S . -B build
sudo apt-get update && sudo apt-get install -y bear

## Construire le fichier compile_commands.json permetant une analyse correct du code par clangd
mkdir -p build && bear --output build/compile_commands.json -- make

## Installation de graphviz 
sudo apt install graphviz

## utilisation 

dot -Tpng mon_graphe.dot -o mon_graphe.png