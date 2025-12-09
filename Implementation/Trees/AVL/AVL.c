//
// Implémentation de l'arbre AVL
//

#include "AVL.h"
#include <stdio.h>
#include <stdlib.h>

// Fonction utilitaire pour obtenir le maximum de deux entiers
static int max(int a, int b) {
    return (a > b) ? a : b;
}

// Initialiser un arbre AVL vide
// Complexité: O(1)
void ds_avl_init(AVLTree *tree) {
    tree->root = NULL;
}

// Créer un nouveau nœud AVL avec la valeur donnée
// Complexité: O(1)
AVLNode *ds_avl_create_node(int value) {
    AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
    if (!node) return NULL; // Échec d'allocation
    
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Nouveau nœud est une feuille (hauteur 1)
    
    return node;
}

// Vérifier si l'arbre est vide
// Complexité: O(1)
int ds_avl_is_empty(const AVLTree *tree) {
    return tree->root == NULL;
}

// Obtenir la hauteur d'un nœud
// Complexité: O(1)
int ds_avl_get_height(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Calculer le facteur d'équilibre d'un nœud
// Facteur d'équilibre = hauteur(sous-arbre droit) - hauteur(sous-arbre gauche)
// Pour un arbre AVL, ce facteur doit être -1, 0, ou 1
// Complexité: O(1)
int ds_avl_get_balance(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return ds_avl_get_height(node->right) - ds_avl_get_height(node->left);
}

// Mettre à jour la hauteur d'un nœud
// Complexité: O(1)
void ds_avl_update_height(AVLNode *node) {
    if (node != NULL) {
        node->height = 1 + max(ds_avl_get_height(node->left),
                               ds_avl_get_height(node->right));
    }
}

// Rotation simple à droite
// Utilisée quand le sous-arbre gauche est plus haut (facteur d'équilibre < -1)
// Complexité: O(1)
AVLNode *ds_avl_rotate_right(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;
    
    // Effectuer la rotation
    x->right = y;
    y->left = T2;
    
    // Mettre à jour les hauteurs
    ds_avl_update_height(y);
    ds_avl_update_height(x);
    
    // Retourner la nouvelle racine
    return x;
}

// Rotation simple à gauche
// Utilisée quand le sous-arbre droit est plus haut (facteur d'équilibre > 1)
// Complexité: O(1)
AVLNode *ds_avl_rotate_left(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;
    
    // Effectuer la rotation
    y->left = x;
    x->right = T2;
    
    // Mettre à jour les hauteurs
    ds_avl_update_height(x);
    ds_avl_update_height(y);
    
    // Retourner la nouvelle racine
    return y;
}

// Insérer une valeur dans l'arbre AVL
// Complexité: O(log n) où n est le nombre de nœuds
void ds_avl_insert(AVLTree *tree, int value) {
    tree->root = ds_avl_insert_node(tree->root, value);
}

// Insérer une valeur dans un sous-arbre (fonction récursive interne)
// Complexité: O(log n)
AVLNode *ds_avl_insert_node(AVLNode *node, int value) {
    // 1. Insertion BST standard
    if (node == NULL) {
        return ds_avl_create_node(value);
    }
    
    if (value < node->data) {
        node->left = ds_avl_insert_node(node->left, value);
    } else if (value > node->data) {
        node->right = ds_avl_insert_node(node->right, value);
    } else {
        // Valeur déjà présente, ne pas insérer de doublon
        return node;
    }
    
    // 2. Mettre à jour la hauteur du nœud ancêtre
    ds_avl_update_height(node);
    
    // 3. Obtenir le facteur d'équilibre de ce nœud
    int balance = ds_avl_get_balance(node);
    
    // 4. Si le nœud devient déséquilibré, il y a 4 cas possibles
    
    // Cas gauche-gauche (LL)
    if (balance < -1 && value < node->left->data) {
        return ds_avl_rotate_right(node);
    }
    
    // Cas droite-droite (RR)
    if (balance > 1 && value > node->right->data) {
        return ds_avl_rotate_left(node);
    }
    
    // Cas gauche-droite (LR)
    if (balance < -1 && value > node->left->data) {
        node->left = ds_avl_rotate_left(node->left);
        return ds_avl_rotate_right(node);
    }
    
    // Cas droite-gauche (RL)
    if (balance > 1 && value < node->right->data) {
        node->right = ds_avl_rotate_right(node->right);
        return ds_avl_rotate_left(node);
    }
    
    // Retourner le pointeur du nœud (non modifié)
    return node;
}

// Trouver le nœud avec la valeur minimale dans un sous-arbre
// Complexité: O(log n)
AVLNode *ds_avl_find_min(AVLNode *node) {
    if (node == NULL) return NULL;
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Supprimer une valeur de l'arbre AVL
// Complexité: O(log n)
int ds_avl_remove(AVLTree *tree, int value) {
    if (ds_avl_find(tree, value) == NULL) {
        return 0; // Valeur non trouvée
    }
    tree->root = ds_avl_remove_node(tree->root, value);
    return 1; // Succès
}

// Supprimer une valeur d'un sous-arbre (fonction récursive interne)
// Complexité: O(log n)
AVLNode *ds_avl_remove_node(AVLNode *node, int value) {
    // 1. Suppression BST standard
    if (node == NULL) {
        return node;
    }
    
    if (value < node->data) {
        node->left = ds_avl_remove_node(node->left, value);
    } else if (value > node->data) {
        node->right = ds_avl_remove_node(node->right, value);
    } else {
        // Nœud à supprimer trouvé
        
        // Cas 1: Nœud avec 0 ou 1 enfant
        if (node->left == NULL) {
            AVLNode *temp = node->right;
            free(node);
            return temp;
        } else if (node->right == NULL) {
            AVLNode *temp = node->left;
            free(node);
            return temp;
        }
        
        // Cas 2: Nœud avec 2 enfants
        // Remplacer par le successeur (min du sous-arbre droit)
        AVLNode *temp = ds_avl_find_min(node->right);
        node->data = temp->data;
        node->right = ds_avl_remove_node(node->right, temp->data);
    }
    
    // 2. Mettre à jour la hauteur du nœud actuel
    ds_avl_update_height(node);
    
    // 3. Obtenir le facteur d'équilibre
    int balance = ds_avl_get_balance(node);
    
    // 4. Si le nœud devient déséquilibré, effectuer les rotations
    
    // Cas gauche-gauche (LL)
    if (balance < -1 && ds_avl_get_balance(node->left) <= 0) {
        return ds_avl_rotate_right(node);
    }
    
    // Cas gauche-droite (LR)
    if (balance < -1 && ds_avl_get_balance(node->left) > 0) {
        node->left = ds_avl_rotate_left(node->left);
        return ds_avl_rotate_right(node);
    }
    
    // Cas droite-droite (RR)
    if (balance > 1 && ds_avl_get_balance(node->right) >= 0) {
        return ds_avl_rotate_left(node);
    }
    
    // Cas droite-gauche (RL)
    if (balance > 1 && ds_avl_get_balance(node->right) < 0) {
        node->right = ds_avl_rotate_right(node->right);
        return ds_avl_rotate_left(node);
    }
    
    return node;
}

// Rechercher une valeur dans l'arbre AVL
// Complexité: O(log n)
AVLNode *ds_avl_find(AVLTree *tree, int value) {
    return ds_avl_find_in_node(tree->root, value);
}

// Rechercher une valeur dans un sous-arbre
// Complexité: O(log n)
AVLNode *ds_avl_find_in_node(AVLNode *node, int value) {
    if (node == NULL) {
        return NULL;
    }
    
    if (value == node->data) {
        return node;
    } else if (value < node->data) {
        return ds_avl_find_in_node(node->left, value);
    } else {
        return ds_avl_find_in_node(node->right, value);
    }
}

// Afficher l'arbre AVL (parcours infixe - valeurs triées)
// Complexité: O(n)
void ds_avl_print_inorder(AVLNode *node) {
    if (node != NULL) {
        ds_avl_print_inorder(node->left);
        printf("%d ", node->data);
        ds_avl_print_inorder(node->right);
    }
}

// Afficher l'arbre AVL (parcours préfixe)
// Complexité: O(n)
void ds_avl_print_preorder(AVLNode *node) {
    if (node != NULL) {
        printf("%d ", node->data);
        ds_avl_print_preorder(node->left);
        ds_avl_print_preorder(node->right);
    }
}

// Vider un sous-arbre
// Complexité: O(n)
void ds_avl_clear_node(AVLNode *node) {
    if (node != NULL) {
        ds_avl_clear_node(node->left);
        ds_avl_clear_node(node->right);
        free(node);
    }
}

// Vider l'arbre AVL
// Complexité: O(n)
void ds_avl_clear(AVLTree *tree) {
    ds_avl_clear_node(tree->root);
    tree->root = NULL;
}

// Obtenir la taille de l'arbre (nombre de nœuds)
// Complexité: O(n)
int ds_avl_size(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return 1 + ds_avl_size(node->left) + ds_avl_size(node->right);
}

