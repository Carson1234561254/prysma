# Analyse Technique : Projet Prysma

Ce document fournit une analyse détaillée du développement du langage Prysma, couvrant les aspects théoriques, les besoins fonctionnels, les défis de bas niveau et l'architecture du compilateur.

## 1. Objectifs du projet

L'objectif principal est de développer un langage nommé "Prysma" répliquant les fonctionnalités modernes. Le compilateur est écrit en C++. Pour la génération de code, trois approches ont été analysées :

- **LLVM IR (Retenu) :** Représentation intermédiaire en SSA (Single Static Assignment). Facilite les optimisations et la génération machine multi-cibles.
- **Backend x86-64 Manuel :** Offre un contrôle total mais impose une gestion complexe des registres et de l'ABI.
- **Transpilation vers C :** Simple à implémenter mais limite le contrôle fin sur les optimisations spécifiques.

Remarque : LLVM IR est une représentation intermédiaire (IR) en SSA, indépendante de la cible, facilitant les optimisations et la génération de code pour différentes architectures. Utiliser LLVM IR permet de ne pas gérer soi-même toutes les complexités de la génération machine.

Exemple de LLVM IR cible :

```llvm
%1 = load i32, i32* %ptr_x        ; charge x depuis %ptr_x
%resultat = add i32 %1, 5         ; additionne 5 à la valeur chargée
```

## 2. Défis de la Génération de Code Machine

### Problématiques du Backend personnalisé (x86-64 Linux)

1. **Gestion des registres :** L'architecture x86-64 offre 16 registres généraux. Il faut gérer efficacement l'utilisation et l'allocation pour éviter les conflits et les sauvegardes inutiles.
2. **Allocation de registres :** Nécessite des algorithmes sophistiqués (coloriage de graphe, Linear Scan) ou une gestion du débordement sur la pile (spilling).
3. **Table des symboles et Adressage :** Implique la gestion manuelle des adresses et des offsets de cadre (stack frame).
4. **Conventions d'appel (ABI) :** Implémentation manuelle du passage des arguments, de l'alignement de la pile et du retour de valeur (System V AMD64).
5. **Encapsulation et visibilité :** Nécessite des conventions (préfixes, sections) pour contrôler la visibilité des symboles à la liaison.
6. **Complexité :** Écrire et maintenir un backend assembleur est plus long et sujet aux erreurs qu'utiliser un backend établi.

### Avantages de l'infrastructure LLVM

- **Abstraction et Portabilité :** Le compilateur peut cibler plusieurs architectures sans modifications majeures.
- **Optimisations :** LLVM intègre de nombreuses optimisations avancées appliquées automatiquement au code intermédiaire.
- **Écosystème :** Riche en outils (analyse statique, génération de symboles de débogage DWARF).
- **Gestion des registres :** LLVM utilise des registres virtuels en forme SSA, simplifiant l'allocation.

## 3. Conception du Langage Prysma

### Conception Orientée Objet
Le support complet des classes est implémenté nativement :
- **Classes et objets :** Définition de la syntaxe et de la sémantique pour la création de classes et l'héritage.
- **Méthodes et attributs :** Déclaration, appel de méthodes et accès aux attributs.
- **Encapsulation :** Gestion stricte de la visibilité des membres (public, private, protected).
- **Polymorphisme et VTable :** Support de la redéfinition de méthodes via une gestion dynamique utilisant la classe `VTableNavigator`. La construction de la table des méthodes virtuelles (vtable) est exécutée lors de la seconde passe de compilation pour garantir la disponibilité des pointeurs de fonction.

### Analyse Sémantique
- **Table des Symboles :** Utilisation de registres centralisés pour gérer les variables et les fonctions, avec une portée résolue récursivement.
- **Vérification de Type :** Validation statique stricte des opérations et des signatures, supportant un système de casting dynamique.

## 4. Gestion de la Mémoire

### Mémoire du langage Prysma (Exécution)
Le langage utilise une gestion manuelle de la mémoire dynamique, offrant un contrôle déterministe.
- L'allocation et la libération de la mémoire s'effectuent via l'implémentation de bas niveau `prysma_malloc`, exposée au développeur par les mots-clés `new` et `delete`. 

