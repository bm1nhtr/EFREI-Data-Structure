# Structures de Données en C

Ce projet contient des implémentations complètes des structures de données fondamentales en langage C, avec des commentaires en français pour faciliter l'apprentissage.

## 🚀 Démarrage Rapide

### Compilation et Exécution

**⚠️ Problème Courant:** Si vous obtenez des erreurs `undefined reference`, c'est parce que vous compilez seulement `main.c` sans lier les autres fichiers `.c`.

**✅ Solution:** Compiler TOUS les fichiers `.c` ensemble.

**Windows (PowerShell):**
```bash
cd Implementation
gcc -o main.exe main.c Lists/Slist/Slist.c Lists/Slist_tail/Slist_tail.c Lists/Dlist/Dlist.c Stack/Stack.c Queue/Queue.c Trees/Btree/Btree.c Trees/AVL/AVL.c -std=c11 -Wall
.\main.exe
```

**Linux/Mac:**
```bash
cd Implementation
gcc -o main main.c Lists/Slist/Slist.c Lists/Slist_tail/Slist_tail.c Lists/Dlist/Dlist.c Stack/Stack.c Queue/Queue.c Trees/Btree/Btree.c Trees/AVL/AVL.c -std=c11 -Wall
./main
```

**Avec CMake (CLion):**
```bash
cd Implementation
mkdir build && cd build
cmake ..
make                    # Linux/Mac
# ou dans CLion: Build Project (Ctrl+F9)
./LinkedList            # Linux/Mac
# ou cmake-build-debug/LinkedList.exe (Windows)
```

