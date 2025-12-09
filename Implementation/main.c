//
// Fichier de test pour toutes les structures de donnees
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

// Fonction helper pour afficher un entier en hexadecimal
// (Non utilisee actuellement, mais disponible pour les tests futurs)
// static void print_int_in_hex(int v) {
//     printf("%x ", v);
// }

// Fonction helper pour afficher la valeur d'un nœud d'arbre
// (Non utilisee actuellement, mais disponible pour les tests futurs)
// pnode est un pointeur vers TNode (TNode*)
// On utilise -> pour acceder au champ data du nœud pointe
// static void print_node_value(TNode* pnode) {
//     if (pnode) printf("%d ", pnode->data); // pnode->data accede a la donnee du nœud
// }

// ==================== TEST LISTE SIMPLEMENT CHAINeE (HEAD) ====================

void test_slist(void) {
    printf("\n========== TEST LISTE SIMPLEMENT CHAINEE (HEAD) ==========\n\n");
    
    // Declaration d'une variable de type SList (structure de liste)
    // list est une variable locale, pas un pointeur
    SList list;
    
    // ds_slist_init(&list) : on passe l'ADRESSE de list avec &list
    // &list retourne un pointeur vers list (SList*)
    // La fonction init modifie directement la liste passee par adresse
    ds_slist_init(&list);
    
    // Test insertion
    printf("Insertion en tete: 10, 20, 30\n");
    // On passe &list (adresse) car la fonction modifie la liste
    // Les valeurs 10, 20, 30 sont passees par valeur (int)
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
    // ds_slist_find retourne un pointeur vers le nœud trouve, ou NULL si non trouve
    SNode* found = ds_slist_find(&list, 20);
    if (found) { // Si found n'est pas NULL (nœud trouve)
        // found->data : on utilise -> pour acceder au champ data du nœud pointe
        // found est un pointeur, donc on utilise -> et non .
        printf("Trouve! Valeur = %d\n", found->data);
    } else {
        printf("Non trouve\n");
    }
    
    // Test insertion a un index
    printf("\nInsertion de 99 a l'index 2\n");
    ds_slist_insert_at(&list, 2, 99);
    ds_slist_print(&list);
    
    // Test suppression
    // value est une variable locale pour stocker la valeur supprimee
    int value;
    printf("\nSuppression de la tete: ");
    // ds_slist_remove_head(&list, &value) :
    //   - &list : adresse de la liste a modifier
    //   - &value : adresse de la variable ou stocker la valeur supprimee
    //   La fonction retourne 1 si succes, 0 si echec
    if (ds_slist_remove_head(&list, &value)) {
        printf("Valeur supprimee = %d\n", value);
    }
    ds_slist_print(&list);
    
    printf("\nSuppression de la valeur 100: ");
    if (ds_slist_remove_value(&list, 100)) {
        printf("Supprime avec succes\n");
    }
    ds_slist_print(&list);
    
    // Nettoyage : liberer toute la memoire allouee
    ds_slist_clear(&list);
    printf("\nListe videe\n");
}

// ==================== TEST LISTE SIMPLEMENT CHAINeE (HEAD + TAIL) ====================

