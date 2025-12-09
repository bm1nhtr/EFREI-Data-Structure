//
// Fichier de test pour toutes les structures de données
//

#include <stdio.h>
#include <stdlib.h>
#include "Trees/Btree/Btree.h"
#include "Lists/Slist/Slist.h"
#include "Lists/Slist_tail/Slist_tail.h"
#include "Lists/Dlist/Dlist.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
#include "Trees/AVL/AVL.h"

// ==================== FONCTIONS HELPER ====================

// Fonction helper pour afficher un entier
static void print_int(int v) {
    printf("%d ", v);
}

// Fonction helper pour afficher un entier en hexadécimal
static void print_int_in_hex(int v) {
    printf("%x ", v);
}

// Fonction helper pour afficher la valeur d'un nœud d'arbre
// pnode est un pointeur vers TNode (TNode*)
// On utilise -> pour accéder au champ data du nœud pointé
static void print_node_value(TNode* pnode) {
    if (pnode) printf("%d ", pnode->data); // pnode->data accède à la donnée du nœud
}

// ==================== TEST LISTE SIMPLEMENT CHAINÉE (HEAD) ====================

void test_slist(void) {
    printf("\n========== TEST LISTE SIMPLEMENT CHAINÉE (HEAD) ==========\n\n");
    
    // Déclaration d'une variable de type SList (structure de liste)
    // list est une variable locale, pas un pointeur
    SList list;
    
    // ds_slist_init(&list) : on passe l'ADRESSE de list avec &list
    // &list retourne un pointeur vers list (SList*)
    // La fonction init modifie directement la liste passée par adresse
    ds_slist_init(&list);
    
    // Test insertion
    printf("Insertion en tête: 10, 20, 30\n");
    // On passe &list (adresse) car la fonction modifie la liste
    // Les valeurs 10, 20, 30 sont passées par valeur (int)
    ds_slist_insert_head(&list, 10);
    ds_slist_insert_head(&list, 20);
    ds_slist_insert_head(&list, 30);
    ds_slist_print(&list); // On passe &list pour lire la liste (const SList*)
    
    printf("\nInsertion en queue: 100, 200\n");
    ds_slist_insert_tail(&list, 100);
    ds_slist_insert_tail(&list, 200);
    ds_slist_print(&list);
    
    // Test recherche
    printf("\nRecherche de 20: ");
    // found est un pointeur vers SNode (SNode*)
    // ds_slist_find retourne un pointeur vers le nœud trouvé, ou NULL si non trouvé
    SNode* found = ds_slist_find(&list, 20);
    if (found) { // Si found n'est pas NULL (nœud trouvé)
        // found->data : on utilise -> pour accéder au champ data du nœud pointé
        // found est un pointeur, donc on utilise -> et non .
        printf("Trouvé! Valeur = %d\n", found->data);
    } else {
        printf("Non trouvé\n");
    }
    
    // Test insertion à un index
    printf("\nInsertion de 99 à l'index 2\n");
    ds_slist_insert_at(&list, 2, 99);
    ds_slist_print(&list);
    
    // Test suppression
    // value est une variable locale pour stocker la valeur supprimée
    int value;
    printf("\nSuppression de la tête: ");
    // ds_slist_remove_head(&list, &value) :
    //   - &list : adresse de la liste à modifier
    //   - &value : adresse de la variable où stocker la valeur supprimée
    //   La fonction retourne 1 si succès, 0 si échec
    if (ds_slist_remove_head(&list, &value)) {
        printf("Valeur supprimée = %d\n", value);
    }
    ds_slist_print(&list);
    
    printf("\nSuppression de la valeur 100: ");
    if (ds_slist_remove_value(&list, 100)) {
        printf("Supprimé avec succès\n");
    }
    ds_slist_print(&list);
    
    // Nettoyage : libérer toute la mémoire allouée
    ds_slist_clear(&list);
    printf("\nListe vidée\n");
}

// ==================== TEST LISTE SIMPLEMENT CHAINÉE (HEAD + TAIL) ====================