### Mémoire interne du compilateur
L'allocation des nœuds de l'Arbre Syntaxique Abstrait (AST) n'utilise pas de pointeurs intelligents (`std::shared_ptr`). 
- Le compilateur s'appuie sur un **Bump Pointer Allocator** (Arena) fourni par LLVM, en manipulant des pointeurs bruts (`INoeud*`). Cette architecture garantit une mémoire contiguë, élimine les sauts mémoire redondants (double déréférencement) et maximise les performances des caches L1/L2 lors de la compilation.

## 5. Implémentation du Compilateur

### Architecture générale
- **Frontend :** Lexer et Parser.
- **AST (Abstract Syntax Tree) :** Utilisation du design pattern **Composite** pour représenter les nœuds, générés dynamiquement via une usine automatisée (fichiers YAML). Chaque nœud stocke sa position (ligne/colonne) pour le ciblage des erreurs dans les éditeurs (type VS Code).
- **Orchestration et Multithreading :** L'orchestration s'effectue en deux passes distinctes pour garantir le *thread-safety* des registres. La compilation de masse est parallélisée via `llvm::ThreadPool`, évitant la surcharge liée à la création incontrôlée de threads.
- **Runtime :** Le binaire final est lié à une bibliothèque d'exécution écrite en C++.

### Lexer et Syntaxe
Prysma adopte une syntaxe de type C/C++. Le lexer consomme des points-virgules (`;`) pour délimiter les instructions. L'identification des mots-clés est optimisée à la compilation via l'utilisation de tableaux statiques `constexpr`.

### Parser et Construction de l'AST
Le parser utilise une approche récursive descendante. La logique de résolution des expressions imbriquées (comme les conditions contenant des équations mathématiques complexes) repose sur un système de récursion mutuelle entre les constructeurs d'instructions et d'équations, enveloppé par un `ContextParseur`.

### Génération de code (LLVM IR) et Visiteurs
La génération de code est découplée des nœuds de l'AST grâce au patron de conception **Visiteur** :
- Les nœuds n'embarquent aucune logique de génération. Ils n'exposent que des accesseurs (getters) ainsi que la méthode `accept(IVisiteur)`.
- La production de l'IR LLVM est gérée par des classes dédiées (ex. : `VisiteurGeneralGenCode`).
- Le contexte global, incluant les environnements de registres et l'API `llvm::IRBuilder`, est injecté directement dans le visiteur via une structure `ContextGenCode`, simplifiant l'architecture et évitant le passage fastidieux de dépendances à travers l'arbre.

## 3 projets similaires au mien qui m'inspirent 

 - Rust : langage de programmation système qui met l'accent sur la sécurité et la performance. Il utilise LLVM comme backend pour la compilation. C'est un langage très solide et a fait ses preuves dans l'industrie. D'ailleurs, le langage est à une maturation avancée, le compilateur est écrit en Rust lui-même, pour bénéficier de ses propres fonctionnalités de sécurité mémoire, c'est une démonstration de fiabilité, construire un gros projet montre sa robustesse. 
 URL du projet GitHub : https://github.com/rust-lang/rust.git

 - Kaléidoscope : un langage de programmation éducatif, développé par l'équipe LLVM pour enseigner les concepts de base de la compilation en utilisant LLVM comme backend. C'est un bon exemple qui montre les étapes pour construire un compilateur fonctionnel. Toutes les étapes sont expliquées et documentées, ce qui facilite la compréhension. URL du tutoriel : https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/

- GCC : un compilateur open-source très populaire, il permet de compiler le C, C++, Fortran, etc. Il est largement utilisé dans l'industrie, c'est un projet mature et robuste. Intéressant de le voir pour comprendre la construction d'un compilateur évolué. Bien que les parties soient très complexes. URL du projet GitHub : https://github.com/gcc-mirror/gcc.git

## Contrainte d'acceptation

### Deux aspects technologiques majeurs du projet

