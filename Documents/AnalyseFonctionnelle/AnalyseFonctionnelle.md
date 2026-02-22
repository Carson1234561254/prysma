# Prysma: Rapport d’analyse fonctionnelle et organique

**Auteur :** Raphael Arseneault  
**Cours :** Épreuve Synthèse de programme (420-626-RK)

**Présenté à :**
- Monsieur Charles Lemaire
- Monsieur Jonathan Roy
- Monsieur Marcel Landry

**Département de techniques de l’informatique**  
*Cégep Rimouski*  
*25 mars 2026*



Analyse Fonctionnelle
## Diagramme de séquence fonctionnel 

![Diagramme de séquence fonctionnel](../../Images/DiagrammeSequanceFonctionnel.png) 

## Flux d'Exécution Frontend : Génération de l'AST

Ce diagramme de séquence détaille l'architecture de la phase frontend du compilateur Prysma. L'objectif est d'isoler les responsabilités pour garantir une structure de données stable avant la génération de code intermédiaire LLVM IR.
Composants et Interactions

    Main : Contrôleur central. Il orchestre le flux séquentiel sans exécuter de logique d'analyse.

    LecteurFichierTexte : Extrait le code brut du fichier source et retourne une std::string.

    Lexer : Analyse le texte et génère un vecteur de tokens (analyse lexicale).

    Curseur : Constructeur de l'arbre. Reçoit les tokens et initie l'analyse syntaxique.

    Noeud : Représente la logique de l'Arbre Syntaxique Abstrait (AST). La construction s'effectue par récursivité, chaque nœud instanciant et évaluant ses enfants selon la grammaire de Prysma.

Contrainte architecturale

L'AST généré est renvoyé au Main uniquement s'il est complet. Cette isolation stricte des couches applique le principe de Fail-Fast. En cas d'erreur de syntaxe détectée par le Lexer ou le Curseur, la compilation s'arrête immédiatement, empêchant toute corruption de la mémoire et garantissant que l'API C++ de LLVM ne reçoive qu'un arbre syntaxique 100% valide.


## Schéma général du projet

![Schéma général du projet](../../Images/diagram_general.jpeg)


## Description détaillée de l’algorithme
On commence par traiter un fichier texte contenant le code source Prysma. Il est chargé en mémoire et envoyé au lexer. Le lexer se charge de transformer le fichier texte en vecteur de tokens, chaque token contient un identifiant et une string value. Il sépare mot à mot chaque token en lui attribuant son propre identifiant. Tout superflu n’est pas traité par le lexer : espaces, caractères invalides non disponibles dans le langage s’il y a lieu. Ensuite, le vecteur de tokens est envoyé vers le parseur, la classe curseur sera en charge de parcourir le vecteur de tokens avec l’algorithme de descente récursive pour construire l’arbre approprié avec les nœuds conformes pour celui-ci. Un arbre syntaxique complet en sortira. Ensuite, dans le main, l’utilisation du parcours en profondeur sera utilisée pour parcourir récursivement l’arbre syntaxique abstrait, chaque nœud pourra alors construire le code intermédiaire en utilisant le framework LLVM. Le backend LLVM se chargera de traduire le code intermédiaire en code assembleur, puis en code machine exécutable.

## Cas de tests fonctionnels

Les cas de tests, situés dans le répertoire `/Tests/PrysmaCodeTests/`, ont pour objectif de valider individuellement les fonctionnalités critiques du compilateur Prysma. Chaque fichier `.p` représente un scénario de test autonome qui vérifie un aspect spécifique du langage, de la déclaration des variables à des opérations complexes comme la récursivité et la manipulation de tableaux. L'approche est de garantir que chaque composant du compilateur fonctionne comme attendu avant de les intégrer.

### TestFonctionnelVariableInt.p
Ce cas de test se concentre sur la validation des opérations arithmétiques et de la logique de base pour les variables de type entier (`int32`). L'objectif est de confirmer que le compilateur gère correctement la priorité des opérateurs (multiplication avant addition), les affectations de variables, l'auto-incrémentation (`a = a + 1`), et la copie de valeurs entre variables. Il vérifie également que les arguments de fonction sont correctement passés et que les expressions complexes avec parenthèses sont évaluées dans le bon ordre.

### TestFonctionnelVariableFloat.p
Similaire au test sur les entiers, ce fichier valide les mêmes fonctionnalités mais pour les variables à virgule flottante (`float`). Il s'assure que la précision des calculs est maintenue et que les opérations de base (priorité, affectation, passage d'arguments) sont conformes aux attentes pour les nombres décimaux.

### TestFonctionnelVariableBool.p
Ce test est dédié à la manipulation des variables booléennes (`bool`). Il a pour but de vérifier la correction des opérateurs logiques `&&` (ET), `||` (OU), et `!` (NON). Les tests couvrent des scénarios où les opérateurs sont utilisés avec des valeurs littérales (`true`, `false`) ainsi qu'avec des variables, garantissant que la logique booléenne du langage est solide.

### TestCondition.p
L'objectif de ce cas de test est de valider le comportement des structures conditionnelles `if-else`. Il teste une variété de conditions, incluant des comparaisons sur les entiers et les flottants (`>`, `<`, `==`), des opérateurs logiques (`&&`, `||`), et des conditions imbriquées. Un test critique vérifie que les parenthèses dans les conditions complexes sont correctement interprétées par le parseur.

### TestBoucle.p
Ce fichier a pour but de tester la fonctionnalité des boucles `while`. Il couvre des scénarios de base, comme une boucle simple avec un compteur, des boucles imbriquées, et des conditions de sortie plus complexes utilisant des opérateurs logiques. Un cas spécifique s'assure qu'une boucle dont la condition est initialement fausse ne s'exécute jamais.

### TestRecursivité.p
Ce cas de test a pour objectif de valider la capacité du compilateur à gérer des appels de fonction récursifs. Il implémente deux algorithmes classiques, la factorielle et la suite de Fibonacci, pour s'assurer que la pile d'appels est correctement gérée et que les fonctions peuvent s'appeler elles-mêmes sans provoquer de corruption de la mémoire ou de boucle infinie.

### TestTableauInt.p, TestTableauFloat.p, TestTableauBool.p
Ces trois fichiers de test sont dédiés à la validation de la gestion des tableaux pour chaque type de données de base. Leur objectif est de confirmer que la déclaration, l'affectation, et la lecture des éléments de tableau fonctionnent correctement. Les tests incluent l'utilisation d'index statiques et dynamiques (variables ou expressions), la vérification de l'intégrité de la pile mémoire lors des accès au tableau, et la capacité de passer des tableaux en argument de fonction et de les retourner. Un cas de test important vérifie également que l'accès à un index en dehors des limites du tableau est correctement géré, bien que ce test soit actuellement commenté car il devrait provoquer une erreur de compilation.