void test_slist_tail(void) {
    printf("\n========== TEST LISTE SIMPLEMENT CHAINÉE (HEAD + TAIL) ==========\n\n");
    
    // SListTail est une structure qui contient head ET tail
    // Cela permet insertion en queue en O(1) au lieu de O(n)
    SListTail list;
    ds_slist_tail_init(&list); // Initialiser avec &list (adresse)
    
    // Test insertion en queue (O(1) maintenant grâce au pointeur tail!)
    printf("Insertion en queue: 1, 2, 3, 4, 5\n");
    // Chaque insertion est O(1) car on a directement accès au dernier nœud via tail
    ds_slist_tail_insert_tail(&list, 1);
    ds_slist_tail_insert_tail(&list, 2);
    ds_slist_tail_insert_tail(&list, 3);
    ds_slist_tail_insert_tail(&list, 4);
    ds_slist_tail_insert_tail(&list, 5);
    ds_slist_tail_print(&list);
    
    printf("\nInsertion en tête: 0\n");
    ds_slist_tail_insert_head(&list, 0);
    ds_slist_tail_print(&list);
    
    // Test recherche
    printf("\nRecherche de 3: ");
    // found est un pointeur vers SNodeTail
    // La fonction retourne un pointeur vers le nœud ou NULL
    SNodeTail* found = ds_slist_tail_find(&list, 3);
    if (found) { // Vérifier si le pointeur n'est pas NULL
        // found->data : accès au champ data via le pointeur
        printf("Trouvé! Valeur = %d\n", found->data);
    }
    
    // Test suppression
    int value; // Variable pour stocker la valeur supprimée
    printf("\nSuppression de la tête: ");
    // &value : on passe l'adresse pour que la fonction puisse y écrire la valeur
    if (ds_slist_tail_remove_head(&list, &value)) {
        printf("Valeur supprimée = %d\n", value);
    }
    ds_slist_tail_print(&list);
    
    // Nettoyage
    ds_slist_tail_clear(&list);
    printf("\nListe vidée\n");
}

// ==================== TEST LISTE DOUBLEMENT CHAINÉE ====================

void test_dlist(void) {
    printf("\n========== TEST LISTE DOUBLEMENT CHAINÉE ==========\n\n");
    
    // DList : liste doublement chainée, chaque nœud a prev ET next
    DList list;
    ds_dlist_init(&list); // Initialiser avec l'adresse
    
    // Test insertion
    printf("Insertion en tête: 10, 20\n");
    ds_dlist_insert_head(&list, 10);
    ds_dlist_insert_head(&list, 20);
    ds_dlist_print_forward(&list); // Parcours de gauche à droite
    
    printf("\nInsertion en queue: 30, 40\n");
    ds_dlist_insert_tail(&list, 30);
    ds_dlist_insert_tail(&list, 40);
    ds_dlist_print_forward(&list);
    
    // Test parcours inverse (avantage de la liste doublement chainée!)
    printf("\nParcours inverse: ");
    // On peut parcourir de droite à gauche grâce au pointeur prev
    ds_dlist_print_backward(&list);
    
    // Test insertion après un nœud
    // ds_dlist_find retourne un pointeur vers DNode (ou NULL)
    DNode* node = ds_dlist_find(&list, 20);
    if (node) { // Si le nœud existe (pointeur non NULL)
        printf("\nInsertion de 25 après 20\n");
        // On peut insérer directement après un nœud en O(1) car on a les pointeurs prev et next
        ds_dlist_insert_after(&list, node, 25);
        ds_dlist_print_forward(&list);
    }
    
    // Test suppression
    int value;
    printf("\nSuppression de la queue: ");
    // Suppression en O(1) grâce au pointeur tail et prev
    if (ds_dlist_remove_tail(&list, &value)) {
        printf("Valeur supprimée = %d\n", value);
    }
    ds_dlist_print_forward(&list);
    
    // Nettoyage
    ds_dlist_clear(&list);
    printf("\nListe vidée\n");
}

