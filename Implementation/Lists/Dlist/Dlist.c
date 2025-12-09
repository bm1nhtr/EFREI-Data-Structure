//
// Implémentation de la liste doublement chainée
//

#include "Dlist.h"
#include <stdio.h>
#include <stdlib.h>

// Initialiser une liste vide
// Complexité: O(1)
void ds_dlist_init(DList *list) {
    list->head = NULL;
    list->tail = NULL;
}

// Créer une nouvelle liste vide
// Complexité: O(1)
DList ds_dlist_create(void) {
    DList list;
    list.head = NULL;
    list.tail = NULL;
    return list;
}

// Vérifier si la liste est vide
// Complexité: O(1)
int ds_dlist_is_empty(const DList *list) {
    return list->head == NULL;
}

// Créer un nouveau nœud avec la valeur donnée
// Complexité: O(1)
DNode *ds_dlist_create_node(int data) {
    DNode *pnode = (DNode *)malloc(sizeof(DNode));
    if (!pnode) return NULL; // Échec d'allocation
    pnode->data = data;
    pnode->next = NULL;
    pnode->prev = NULL;
    return pnode;
}

// Insérer un élément en tête de liste
// Complexité: O(1)
int ds_dlist_insert_head(DList *list, int value) {
    DNode *new_node = ds_dlist_create_node(value);
    if (!new_node) return 0; // Échec d'allocation
    
    if (ds_dlist_is_empty(list)) {
        // Liste vide: head et tail pointent vers le nouveau nœud
        list->head = new_node;
        list->tail = new_node;
    } else {
        // Insérer avant la tête actuelle
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    
    return 1; // Succès
}

// Insérer un élément en queue de liste
// Complexité: O(1)
int ds_dlist_insert_tail(DList *list, int value) {
    DNode *new_node = ds_dlist_create_node(value);
    if (!new_node) return 0; // Échec d'allocation
    
    if (ds_dlist_is_empty(list)) {
        // Liste vide: head et tail pointent vers le nouveau nœud
        list->head = new_node;
        list->tail = new_node;
    } else {
        // Insérer après la queue actuelle
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    
    return 1; // Succès
}

// Insérer après un nœud donné
// Complexité: O(1)
int ds_dlist_insert_after(DList *list, DNode *node, int value) {
    if (!node) return 0; // Nœud invalide
    
    DNode *new_node = ds_dlist_create_node(value);
    if (!new_node) return 0; // Échec d'allocation
    
    new_node->prev = node;
    new_node->next = node->next;
    
    if (node->next != NULL) {
        node->next->prev = new_node;
    } else {
        // node était le dernier, mettre à jour tail
        list->tail = new_node;
    }
    
    node->next = new_node;
    return 1; // Succès
}

// Insérer avant un nœud donné
// Complexité: O(1)
int ds_dlist_insert_before(DList *list, DNode *node, int value) {
    if (!node) return 0; // Nœud invalide
    
    DNode *new_node = ds_dlist_create_node(value);
    if (!new_node) return 0; // Échec d'allocation
    
    new_node->next = node;
    new_node->prev = node->prev;
    
    if (node->prev != NULL) {
        node->prev->next = new_node;
    } else {
        // node était le premier, mettre à jour head
        list->head = new_node;
    }
    
    node->prev = new_node;
    return 1; // Succès
}

// Supprimer le premier élément
// Complexité: O(1)
int ds_dlist_remove_head(DList *list, int *out) {
    if (ds_dlist_is_empty(list)) {
        return 0; // Liste vide
    }
    
    DNode *old_head = list->head;
    if (out) {
        *out = old_head->data;
    }
    
    list->head = old_head->next;
    
    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        // La liste devient vide
        list->tail = NULL;
    }
    
    free(old_head);
    return 1; // Succès
}

// Supprimer le dernier élément
// Complexité: O(1) grâce aux pointeurs bidirectionnels
int ds_dlist_remove_tail(DList *list, int *out) {
    if (ds_dlist_is_empty(list)) {
        return 0; // Liste vide
    }
    
    DNode *old_tail = list->tail;
    if (out) {
        *out = old_tail->data;
    }
    
    list->tail = old_tail->prev;
    
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        // La liste devient vide
        list->head = NULL;
    }
    
    free(old_tail);
    return 1; // Succès
}

// Supprimer un nœud spécifique
// Complexité: O(1) car on a les pointeurs prev et next
int ds_dlist_remove_node(DList *list, DNode *node, int *out) {
    if (!node || ds_dlist_is_empty(list)) {
        return 0; // Nœud invalide ou liste vide
    }
    
    if (out) {
        *out = node->data;
    }
    
    // Mettre à jour les pointeurs des nœuds adjacents
    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        // node était le premier
        list->head = node->next;
    }
    
    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        // node était le dernier
        list->tail = node->prev;
    }
    
    free(node);
    return 1; // Succès
}

// Supprimer la première occurrence d'une valeur
// Complexité: O(n) dans le pire cas
int ds_dlist_remove_value(DList *list, int value) {
    DNode *node = ds_dlist_find(list, value);
    if (node) {
        return ds_dlist_remove_node(list, node, NULL);
    }
    return 0; // Valeur non trouvée
}

// Afficher la liste de gauche à droite
// Complexité: O(n)
void ds_dlist_print_forward(const DList *list) {
    const DNode *cur = list->head;
    printf("[");
    while (cur) {
        printf("%d", cur->data);
        if (cur->next != NULL) {
            printf(" <--> ");
        }
        cur = cur->next;
    }
    printf("]\n");
}

// Afficher la liste de droite à gauche
// Complexité: O(n)
void ds_dlist_print_backward(const DList *list) {
    const DNode *cur = list->tail;
    printf("[");
    while (cur) {
        printf("%d", cur->data);
        if (cur->prev != NULL) {
            printf(" <--> ");
        }
        cur = cur->prev;
    }
    printf("]\n");
}

// Trouver un nœud avec une valeur donnée
// Complexité: O(n) dans le pire cas
DNode *ds_dlist_find(const DList *list, int value) {
    DNode *cur = list->head;
    while (cur != NULL) {
        if (cur->data == value) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL; // Non trouvé
}

// Vider complètement la liste
// Complexité: O(n)
void ds_dlist_clear(DList *list) {
    DNode *cur = list->head;
    while (cur != NULL) {
        DNode *next = cur->next;
        free(cur);
        cur = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