**Note:** Dans PowerShell, utilisez `.\main.exe` (avec `.\`) pour exécuter un fichier dans le répertoire courant.

## 📚 Structures de Données Implémentées

### 1. Liste Simplement Chainée (Singly Linked List)
**Fichiers:** `Lists/Slist/Slist.h`, `Lists/Slist/Slist.c`

- **Structure:** Chaque nœud pointe uniquement vers le nœud suivant
- **Complexité:**
  - Insertion en tête: O(1)
  - Insertion en queue: O(n)
  - Suppression en tête: O(1)
  - Suppression en queue: O(n)
  - Recherche: O(n)

**Fonctions principales:**
- `ds_slist_init()` - Initialiser une liste vide
- `ds_slist_insert_head()` - Insérer en tête
- `ds_slist_insert_tail()` - Insérer en queue
- `ds_slist_remove_head()` - Supprimer la tête
- `ds_slist_remove_tail()` - Supprimer la queue
- `ds_slist_find()` - Rechercher une valeur
- `ds_slist_clear()` - Vider la liste

### 2. Liste Simplement Chainée avec Head et Tail
**Fichiers:** `Lists/Slist_tail/Slist_tail.h`, `Lists/Slist_tail/Slist_tail.c`

- **Structure:** Liste avec pointeurs vers la tête ET la queue
- **Avantage:** Insertion en queue en O(1) au lieu de O(n)
- **Complexité:**
  - Insertion en tête: O(1)
  - Insertion en queue: O(1) ⚡
  - Suppression en tête: O(1)
  - Suppression en queue: O(n) (toujours besoin de trouver l'avant-dernier)

**Fonctions principales:**
- `ds_slist_tail_init()` - Initialiser
- `ds_slist_tail_insert_head()` - Insérer en tête
- `ds_slist_tail_insert_tail()` - Insérer en queue (O(1))
- `ds_slist_tail_remove_head()` - Supprimer la tête
- `ds_slist_tail_remove_tail()` - Supprimer la queue

### 3. Liste Doublement Chainée (Doubly Linked List)
**Fichiers:** `Lists/Dlist/Dlist.h`, `Lists/Dlist/Dlist.c`

- **Structure:** Chaque nœud pointe vers le nœud suivant ET le nœud précédent
- **Avantage:** Parcours dans les deux sens, suppression en O(1) si on a le nœud
- **Complexité:**
  - Insertion en tête/queue: O(1)
  - Suppression en tête/queue: O(1)
  - Suppression d'un nœud donné: O(1) ⚡
  - Parcours bidirectionnel: O(n)

**Fonctions principales:**
- `ds_dlist_init()` - Initialiser
- `ds_dlist_insert_head()` - Insérer en tête
- `ds_dlist_insert_tail()` - Insérer en queue
- `ds_dlist_insert_after()` - Insérer après un nœud
- `ds_dlist_insert_before()` - Insérer avant un nœud
- `ds_dlist_remove_node()` - Supprimer un nœud (O(1))
- `ds_dlist_print_forward()` - Afficher de gauche à droite
- `ds_dlist_print_backward()` - Afficher de droite à gauche

### 4. Pile (Stack)
**Fichiers:** `Stack/Stack.h`, `Stack/Stack.c`

- **Structure:** LIFO (Last In First Out) - Dernier entré, premier sorti
- **Implémentation:** Liste simplement chainée avec pointeur vers le sommet
- **Complexité:**
  - Push (empiler): O(1)
  - Pop (dépiler): O(1)
  - Peek (consulter): O(1)
  - Taille: O(1) grâce au compteur

**Fonctions principales:**
- `ds_stack_init()` - Initialiser une pile vide
- `ds_stack_push()` - Empiler un élément
- `ds_stack_pop()` - Dépiler un élément
- `ds_stack_peek()` - Consulter le sommet sans retirer
- `ds_stack_size()` - Obtenir la taille
- `ds_stack_clear()` - Vider la pile

**Utilisations typiques:**
- Évaluation d'expressions
- Parcours d'arbre (DFS)
- Gestion de la pile d'appels
- Annulation/refaire (undo/redo)

### 5. File (Queue)
**Fichiers:** `Queue/Queue.h`, `Queue/Queue.c`

- **Structure:** FIFO (First In First Out) - Premier entré, premier sorti
- **Implémentation:** Liste simplement chainée avec head et tail
- **Complexité:**
  - Enqueue (enfiler): O(1)
  - Dequeue (défiler): O(1)
  - Taille: O(1)

**Fonctions principales:**
- `queue_init()` - Initialiser une file vide
- `queue_enqueue()` - Enfiler un élément
- `queue_dequeue()` - Défiler un élément
- `queue_clear()` - Vider la file

**Utilisations typiques:**
- Parcours en largeur (BFS) des arbres
- Gestion de files d'attente
- Planification de tâches

### 6. Arbre Binaire (Binary Tree)
**Fichiers:** `Trees/Btree/Btree.h`, `Trees/Btree/Btree.c`

- **Structure:** Chaque nœud a au plus 2 enfants (gauche et droit)
- **Complexité:**
  - Insertion: O(1) pour attacher un nœud
  - Parcours: O(n) où n est le nombre de nœuds
  - Hauteur: O(n)
  - Taille: O(n)

**Parcours disponibles:**
- **Préfixe (Preorder):** Racine → Gauche → Droit
- **Infixe (Inorder):** Gauche → Racine → Droit
- **Postfixe (Postorder):** Gauche → Droit → Racine
- **Par niveau (Level-order/BFS):** Niveau par niveau

**Fonctions principales:**
- `ds_btree_init()` - Initialiser un arbre vide
- `ds_btree_create_node()` - Créer un nœud
- `ds_btree_attach_left()` - Attacher un fils gauche
- `ds_btree_attach_right()` - Attacher un fils droit
- `ds_btree_preorder()` - Parcours préfixe
- `ds_btree_inorder()` - Parcours infixe
- `ds_btree_postorder()` - Parcours postfixe
- `ds_btree_level_order()` - Parcours par niveau
- `ds_btree_height()` - Calculer la hauteur
- `ds_btree_size()` - Calculer la taille

### 7. Arbre Binaire de Recherche (BST - Binary Search Tree)
**Fichiers:** `Trees/Btree/Btree.h`, `Trees/Btree/Btree.c` (fonctions `ds_bsttree_*`)

- **Structure:** Arbre binaire avec propriété de recherche
  - Tous les nœuds du sous-arbre gauche < racine
  - Tous les nœuds du sous-arbre droit > racine
- **Complexité:**
  - Recherche: O(h) où h est la hauteur
  - Insertion: O(h)
  - Suppression: O(h)
  - Dans le meilleur cas (arbre équilibré): O(log n)
  - Dans le pire cas (arbre dégénéré): O(n)

**Fonctions principales:**
- `ds_bsttree_add()` - Ajouter une valeur
- `ds_bsttree_find()` - Rechercher une valeur
- `ds_bsttree_remove()` - Supprimer une valeur
- `ds_bsttree_find_in_node()` - Rechercher dans un sous-arbre

**Avantages:**
- Recherche rapide si équilibré
- Parcours infixe donne les valeurs triées

**Inconvénients:**
- Peut devenir déséquilibré (dégénérer en liste chainée)
- Performance dégradée dans le pire cas

### 8. Arbre AVL (Adelson-Velsky et Landis)
**Fichiers:** `Trees/AVL/AVL.h`, `Trees/AVL/AVL.c`

- **Structure:** BST auto-équilibré
- **Propriété:** La différence de hauteur entre les sous-arbres gauche et droit est au plus 1
- **Complexité:**
  - Recherche: O(log n) ⚡
  - Insertion: O(log n) ⚡
  - Suppression: O(log n) ⚡
  - Toujours équilibré grâce aux rotations

**Rotations:**
- **Rotation simple à droite (LL):** Quand le sous-arbre gauche est trop haut
- **Rotation simple à gauche (RR):** Quand le sous-arbre droit est trop haut
- **Rotation double gauche-droite (LR):** Rotation gauche puis droite
- **Rotation double droite-gauche (RL):** Rotation droite puis gauche

**Fonctions principales:**
- `ds_avl_init()` - Initialiser un arbre AVL vide
- `ds_avl_insert()` - Insérer une valeur (avec auto-équilibrage)
- `ds_avl_remove()` - Supprimer une valeur (avec auto-équilibrage)
- `ds_avl_find()` - Rechercher une valeur
- `ds_avl_get_balance()` - Obtenir le facteur d'équilibre
- `ds_avl_rotate_left()` - Rotation à gauche
- `ds_avl_rotate_right()` - Rotation à droite

**Avantages:**
- Toujours équilibré
- Garantit O(log n) pour toutes les opérations
- Meilleur que BST pour des données dynamiques


## 📖 Exemples d'Utilisation

### Liste Simplement Chainée

```c
#include "Lists/Slist/Slist.h"

SList list;
ds_slist_init(&list);

ds_slist_insert_head(&list, 10);
ds_slist_insert_head(&list, 20);
ds_slist_insert_tail(&list, 30);

ds_slist_print(&list); // [20 --> 10 --> 30]

int value;
ds_slist_remove_head(&list, &value);
printf("Valeur supprimée: %d\n", value); // 20
```

### Pile (Stack)

```c
#include "Stack/Stack.h"

Stack stack;
ds_stack_init(&stack);

ds_stack_push(&stack, 10);
ds_stack_push(&stack, 20);
ds_stack_push(&stack, 30);

int top;
ds_stack_peek(&stack, &top);
printf("Sommet: %d\n", top); // 30

ds_stack_pop(&stack, &top);
printf("Dépilé: %d\n", top); // 30
```

### Arbre Binaire de Recherche

```c
#include "Trees/Btree/Btree.h"

BTree bst;
ds_btree_init(&bst);

ds_bsttree_add(&bst, 50);
ds_bsttree_add(&bst, 30);
ds_bsttree_add(&bst, 70);
ds_bsttree_add(&bst, 20);
ds_bsttree_add(&bst, 40);

TNode* found = ds_bsttree_find(&bst, 30);
if (found) {
    printf("Trouvé: %d\n", found->data);
}

ds_bsttree_remove(&bst, 30);
```

### Arbre AVL

```c
#include "Trees/AVL/AVL.h"

AVLTree avl;
ds_avl_init(&avl);

ds_avl_insert(&avl, 10);
ds_avl_insert(&avl, 20);
ds_avl_insert(&avl, 30); // Auto-équilibrage automatique

ds_avl_print_inorder(avl.root); // 10 20 30 (toujours trié)

AVLNode* found = ds_avl_find(&avl, 20);
if (found) {
    printf("Trouvé: %d\n", found->data);
}
```

## 📊 Comparaison des Complexités

| Structure | Insertion | Recherche | Suppression | Notes |
|-----------|-----------|-----------|-------------|-------|
| Liste chainée (head) | O(1) tête, O(n) queue | O(n) | O(1) tête, O(n) queue | Simple mais lent pour queue |
| Liste chainée (head+tail) | O(1) | O(n) | O(1) tête, O(n) queue | Meilleur pour insertions |
| Liste doublement chainée | O(1) | O(n) | O(1) si nœud connu | Parcours bidirectionnel |
| Pile | O(1) | - | O(1) | LIFO |
| File | O(1) | - | O(1) | FIFO |
| Arbre binaire | O(1) attach | O(n) | O(1) attach | Structure de base |
| BST | O(h) | O(h) | O(h) | h = hauteur (log n à n) |
| AVL | O(log n) | O(log n) | O(log n) | Toujours équilibré |

## 🎯 Conseils pour l'Examen

1. **Comprendre les complexités:** Savoir pourquoi chaque opération a sa complexité
2. **Visualiser:** Dessiner les structures avant de coder
3. **Cas limites:** Penser aux cas vides, un seul élément, etc.
4. **Mémoire:** Ne pas oublier de libérer la mémoire avec `free()`
5. **Pointeurs:** Bien comprendre les pointeurs et les pointeurs de pointeurs
6. **Récursivité:** Maîtriser les fonctions récursives pour les arbres

## 📝 Notes Importantes

- Tous les commentaires sont en français
- Les fonctions retournent généralement 1 pour succès, 0 pour échec
- Les fonctions de recherche retournent NULL si non trouvé
- Toujours vérifier les allocations mémoire (retour de `malloc()`)
- Utiliser `const` pour les paramètres qui ne sont pas modifiés

## 🔧 Structure du Projet

```
Implementation/
├── Lists/                    # Toutes les structures de listes
│   ├── Slist/               # Liste simplement chainée (head uniquement)
│   │   ├── Slist.h
│   │   └── Slist.c
│   ├── Slist_tail/          # Liste simplement chainée (head + tail)
│   │   ├── Slist_tail.h
│   │   └── Slist_tail.c
│   └── Dlist/               # Liste doublement chainée
│       ├── Dlist.h
│       └── Dlist.c
├── Stack/                    # Pile (Stack)
│   ├── Stack.h
│   └── Stack.c
├── Queue/                    # File (Queue)
│   ├── Queue.h
│   └── Queue.c
├── Trees/                    # Toutes les structures d'arbres
│   ├── Btree/               # Arbre binaire et BST
│   │   ├── Btree.h
│   │   └── Btree.c
│   └── AVL/                 # Arbre AVL
│       ├── AVL.h
│       └── AVL.c
├── main.c                    # Fichier de test principal
└── CMakeLists.txt            # Configuration CMake
```

**Organisation:** Les structures de données sont organisées par catégorie dans des dossiers séparés pour une meilleure lisibilité et organisation du code.

## 📚 Ressources

- [Introduction aux structures de données](https://fr.wikipedia.org/wiki/Structure_de_donn%C3%A9es)
- [Complexité algorithmique](https://fr.wikipedia.org/wiki/Complexit%C3%A9_algorithmique)
- [Data Structures Easy to Advanced Course - Full Tutorial from a Google Engineer](https://www.youtube.com/watch?v=RBSGKlAvoiM&t=25400s)

---