// ==================== TEST PILE (STACK) ====================

void test_stack(void) {
    printf("\n========== TEST PILE (STACK) ==========\n\n");
    
    // Stack : structure LIFO (Last In First Out)
    Stack stack;
    ds_stack_init(&stack); // Initialiser la pile vide
    
    // Test push (empiler)
    printf("Empilement: 10, 20, 30, 40\n");
    // Push ajoute un élément au sommet (top) de la pile
    // Toutes les opérations sont O(1)
    ds_stack_push(&stack, 10);
    ds_stack_push(&stack, 20);
    ds_stack_push(&stack, 30);
    ds_stack_push(&stack, 40);
    ds_stack_print(&stack); // Affiche du sommet vers le bas
    
    printf("Taille de la pile: %d\n", ds_stack_size(&stack));
    
    // Test peek (consulter sans retirer)
    int top; // Variable pour stocker la valeur du sommet
    // peek lit la valeur au sommet sans la retirer
    if (ds_stack_peek(&stack, &top)) { // Retourne 1 si succès
        printf("Sommet de la pile: %d\n", top);
    }
    
    // Test pop (dépiler)
    printf("\nDépilement:\n");
    // Tant que la pile n'est pas vide
    while (!ds_stack_is_empty(&stack)) {
        int value; // Variable pour stocker la valeur dépilée
        // pop retire et retourne l'élément du sommet
        if (ds_stack_pop(&stack, &value)) {
            printf("  Dépilé: %d\n", value);
        }
    }
    
    // Vérifier que la pile est vide
    printf("Pile vide: %s\n", ds_stack_is_empty(&stack) ? "Oui" : "Non");
}

// ==================== TEST FILE (QUEUE) ====================

void test_queue(void) {
    printf("\n========== TEST FILE (QUEUE) ==========\n\n");
    
    // Queue : structure FIFO (First In First Out)
    Queue queue;
    queue_init(&queue); // Initialiser la file vide
    
    // Créer quelques nœuds d'arbre pour tester
    // ds_btree_create_node alloue de la mémoire avec malloc
    // Retourne un pointeur vers TNode (TNode*)
    TNode* n1 = ds_btree_create_node(10); // n1 est un pointeur vers TNode
    TNode* n2 = ds_btree_create_node(20); // n2 est un pointeur vers TNode
    TNode* n3 = ds_btree_create_node(30);
    TNode* n4 = ds_btree_create_node(40);
    
    // Test enqueue (enfiler)
    printf("Enfilage: 10, 20, 30, 40\n");
    // Enqueue ajoute un élément en queue (tail) de la file
    // On passe les pointeurs n1, n2, etc. (pas &n1 car n1 est déjà un pointeur!)
    queue_enqueue(&queue, n1); // n1 est TNode*, on le passe directement
    queue_enqueue(&queue, n2);
    queue_enqueue(&queue, n3);
    queue_enqueue(&queue, n4);
    
    // Test dequeue (défiler)
    printf("\nDéfilage:\n");
    // Tant que la file n'est pas vide
    while (!queue_is_empty(&queue)) {
        // node est un pointeur vers TNode
        // On va recevoir le pointeur vers le nœud défilé
        TNode* node;
        // dequeue retire l'élément de la tête (head) de la file
        // &node : on passe l'adresse du pointeur pour que la fonction puisse y écrire
        // La fonction écrit dans node le pointeur vers le TNode défilé
        if (queue_dequeue(&queue, &node)) { // Retourne 1 si succès
            // node->data : accès à la donnée du nœud pointé
            printf("  Défilé: %d\n", node->data);
        }
    }
    
    // Nettoyage : libérer la mémoire allouée avec malloc
    // free() libère la mémoire pointée par le pointeur
    free(n1); // Libérer la mémoire allouée pour n1
    free(n2);
    free(n3);
    free(n4);
    queue_clear(&queue);
    printf("File vidée\n");
}

// ==================== TEST ARBRE BINAIRE ====================