| Aspect technologique |
| -------------------- |
| Algorithmique        | 
| Outils de compilation|

### Apprentissage technique qui sera réalisé avec la création de ce projet

LLVM : 
    Le projet utilisera le framework LLVM pour la génération de code intermédiaire. L'apprentissage portera sur l'utilisation de l'API C++ de LLVM pour créer des modules, des fonctions, des blocs de base et des instructions. Il sera également nécessaire de comprendre comment manipuler les types de données, les constantes et les variables dans LLVM. De plus, l'optimisation du code généré sera un aspect important à maîtriser pour améliorer les performances du compilateur.
URL : https://llvm.org/

Compilateur : 
    L'apprentissage se portera sur la construction d'un compilateur de A à Z. Cela inclut la compréhension des différentes phases de compilation, telles que l'analyse lexicale, l'analyse syntaxique, la génération de code intermédiaire et l'optimisation. Je dois comprendre comment construire un arbre syntaxique abstrait (AST) pour représenter la structure du code source, et comment traduire cet AST en code LLVM. De plus, il sera important de maîtriser les techniques pour gérer les erreurs de syntaxe et de sémantique dans le code source. 
URL : https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/

#### Façon dont la technologie sera intégrée au projet

Cette technologie s'intègre au projet en tant que composant central, c'est le backend du compilateur. C'est la pièce qui permet la génération du code intermédiaire LLVM IR, un langage de programmation assembleur évolué pour faciliter la programmation d'un langage de programmation. Cette technologie sera utilisée pour générer le code intermédiaire pour la génération de la résolution d'une équation, ex : 20+42-432*(32-432)/3. Toute la syntaxe du langage de programmation, (if, else, for, while, <, = , == , >), utilisera cette technologie pour construire la logique qui sera compilée en assembleur par clang "NomFichier.ll" -o "sortieBinaire". 

### Les risques technologiques pour la réalisation du projet

Points de blocage potentiels :
- Le débogage n'est pas seulement fait dans le langage C++ mais aussi dans le langage généré par le framework LLVM. Ce qui nous donne deux dimensions de débogage où peut se trouver un problème. 
- La complexité de la génération du code par le framework LLVM peut être importante. 
- La récursivité peut être un défi, visualiser l'état d'exécution du code n'est pas aussi simple qu'avec un code non récursif. 
- La gestion de la mémoire peut être un défi, surtout dans le langage C++ et Prysma.
- La création du garbage collector peut être un défi technique intéressant à relever. 
- La création des bibliothèques du langage Prysma.

Défis techniques pour mener à terme la réalisation :
- Comprendre en profondeur le framework LLVM et son API C++.
- Concevoir une architecture de compilateur robuste et évolutive.
- Gérer les erreurs de syntaxe et de sémantique de manière efficace.
- Optimiser le code généré pour de meilleures performances.

## Illustration du projet

C'est la représentation d'un arbre syntaxique abstrait pour le langage Prysma. Pour le code suivant :

```
fn void afficher_nombre_pair(int32 limite) {
    for (int32 i = 0; i < limite; i = i + 1) {
        if (i % 2 == 0) {
            // Est un nombre pair
            print(i)
        }
        else 
        {
            // Est un nombre impair
            print(i)
        }
    }
}
```

![AST arbre syntaxique abstrait](Images/AST.png)


Représentation de la génération du code intermédiaire LLVM IR pour une résolution d'équation simple : 2.0*3.0-(20.0+3.0). Cet algorithme sera utilisé dans les variables ou tout endroit où j'ai besoin de faire un calcul arithmétique. 

![LLVM IR arbre de résolution d'équation](Images/Arbre_resolution_equation.png)

code généré en sortie du compilateur Prysma pour cette équation : 2.0*3.0-(20.0+3.0)

```
 %addtmp = fadd double 2.000000e+01, 3.000000e+00
  %multmp = fmul double 2.000000e+00, 3.000000e+00
  %subtmp = fsub double %multmp, %addtmp
  %formatPtr = getelementptr [14 x i8], ptr @.str, i64 0, i64 0
```
