//
// Liste doublement chainée
// Chaque nœud a un pointeur vers le nœud suivant ET le nœud précédent
// Permet de parcourir la liste dans les deux sens
//

#ifndef LINKEDLIST_DLIST_H
#define LINKEDLIST_DLIST_H

// Structure d'un nœud doublement chainé
typedef struct DNode {
    int data;              // Donnée stockée dans le nœud
    struct DNode *next;    // Pointeur vers le nœud suivant
    struct DNode *prev;    // Pointeur vers le nœud précédent
} DNode;

// Structure de la liste doublement chainée
typedef struct DList {
    DNode *head;  // Pointeur vers le premier nœud
    DNode *tail;  // Pointeur vers le dernier nœud
} DList;

// Initialisation d'une liste vide
void ds_dlist_init(DList *list);

// Création d'une nouvelle liste vide
DList ds_dlist_create(void);

// Vérifier si la liste est vide
int ds_dlist_is_empty(const DList *list);

// Créer un nouveau nœud
DNode *ds_dlist_create_node(int data);

// Insérer un élément en tête - O(1)
int ds_dlist_insert_head(DList *list, int value);

// Insérer un élément en queue - O(1)
int ds_dlist_insert_tail(DList *list, int value);

// Insérer après un nœud donné - O(1)
int ds_dlist_insert_after(DList *list, DNode *node, int value);

// Insérer avant un nœud donné - O(1)
int ds_dlist_insert_before(DList *list, DNode *node, int value);

// Supprimer le premier élément - O(1)
int ds_dlist_remove_head(DList *list, int *out);

// Supprimer le dernier élément - O(1) grâce aux pointeurs bidirectionnels
int ds_dlist_remove_tail(DList *list, int *out);

// Supprimer un nœud spécifique - O(1)
int ds_dlist_remove_node(DList *list, DNode *node, int *out);

// Supprimer la première occurrence d'une valeur - O(n)
int ds_dlist_remove_value(DList *list, int value);

// Afficher la liste de gauche à droite
void ds_dlist_print_forward(const DList *list);

// Afficher la liste de droite à gauche
void ds_dlist_print_backward(const DList *list);

// Trouver un nœud avec une valeur donnée
DNode *ds_dlist_find(const DList *list, int value);

// Vider la liste
void ds_dlist_clear(DList *list);

#endif //LINKEDLIST_DLIST_H