void test_slist_tail(void) {
    printf("\n========== TEST LISTE SIMPLEMENT CHAINEE (HEAD + TAIL) ==========\n\n");
    
    // SListTail est une structure qui contient head ET tail
    // Cela permet insertion en queue en O(1) au lieu de O(n)
    SListTail list;
    ds_slist_tail_init(&list); // Initialiser avec &list (adresse)
    
    // Test insertion en queue (O(1) maintenant grâce au pointeur tail!)
    printf("Insertion en queue: 1, 2, 3, 4, 5\n");
    // Chaque insertion est O(1) car on a directement acces au dernier nœud via tail
    ds_slist_tail_insert_tail(&list, 1);
    ds_slist_tail_insert_tail(&list, 2);
    ds_slist_tail_insert_tail(&list, 3);
    ds_slist_tail_insert_tail(&list, 4);
    ds_slist_tail_insert_tail(&list, 5);
    ds_slist_tail_print(&list);
    
    printf("\nInsertion en tete: 0\n");
    ds_slist_tail_insert_head(&list, 0);
    ds_slist_tail_print(&list);
    
    // Test recherche
    printf("\nRecherche de 3: ");
    // found est un pointeur vers SNodeTail
    // La fonction retourne un pointeur vers le nœud ou NULL
    SNodeTail* found = ds_slist_tail_find(&list, 3);
    if (found) { // Verifier si le pointeur n'est pas NULL
        // found->data : acces au champ data via le pointeur
        printf("Trouve! Valeur = %d\n", found->data);
    }
    
    // Test suppression
    int value; // Variable pour stocker la valeur supprimee
    printf("\nSuppression de la tete: ");
    // &value : on passe l'adresse pour que la fonction puisse y ecrire la valeur
    if (ds_slist_tail_remove_head(&list, &value)) {
        printf("Valeur supprimee = %d\n", value);
    }
    ds_slist_tail_print(&list);
    
    // Nettoyage
    ds_slist_tail_clear(&list);
    printf("\nListe videe\n");
}

// ==================== TEST LISTE DOUBLEMENT CHAINeE ====================

void test_dlist(void) {
    printf("\n========== TEST LISTE DOUBLEMENT CHAINEE ==========\n\n");
    
    // DList : liste doublement chainee, chaque nœud a prev ET next
    DList list;
    ds_dlist_init(&list); // Initialiser avec l'adresse
    
    // Test insertion
    printf("Insertion en tete: 10, 20\n");
    ds_dlist_insert_head(&list, 10);
    ds_dlist_insert_head(&list, 20);
    ds_dlist_print_forward(&list); // Parcours de gauche a droite
    
    printf("\nInsertion en queue: 30, 40\n");
    ds_dlist_insert_tail(&list, 30);
    ds_dlist_insert_tail(&list, 40);
    ds_dlist_print_forward(&list);
    
    // Test parcours inverse (avantage de la liste doublement chainee!)
    printf("\nParcours inverse: ");
    // On peut parcourir de droite a gauche grâce au pointeur prev
    ds_dlist_print_backward(&list);
    
    // Test insertion apres un nœud
    // ds_dlist_find retourne un pointeur vers DNode (ou NULL)
    DNode* node = ds_dlist_find(&list, 20);
    if (node) { // Si le nœud existe (pointeur non NULL)
        printf("\nInsertion de 25 apres 20\n");
        // On peut inserer directement apres un nœud en O(1) car on a les pointeurs prev et next
        ds_dlist_insert_after(&list, node, 25);
        ds_dlist_print_forward(&list);
    }
    
    // Test suppression
    int value;
    printf("\nSuppression de la queue: ");
    // Suppression en O(1) grâce au pointeur tail et prev
    if (ds_dlist_remove_tail(&list, &value)) {
        printf("Valeur supprimee = %d\n", value);
    }
    ds_dlist_print_forward(&list);
    
    // Nettoyage
    ds_dlist_clear(&list);
    printf("\nListe videe\n");
}

// ==================== TEST PILE (STACK) ====================

void test_stack(void) {
    printf("\n========== TEST PILE (STACK) ==========\n\n");
    
    // Stack : structure LIFO (Last In First Out)
    Stack stack;
    ds_stack_init(&stack); // Initialiser la pile vide
    
    // Test push (empiler)
    printf("Empilement: 10, 20, 30, 40\n");
    // Push ajoute un element au sommet (top) de la pile
    // Toutes les operations sont O(1)
    ds_stack_push(&stack, 10);
    ds_stack_push(&stack, 20);
    ds_stack_push(&stack, 30);
    ds_stack_push(&stack, 40);
    ds_stack_print(&stack); // Affiche du sommet vers le bas
    
    printf("Taille de la pile: %d\n", ds_stack_size(&stack));
    
    // Test peek (consulter sans retirer)
    int top; // Variable pour stocker la valeur du sommet
    // peek lit la valeur au sommet sans la retirer
    if (ds_stack_peek(&stack, &top)) { // Retourne 1 si succes
        printf("Sommet de la pile: %d\n", top);
    }
    
    // Test pop (depiler)
    printf("\nDepilement:\n");
    // Tant que la pile n'est pas vide
    while (!ds_stack_is_empty(&stack)) {
        int value; // Variable pour stocker la valeur depilee
        // pop retire et retourne l'element du sommet
        if (ds_stack_pop(&stack, &value)) {
            printf("  Depile: %d\n", value);
        }
    }
    
    // Verifier que la pile est vide
    printf("Pile vide: %s\n", ds_stack_is_empty(&stack) ? "Oui" : "Non");
}

