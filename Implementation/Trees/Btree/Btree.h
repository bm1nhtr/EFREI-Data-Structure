//
// Arbre binaire et Arbre binaire de recherche (BST)
//

#ifndef LINKEDLIST_BTREE_H
#define LINKEDLIST_BTREE_H

// Structure d'un nœud d'arbre binaire
typedef struct TNode {
    int data;                    // Donnée stockée dans le nœud
    struct TNode *left;          // Pointeur vers le fils gauche
    struct TNode *right;         // Pointeur vers le fils droit
} TNode;

// Structure de l'arbre binaire
typedef struct BTree {
    struct TNode *root;          // Pointeur vers la racine de l'arbre
} BTree;

// Fonctions de base pour arbre binaire

// Initialiser un arbre binaire vide - O(1)
void ds_btree_init(BTree* tree);

// Créer un nouveau nœud avec la valeur donnée - O(1)
TNode* ds_btree_create_node(int value);

// Attacher un nœud enfant à gauche d'un nœud parent - O(1), pas d'écrasement
int ds_btree_attach_left(TNode* parent, TNode* child);

// Attacher un nœud enfant à droite d'un nœud parent - O(1), pas d'écrasement
int ds_btree_attach_right(TNode* parent, TNode* child);

// Vérifier si l'arbre est vide - O(1)
int ds_btree_is_empty(const BTree* tree);

// Calculer la taille (nombre de nœuds) de l'arbre/sous-arbre - O(n)
int ds_btree_size(TNode* node);

// Types de pointeurs de fonction pour les parcours d'arbre
typedef void(*ds_visit_fn)(int value);        // Fonction callback pour visiter la donnée d'un nœud (int)
typedef void(*ds_visit_node_fn)(TNode* node); // Fonction callback pour visiter un nœud entier

// Opérations sur l'arbre
void ds_btree_clear(BTree* tree); // Vider tous les nœuds de l'arbre

// Fonctions de parcours d'arbre
void ds_btree_preorder_display(const TNode* pnode); // Afficher l'arbre en préfixe (print vers stdout)
void ds_btree_preorder(const TNode* pnode, ds_visit_fn visit); // Parcours préfixe avec callback
void ds_btree_inorder(const TNode* pnode, ds_visit_fn visit);  // Parcours infixe avec callback
void ds_btree_postorder(const TNode* pnode, ds_visit_fn visit); // Parcours postfixe avec callback

// Fonctions de parcours visitant les nœuds entiers (pas seulement la donnée)
void ds_btree_preorder_node(const TNode* pnode, ds_visit_node_fn visit);
void ds_btree_inorder_node(const TNode* pnode, ds_visit_node_fn visit);
void ds_btree_postorder_node(const TNode* pnode, ds_visit_node_fn visit);

// Fonctions utilitaires pour l'arbre
int ds_btree_height(TNode* pnode);        // Calculer la hauteur de l'arbre/sous-arbre
TNode* ds_btree_find(TNode* pnode, int val); // Trouver un nœud avec une valeur donnée
int ds_btree_depth_of(TNode* pnode, int val); // Trouver la profondeur d'un nœud avec une valeur donnée

// Parcours par niveau (BFS - Breadth First Search) - O(n)
void ds_btree_level_order(TNode* pnode, ds_visit_fn visit);

// Fonctions pour arbre binaire de recherche (BST)
void ds_bsttree_add(BTree* tree, int value);                    // Ajouter une valeur dans un BST
void ds_bsttree_add_to_node(TNode* cur, int value);            // Ajouter une valeur dans un sous-arbre
TNode* ds_bsttree_find(BTree* tree, int value);                // Rechercher une valeur dans un BST
TNode* ds_bsttree_find_in_node(TNode* node, int value);        // Rechercher une valeur dans un sous-arbre
int ds_bsttree_remove(BTree* tree, int value);                 // Supprimer une valeur d'un BST







#endif //LINKEDLIST_BTREE_H