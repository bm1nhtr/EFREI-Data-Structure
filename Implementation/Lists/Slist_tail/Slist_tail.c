//
// Implémentation de la liste simplement chainée avec head et tail
//

#include "Slist_tail.h"
#include <stdio.h>
#include <stdlib.h>

// Initialiser une liste vide
// Complexité: O(1)
void ds_slist_tail_init(SListTail *list) {
    list->head = NULL;
    list->tail = NULL;
}

// Créer une nouvelle liste vide
// Complexité: O(1)
SListTail ds_slist_tail_create(void) {
    SListTail list;
    list.head = NULL;
    list.tail = NULL;
    return list;
}

// Vérifier si la liste est vide
// Complexité: O(1)
int ds_slist_tail_is_empty(const SListTail *list) {
    return list->head == NULL;
}

// Créer un nouveau nœud avec la valeur donnée
// Complexité: O(1)
SNodeTail *ds_slist_tail_create_node(int data) {
    SNodeTail *pnode = (SNodeTail *)malloc(sizeof(SNodeTail));
    if (!pnode) return NULL; // Échec d'allocation
    pnode->data = data;
    pnode->next = NULL;
    return pnode;
}

// Insérer un élément en tête de liste
// Complexité: O(1)
int ds_slist_tail_insert_head(SListTail *list, int value) {
    SNodeTail *new_node = ds_slist_tail_create_node(value);
    if (!new_node) return 0; // Échec d'allocation
    
    new_node->next = list->head;
    list->head = new_node;
    
    // Si la liste était vide, tail pointe aussi vers le nouveau nœud
    if (list->tail == NULL) {
        list->tail = new_node;
    }
    
    return 1; // Succès
}

// Insérer un élément en queue de liste
// Complexité: O(1) grâce au pointeur tail (contrairement à la version head-only qui est O(n))
int ds_slist_tail_insert_tail(SListTail *list, int value) {
    SNodeTail *new_node = ds_slist_tail_create_node(value);
    if (!new_node) return 0; // Échec d'allocation
    
    if (ds_slist_tail_is_empty(list)) {
        // Liste vide: head et tail pointent vers le nouveau nœud
        list->head = new_node;
        list->tail = new_node;
    } else {
        // Ajouter après le dernier élément et mettre à jour tail
        list->tail->next = new_node;
        list->tail = new_node;
    }
    
    return 1; // Succès
}

// Supprimer le premier élément
// Complexité: O(1)
int ds_slist_tail_remove_head(SListTail *list, int *out) {
    if (ds_slist_tail_is_empty(list)) {
        return 0; // Liste vide
    }
    
    SNodeTail *old_head = list->head;
    if (out) {
        *out = old_head->data;
    }
    
    list->head = old_head->next;
    
    // Si la liste devient vide, mettre tail à NULL aussi
    if (list->head == NULL) {
        list->tail = NULL;
    }
    
    free(old_head);
    return 1; // Succès
}

// Supprimer le dernier élément
// Complexité: O(n) car on doit trouver l'avant-dernier nœud
int ds_slist_tail_remove_tail(SListTail *list, int *out) {
    if (ds_slist_tail_is_empty(list)) {
        return 0; // Liste vide
    }
    
    // Cas spécial: un seul élément
    if (list->head == list->tail) {
        if (out) {
            *out = list->head->data;
        }
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return 1;
    }
    
    // Parcourir jusqu'à l'avant-dernier nœud
    SNodeTail *cur = list->head;
    while (cur->next != list->tail) {
        cur = cur->next;
    }
    
    // cur pointe maintenant vers l'avant-dernier nœud
    if (out) {
        *out = list->tail->data;
    }
    free(list->tail);
    list->tail = cur;
    list->tail->next = NULL;
    
    return 1; // Succès
}

// Afficher la liste
// Complexité: O(n)
void ds_slist_tail_print(const SListTail *list) {
    const SNodeTail *cur = list->head;
    printf("[");
    while (cur) {
        printf("%d", cur->data);
        if (cur->next != NULL) {
            printf(" --> ");
        }
        cur = cur->next;
    }
    printf("]\n");
}

// Vider complètement la liste
// Complexité: O(n)
void ds_slist_tail_clear(SListTail *list) {
    SNodeTail *cur = list->head;
    while (cur != NULL) {
        SNodeTail *next = cur->next;
        free(cur);
        cur = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

// Trouver un nœud avec une valeur donnée
// Complexité: O(n) dans le pire cas
SNodeTail *ds_slist_tail_find(const SListTail *list, int value) {
    SNodeTail *cur = list->head;
    while (cur != NULL) {
        if (cur->data == value) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL; // Non trouvé
}