// ==================== TEST FILE (QUEUE) ====================

void test_queue(void) {
    printf("\n========== TEST FILE (QUEUE) ==========\n\n");
    
    // Queue : structure FIFO (First In First Out)
    Queue queue;
    queue_init(&queue); // Initialiser la file vide
    
    // Creer quelques nœuds d'arbre pour tester
    // ds_btree_create_node alloue de la memoire avec malloc
    // Retourne un pointeur vers TNode (TNode*)
    TNode* n1 = ds_btree_create_node(10); // n1 est un pointeur vers TNode
    TNode* n2 = ds_btree_create_node(20); // n2 est un pointeur vers TNode
    TNode* n3 = ds_btree_create_node(30);
    TNode* n4 = ds_btree_create_node(40);
    
    // Test enqueue (enfiler)
    printf("Enfilage: 10, 20, 30, 40\n");
    // Enqueue ajoute un element en queue (tail) de la file
    // On passe les pointeurs n1, n2, etc. (pas &n1 car n1 est deja un pointeur!)
    queue_enqueue(&queue, n1); // n1 est TNode*, on le passe directement
    queue_enqueue(&queue, n2);
    queue_enqueue(&queue, n3);
    queue_enqueue(&queue, n4);
    
    // Test dequeue (defiler)
    printf("\nDefilage:\n");
    // Tant que la file n'est pas vide
    while (!queue_is_empty(&queue)) {
        // node est un pointeur vers TNode
        // On va recevoir le pointeur vers le nœud defile
        TNode* node;
        // dequeue retire l'element de la tete (head) de la file
        // &node : on passe l'adresse du pointeur pour que la fonction puisse y ecrire
        // La fonction ecrit dans node le pointeur vers le TNode defile
        if (queue_dequeue(&queue, &node)) { // Retourne 1 si succes
            // node->data : acces a la donnee du nœud pointe
            printf("  Defile: %d\n", node->data);
        }
    }
    
    // Nettoyage : liberer la memoire allouee avec malloc
    // free() libere la memoire pointee par le pointeur
    free(n1); // Liberer la memoire allouee pour n1
    free(n2);
    free(n3);
    free(n4);
    queue_clear(&queue);
    printf("File videe\n");
}

// ==================== TEST ARBRE BINAIRE ====================

void test_btree(void) {
    printf("\n========== TEST ARBRE BINAIRE ==========\n\n");
    
    // BTree : structure contenant un pointeur vers la racine
    BTree tree;
    ds_btree_init(&tree); // Initialiser l'arbre vide (root = NULL)
    
    /* Creer l'arbre:
           8
          /   \
         3     10
        / \      \
       1   6      14
          / \     /
         4   7   13
    */
    // Creer tous les nœuds avec malloc
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
    // attach_left/right : attacher un nœud enfant a un nœud parent
    // On passe les pointeurs directement (n8, n3 sont deja des pointeurs)
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
    printf("Taille de l'arbre: %d noeuds\n", ds_btree_size(tree.root));
    printf("Hauteur de l'arbre: %d\n", ds_btree_height(tree.root));
    
    // Test parcours
    // Les fonctions de parcours prennent un pointeur vers le nœud racine
    // et une fonction callback (print_int) pour traiter chaque valeur
    printf("\nParcours prefixe: ");
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
    // found est un pointeur vers TNode (ou NULL si non trouve)
    TNode* found = ds_btree_find(tree.root, 6);
    if (found) { // Si le pointeur n'est pas NULL
        printf("Trouve! Valeur = %d\n", found->data);
    }
    
    // Nettoyage : liberer toute la memoire de l'arbre
    ds_btree_clear(&tree); // On passe &tree pour modifier l'arbre
    printf("\nArbre vide\n");
}

