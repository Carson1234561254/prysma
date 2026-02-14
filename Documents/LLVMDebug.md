# Faire un graphe
## faire un fichier dot 
opt -passes=dot-cfg -disable-output output.ll

## Traduire en photo 
dot -Tpng output.dot -o ast_graph.png

 clang -g -O0 -fsanitize=address output.ll -o debug_bin