void test_btree(void) {
    printf("\n========== TEST ARBRE BINAIRE ==========\n\n");
    
    // BTree : structure contenant un pointeur vers la racine
    BTree tree;
    ds_btree_init(&tree); // Initialiser l'arbre vide (root = NULL)
    
    /* Créer l'arbre:
           8
          /   \
         3     10
        / \      \
       1   6      14
          / \     /
         4   7   13
    */
    // Créer tous les nœuds avec malloc
    // Chaque nœud est un pointeur vers TNode (TNode*)
    TNode* n8 = ds_btree_create_node(8);  // n8 pointe vers un TNode avec data=8
    TNode* n3 = ds_btree_create_node(3);  // n3 pointe vers un TNode avec data=3
    TNode* n10 = ds_btree_create_node(10);
    TNode* n1 = ds_btree_create_node(1);
    TNode* n6 = ds_btree_create_node(6);
    TNode* n14 = ds_btree_create_node(14);
    TNode* n4 = ds_btree_create_node(4);
    TNode* n7 = ds_btree_create_node(7);
    TNode* n13 = ds_btree_create_node(13);
    
    // Construire l'arbre en attachant les nœuds
    tree.root = n8; // La racine de l'arbre pointe vers n8
    // attach_left/right : attacher un nœud enfant à un nœud parent
    // On passe les pointeurs directement (n8, n3 sont déjà des pointeurs)
    ds_btree_attach_left(n8, n3);   // n3 devient le fils gauche de n8
    ds_btree_attach_right(n8, n10); // n10 devient le fils droit de n8
    ds_btree_attach_left(n3, n1);   // n1 devient le fils gauche de n3
    ds_btree_attach_right(n3, n6);  // n6 devient le fils droit de n3
    ds_btree_attach_left(n6, n4);
    ds_btree_attach_right(n6, n7);
    ds_btree_attach_right(n10, n14);
    ds_btree_attach_left(n14, n13);
    
    // Test taille et hauteur
    // tree.root est un pointeur vers TNode, on le passe directement
    printf("Taille de l'arbre: %d nœuds\n", ds_btree_size(tree.root));
    printf("Hauteur de l'arbre: %d\n", ds_btree_height(tree.root));
    
    // Test parcours
    // Les fonctions de parcours prennent un pointeur vers le nœud racine
    // et une fonction callback (print_int) pour traiter chaque valeur
    printf("\nParcours préfixe: ");
    ds_btree_preorder(tree.root, print_int); // tree.root est TNode*
    printf("\n");
    
    printf("Parcours infixe: ");
    ds_btree_inorder(tree.root, print_int);
    printf("\n");
    
    printf("Parcours postfixe: ");
    ds_btree_postorder(tree.root, print_int);
    printf("\n");
    
    printf("Parcours par niveau (BFS): ");
    ds_btree_level_order(tree.root, print_int);
    printf("\n");
    
    // Test recherche
    printf("\nRecherche de 6: ");
    // found est un pointeur vers TNode (ou NULL si non trouvé)
    TNode* found = ds_btree_find(tree.root, 6);
    if (found) { // Si le pointeur n'est pas NULL
        printf("Trouvé! Valeur = %d\n", found->data);
    }
    
    // Nettoyage : libérer toute la mémoire de l'arbre
    ds_btree_clear(&tree); // On passe &tree pour modifier l'arbre
    printf("\nArbre vidé\n");
}

// ==================== TEST ARBRE BINAIRE DE RECHERCHE (BST) ====================