// ==================== TEST ARBRE BINAIRE DE RECHERCHE (BST) ====================

void test_bst(void) {
    printf("\n========== TEST ARBRE BINAIRE DE RECHERCHE (BST) ==========\n\n");
    
    // BST : Binary Search Tree - arbre binaire avec propriete de recherche
    BTree bst;
    ds_btree_init(&bst); // Initialiser l'arbre vide
    
    // Test insertion
    // L'insertion dans un BST place automatiquement les valeurs :
    // - a gauche si < valeur du nœud
    // - a droite si >= valeur du nœud
    printf("Insertion: 50, 30, 70, 20, 40, 60, 80, 10, 25\n");
    // On passe &bst (adresse) car la fonction modifie l'arbre
    ds_bsttree_add(&bst, 50); // 50 devient la racine
    ds_bsttree_add(&bst, 30); // 30 < 50, donc a gauche de 50
    ds_bsttree_add(&bst, 70); // 70 > 50, donc a droite de 50
    ds_bsttree_add(&bst, 20);
    ds_bsttree_add(&bst, 40);
    ds_bsttree_add(&bst, 60);
    ds_bsttree_add(&bst, 80);
    ds_bsttree_add(&bst, 10);
    ds_bsttree_add(&bst, 25);
    
    // Parcours infixe (doit etre trie)
    // Dans un BST, le parcours infixe donne toujours les valeurs triees!
    printf("\nParcours infixe (doit etre trie): ");
    // bst.root est un pointeur vers TNode, on le passe directement
    ds_btree_inorder(bst.root, print_int);
    printf("\n");
    
    // Test recherche
    // La recherche dans un BST est efficace : O(log n) si equilibre
    printf("\nRecherche de 40: ");
    // found est un pointeur vers TNode (ou NULL)
    TNode* found = ds_bsttree_find(&bst, 40);
    if (found) {
        printf("Trouve! Valeur = %d\n", found->data);
    } else {
        printf("Non trouve\n");
    }
    
    // Test suppression
    printf("\nSuppression de 20: ");
    // La suppression dans un BST est complexe (3 cas possibles)
    if (ds_bsttree_remove(&bst, 20)) { // Retourne 1 si succes
        printf("Supprime avec succes\n");
    }
    printf("Parcours infixe apres suppression: ");
    ds_btree_inorder(bst.root, print_int);
    printf("\n");
    
    // Nettoyage
    ds_btree_clear(&bst);
    printf("\nBST vide\n");
}

// ==================== TEST ARBRE AVL ====================

