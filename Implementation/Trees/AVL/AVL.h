//
// Arbre AVL (Adelson-Velsky et Landis)
// Arbre binaire de recherche auto-équilibré
// La différence de hauteur entre les sous-arbres gauche et droit est au plus 1
//

#ifndef LINKEDLIST_AVL_H
#define LINKEDLIST_AVL_H

// Structure d'un nœud AVL
typedef struct AVLNode {
    int data;                    // Donnée stockée
    struct AVLNode *left;        // Fils gauche
    struct AVLNode *right;       // Fils droit
    int height;                  // Hauteur du nœud (pour calculer le facteur d'équilibre)
} AVLNode;

// Structure de l'arbre AVL
typedef struct AVLTree {
    AVLNode *root;               // Racine de l'arbre
} AVLTree;

// Initialiser un arbre AVL vide
void ds_avl_init(AVLTree *tree);

// Créer un nouveau nœud AVL
AVLNode *ds_avl_create_node(int value);

// Vérifier si l'arbre est vide
int ds_avl_is_empty(const AVLTree *tree);

// Obtenir la hauteur d'un nœud
int ds_avl_get_height(AVLNode *node);

// Calculer le facteur d'équilibre d'un nœud (hauteur droite - hauteur gauche)
int ds_avl_get_balance(AVLNode *node);

// Mettre à jour la hauteur d'un nœud
void ds_avl_update_height(AVLNode *node);

// Rotation simple à droite (cas gauche-gauche)
AVLNode *ds_avl_rotate_right(AVLNode *y);

// Rotation simple à gauche (cas droite-droite)
AVLNode *ds_avl_rotate_left(AVLNode *x);

// Insérer une valeur dans l'arbre AVL
void ds_avl_insert(AVLTree *tree, int value);

// Insérer une valeur dans un sous-arbre (fonction récursive interne)
AVLNode *ds_avl_insert_node(AVLNode *node, int value);

// Supprimer une valeur de l'arbre AVL
int ds_avl_remove(AVLTree *tree, int value);

// Supprimer une valeur d'un sous-arbre (fonction récursive interne)
AVLNode *ds_avl_remove_node(AVLNode *node, int value);

// Trouver le nœud avec la valeur minimale dans un sous-arbre
AVLNode *ds_avl_find_min(AVLNode *node);

// Rechercher une valeur dans l'arbre AVL
AVLNode *ds_avl_find(AVLTree *tree, int value);

// Rechercher une valeur dans un sous-arbre
AVLNode *ds_avl_find_in_node(AVLNode *node, int value);

// Afficher l'arbre AVL (parcours infixe)
void ds_avl_print_inorder(AVLNode *node);

// Afficher l'arbre AVL (parcours préfixe)
void ds_avl_print_preorder(AVLNode *node);

// Vider l'arbre AVL
void ds_avl_clear(AVLTree *tree);

// Vider un sous-arbre
void ds_avl_clear_node(AVLNode *node);

// Obtenir la taille de l'arbre
int ds_avl_size(AVLNode *node);

#endif //LINKEDLIST_AVL_H