void test_bst(void) {
    printf("\n========== TEST ARBRE BINAIRE DE RECHERCHE (BST) ==========\n\n");
    
    // BST : Binary Search Tree - arbre binaire avec propriété de recherche
    BTree bst;
    ds_btree_init(&bst); // Initialiser l'arbre vide
    
    // Test insertion
    // L'insertion dans un BST place automatiquement les valeurs :
    // - À gauche si < valeur du nœud
    // - À droite si >= valeur du nœud
    printf("Insertion: 50, 30, 70, 20, 40, 60, 80, 10, 25\n");
    // On passe &bst (adresse) car la fonction modifie l'arbre
    ds_bsttree_add(&bst, 50); // 50 devient la racine
    ds_bsttree_add(&bst, 30); // 30 < 50, donc à gauche de 50
    ds_bsttree_add(&bst, 70); // 70 > 50, donc à droite de 50
    ds_bsttree_add(&bst, 20);
    ds_bsttree_add(&bst, 40);
    ds_bsttree_add(&bst, 60);
    ds_bsttree_add(&bst, 80);
    ds_bsttree_add(&bst, 10);
    ds_bsttree_add(&bst, 25);
    
    // Parcours infixe (doit être trié)
    // Dans un BST, le parcours infixe donne toujours les valeurs triées!
    printf("\nParcours infixe (doit être trié): ");
    // bst.root est un pointeur vers TNode, on le passe directement
    ds_btree_inorder(bst.root, print_int);
    printf("\n");
    
    // Test recherche
    // La recherche dans un BST est efficace : O(log n) si équilibré
    printf("\nRecherche de 40: ");
    // found est un pointeur vers TNode (ou NULL)
    TNode* found = ds_bsttree_find(&bst, 40);
    if (found) {
        printf("Trouvé! Valeur = %d\n", found->data);
    } else {
        printf("Non trouvé\n");
    }
    
    // Test suppression
    printf("\nSuppression de 20: ");
    // La suppression dans un BST est complexe (3 cas possibles)
    if (ds_bsttree_remove(&bst, 20)) { // Retourne 1 si succès
        printf("Supprimé avec succès\n");
    }
    printf("Parcours infixe après suppression: ");
    ds_btree_inorder(bst.root, print_int);
    printf("\n");
    
    // Nettoyage
    ds_btree_clear(&bst);
    printf("\nBST vidé\n");
}

// ==================== TEST ARBRE AVL ====================

void test_avl(void) {
    printf("\n========== TEST ARBRE AVL ==========\n\n");
    
    // AVL : arbre auto-équilibré, garantit O(log n) pour toutes les opérations
    AVLTree avl;
    ds_avl_init(&avl); // Initialiser l'arbre vide
    
    // Test insertion avec auto-équilibrage
    // L'AVL s'équilibre automatiquement après chaque insertion
    // en effectuant des rotations si nécessaire
    printf("Insertion: 10, 20, 30, 40, 50, 25\n");
    printf("(L'arbre s'équilibre automatiquement)\n");
    // Chaque insertion peut déclencher des rotations pour maintenir l'équilibre
    ds_avl_insert(&avl, 10);
    ds_avl_insert(&avl, 20);
    ds_avl_insert(&avl, 30); // Peut déclencher une rotation
    ds_avl_insert(&avl, 40);
    ds_avl_insert(&avl, 50);
    ds_avl_insert(&avl, 25);
    
    // Parcours infixe (doit être trié, comme un BST)
    printf("\nParcours infixe: ");
    // avl.root est un pointeur vers AVLNode
    ds_avl_print_inorder(avl.root);
    printf("\n");
    
    printf("Parcours préfixe: ");
    ds_avl_print_preorder(avl.root);
    printf("\n");
    
    // Test taille et hauteur
    // La hauteur d'un AVL est toujours O(log n)
    printf("\nTaille de l'arbre AVL: %d nœuds\n", ds_avl_size(avl.root));
    printf("Hauteur de l'arbre AVL: %d\n", ds_avl_get_height(avl.root));
    
    // Test recherche
    // Recherche en O(log n) garantie
    printf("\nRecherche de 30: ");
    // found est un pointeur vers AVLNode
    AVLNode* found = ds_avl_find(&avl, 30);
    if (found) {
        // found->data : accès à la donnée
        // found->height : accès à la hauteur du nœud (spécifique à AVL)
        printf("Trouvé! Valeur = %d, Hauteur = %d\n", found->data, found->height);
    }
    
    // Test facteur d'équilibre
    // Le facteur d'équilibre = hauteur(droite) - hauteur(gauche)
    // Pour un AVL, ce facteur doit être -1, 0, ou 1
    if (avl.root) { // Vérifier que la racine existe
        int balance = ds_avl_get_balance(avl.root);
        printf("Facteur d'équilibre de la racine: %d (doit être -1, 0, ou 1)\n", balance);
    }
    
    // Test suppression
    // La suppression peut aussi déclencher des rotations
    printf("\nSuppression de 40: ");
    if (ds_avl_remove(&avl, 40)) {
        printf("Supprimé avec succès\n");
    }
    printf("Parcours infixe après suppression: ");
    ds_avl_print_inorder(avl.root);
    printf("\n");
    
    // Nettoyage
    ds_avl_clear(&avl);
    printf("\nArbre AVL vidé\n");
}