void test_avl(void) {
    printf("\n========== TEST ARBRE AVL ==========\n\n");
    
    // AVL : arbre auto-equilibre, garantit O(log n) pour toutes les operations
    AVLTree avl;
    ds_avl_init(&avl); // Initialiser l'arbre vide
    
    // Test insertion avec auto-equilibrage
    // L'AVL s'equilibre automatiquement apres chaque insertion
    // en effectuant des rotations si necessaire
    printf("Insertion: 10, 20, 30, 40, 50, 25\n");
    printf("(L'arbre s'equilibre automatiquement)\n");
    // Chaque insertion peut declencher des rotations pour maintenir l'equilibre
    ds_avl_insert(&avl, 10);
    ds_avl_insert(&avl, 20);
    ds_avl_insert(&avl, 30); // Peut declencher une rotation
    ds_avl_insert(&avl, 40);
    ds_avl_insert(&avl, 50);
    ds_avl_insert(&avl, 25);
    
    // Parcours infixe (doit etre trie, comme un BST)
    printf("\nParcours infixe: ");
    // avl.root est un pointeur vers AVLNode
    ds_avl_print_inorder(avl.root);
    printf("\n");
    
    printf("Parcours prefixe: ");
    ds_avl_print_preorder(avl.root);
    printf("\n");
    
    // Test taille et hauteur
    // La hauteur d'un AVL est toujours O(log n)
    printf("\nTaille de l'arbre AVL: %d noeuds\n", ds_avl_size(avl.root));
    printf("Hauteur de l'arbre AVL: %d\n", ds_avl_get_height(avl.root));
    
    // Test recherche
    // Recherche en O(log n) garantie
    printf("\nRecherche de 30: ");
    // found est un pointeur vers AVLNode
    AVLNode* found = ds_avl_find(&avl, 30);
    if (found) {
        // found->data : acces a la donnee
        // found->height : acces a la hauteur du nœud (specifique a AVL)
        printf("Trouve! Valeur = %d, Hauteur = %d\n", found->data, found->height);
    }
    
    // Test facteur d'equilibre
    // Le facteur d'equilibre = hauteur(droite) - hauteur(gauche)
    // Pour un AVL, ce facteur doit etre -1, 0, ou 1
    if (avl.root) { // Verifier que la racine existe
        int balance = ds_avl_get_balance(avl.root);
        printf("Facteur d'equilibre de la racine: %d (doit etre -1, 0, ou 1)\n", balance);
    }
    
    // Test suppression
    // La suppression peut aussi declencher des rotations
    printf("\nSuppression de 40: ");
    if (ds_avl_remove(&avl, 40)) {
        printf("Supprime avec succes\n");
    }
    printf("Parcours infixe apres suppression: ");
    ds_avl_print_inorder(avl.root);
    printf("\n");
    
    // Nettoyage
    ds_avl_clear(&avl);
    printf("\nArbre AVL vide\n");
}

// ==================== MENU PRINCIPAL ====================

void print_menu(void) {
    printf("\n");
    printf("============================================================\n");
    printf("     TEST DES STRUCTURES DE DONNEES\n");
    printf("============================================================\n");
    printf("  1. Liste simplement chainee (head)\n");
    printf("  2. Liste simplement chainee (head + tail)\n");
    printf("  3. Liste doublement chainee\n");
    printf("  4. Pile (Stack)\n");
    printf("  5. File (Queue)\n");
    printf("  6. Arbre binaire\n");
    printf("  7. Arbre binaire de recherche (BST)\n");
    printf("  8. Arbre AVL\n");
    printf("  9. Tous les tests\n");
    printf("  0. Quitter\n");
    printf("============================================================\n");
    printf("\nVotre choix: ");
}

int main(void) {
    // choice est une variable locale de type int
    int choice;
    
    printf("Bienvenue dans le programme de test des structures de donnees!\n");
    
    // Boucle infinie pour le menu
    while (1) {
        print_menu(); // Afficher le menu
        
        // scanf("%d", &choice) : lire un entier depuis stdin
        // &choice : on passe l'ADRESSE de choice pour que scanf puisse y ecrire
        // scanf retourne le nombre d'elements lus avec succes (1 si OK, 0 si erreur)
        if (scanf("%d", &choice) != 1) {
            printf("Erreur de saisie. Veuillez entrer un nombre.\n");
            // Vider le buffer d'entree pour eviter les problemes
            while (getchar() != '\n'); // Lire jusqu'a trouver '\n'
            continue; // Recommencer la boucle
        }
        
        // switch : structure de controle pour choisir selon la valeur de choice
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
                // Executer tous les tests
                test_slist();
                test_slist_tail();
                test_dlist();
                test_stack();
                test_queue();
                test_btree();
                test_bst();
                test_avl();
                printf("\n[OK] Tous les tests sont termines!\n");
                break;
            case 0:
                printf("\nAu revoir!\n");
                return 0; // Quitter le programme (retourner 0 = succes)
            default:
                // Cas par defaut si choice ne correspond a aucun case
                printf("Choix invalide. Veuillez choisir entre 0 et 9.\n");
                break;
        }
        
        // Attendre que l'utilisateur appuie sur Entree
        printf("\nAppuyez sur Entree pour continuer...");
        // Vider le buffer jusqu'a trouver '\n'
        while (getchar() != '\n'); // Lire et ignorer les caracteres jusqu'a '\n'
        getchar(); // Consommer le '\n' restant
    }
    
    return 0; // Ne sera jamais atteint a cause de la boucle infinie
}