// ==================== MENU PRINCIPAL ====================

void print_menu(void) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║     TEST DES STRUCTURES DE DONNÉES                      ║\n");
    printf("╠══════════════════════════════════════════════════════════╣\n");
    printf("║  1. Liste simplement chainée (head)                     ║\n");
    printf("║  2. Liste simplement chainée (head + tail)              ║\n");
    printf("║  3. Liste doublement chainée                             ║\n");
    printf("║  4. Pile (Stack)                                         ║\n");
    printf("║  5. File (Queue)                                         ║\n");
    printf("║  6. Arbre binaire                                        ║\n");
    printf("║  7. Arbre binaire de recherche (BST)                    ║\n");
    printf("║  8. Arbre AVL                                            ║\n");
    printf("║  9. Tous les tests                                       ║\n");
    printf("║  0. Quitter                                              ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    printf("\nVotre choix: ");
}

int main(void) {
    // choice est une variable locale de type int
    int choice;
    
    printf("Bienvenue dans le programme de test des structures de données!\n");
    
    // Boucle infinie pour le menu
    while (1) {
        print_menu(); // Afficher le menu
        
        // scanf("%d", &choice) : lire un entier depuis stdin
        // &choice : on passe l'ADRESSE de choice pour que scanf puisse y écrire
        // scanf retourne le nombre d'éléments lus avec succès (1 si OK, 0 si erreur)
        if (scanf("%d", &choice) != 1) {
            printf("Erreur de saisie. Veuillez entrer un nombre.\n");
            // Vider le buffer d'entrée pour éviter les problèmes
            while (getchar() != '\n'); // Lire jusqu'à trouver '\n'
            continue; // Recommencer la boucle
        }
        
        // switch : structure de contrôle pour choisir selon la valeur de choice
        switch (choice) {
            case 1:
                test_slist(); // Appeler la fonction de test
                break; // Sortir du switch
            case 2:
                test_slist_tail();
                break;
            case 3:
                test_dlist();
                break;
            case 4:
                test_stack();
                break;
            case 5:
                test_queue();
                break;
            case 6:
                test_btree();
                break;
            case 7:
                test_bst();
                break;
            case 8:
                test_avl();
                break;
            case 9:
                // Exécuter tous les tests
                test_slist();
                test_slist_tail();
                test_dlist();
                test_stack();
                test_queue();
                test_btree();
                test_bst();
                test_avl();
                printf("\n✅ Tous les tests sont terminés!\n");
                break;
            case 0:
                printf("\nAu revoir!\n");
                return 0; // Quitter le programme (retourner 0 = succès)
            default:
                // Cas par défaut si choice ne correspond à aucun case
                printf("Choix invalide. Veuillez choisir entre 0 et 9.\n");
                break;
        }
        
        // Attendre que l'utilisateur appuie sur Entrée
        printf("\nAppuyez sur Entrée pour continuer...");
        // Vider le buffer jusqu'à trouver '\n'
        while (getchar() != '\n'); // Lire et ignorer les caractères jusqu'à '\n'
        getchar(); // Consommer le '\n' restant
    }
    
    return 0; // Ne sera jamais atteint à cause de la boucle infinie
}
