//
// Implémentation de la liste simplement chainée avec head uniquement
//

#include "Slist.h"
#include <stdio.h>
#include <stdlib.h>

// Créer un nouveau nœud pour une liste simplement chainée
// Complexité: O(1)
SNode *ds_slit_create_node(int data) {
    // Allouer de la mémoire sur le tas (heap) pour un nouveau SNode
    SNode *pnode = (SNode *)malloc(sizeof(SNode));
    if (!pnode) return NULL; // Échec d'allocation mémoire
    
    pnode->data = data;  // Définir la donnée du nouveau nœud
    pnode->next = NULL;  // Initialiser le pointeur next à NULL (pas encore lié)
    return pnode;        // Retourner le pointeur vers le nouveau nœud
}


// Initialiser une liste vide (passer par pointeur)
// Complexité: O(1)
void ds_slist_init(SList* plist) {
    // plist est un pointeur vers SList, on utilise -> pour accéder au champ head
    plist->head = NULL;
}

// Créer une nouvelle liste vide (retourner par valeur)
// Complexité: O(1)
// Différence avec ds_slist_init: cette fonction retourne une liste, l'autre modifie une liste existante
SList ds_slist_create() {
    SList list;
    list.head = NULL;
    return list;
}

// Vérifier si la liste est vide
// Complexité: O(1)
int ds_slist_is_empty(const SList *plist) {
    return plist->head == NULL;
}


// Insérer un élément en tête de liste
// Complexité: O(1)
int ds_slist_insert_head(SList *plist, int value) {
    SNode *new_node = ds_slit_create_node(value);
    if (!new_node) return 0; // Échec d'allocation mémoire
    
    new_node->next = plist->head;  // Le nouveau nœud pointe vers l'ancienne tête
    plist->head = new_node;        // Mettre à jour la tête de la liste
    return 1; // Succès
}

// Insérer un élément en queue de liste
// Complexité: O(n) car on doit parcourir jusqu'à la fin
int ds_slist_insert_tail(SList *plist, int value) {
    SNode *new_node = ds_slit_create_node(value);
    if (!new_node) return 0; // Échec d'allocation mémoire
    
    if (ds_slist_is_empty(plist)) {
        // Liste vide: le nouveau nœud devient la tête
        plist->head = new_node;
    } else {
        // Parcourir jusqu'au dernier nœud (celui dont next est NULL)
        SNode *cur = plist->head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        // cur pointe maintenant vers le dernier nœud
        cur->next = new_node;
    }
    return 1;
}

void ds_slist_print(const SList *plist) {
    const SNode *cur = plist->head;
    printf("[");
    while (cur) {
        printf("%d, ", cur->data);
        if (cur->next != NULL) printf(" --> ");
        cur = cur->next;
    }
    printf("]\n");
}

void ds_slist_print_recursive(const SNode *pnode) {
    if (pnode) {
        printf("%d ",pnode->data);
        if (pnode->next != NULL) printf(" --> ");
        ds_slist_print_recursive(pnode->next);
    }
}
void ds_slist_print_v1(const SList *plist) {
    printf("[");
    ds_slist_print_recursive(plist->head);
    printf("]\n");
}

// Trouver un nœud avec une valeur donnée
// Complexité: O(n) dans le pire cas
SNode* ds_slist_find(const SList *plist, int value) {
    SNode *cur = plist->head;
    while (cur != NULL) {
        if (cur->data == value) {
            return cur; // Trouvé!
        }
        cur = cur->next;
    }
    return NULL; // Non trouvé
}

// Trouver récursivement un nœud avec une valeur donnée à partir d'un nœud
// Complexité: O(n) dans le pire cas
SNode *ds_slist_first_rec_fronode(const SNode *start, int value) {
    if (start == NULL) return NULL; // Fin de liste
    if (start->data == value) return (SNode*)start; // Trouvé!
    return ds_slist_first_rec_fronode(start->next, value); // Continuer la recherche
}

// Insérer un élément à un index donné
// Complexité: O(n) dans le pire cas
int ds_slist_insert_at(SList *plist, int index, int value) {
    if (index == 0) {
        // Insérer au début de la liste
        return ds_slist_insert_head(plist, value);
    }
    
    if (index > 0 && !ds_slist_is_empty(plist)) {
        // Commencer depuis la tête
        SNode *cur = plist->head;
        int i = 0;
        // Se déplacer jusqu'au nœud à la position (index - 1)
        // On doit s'arrêter au nœud avant le point d'insertion
        while (cur != NULL && i < index - 1) {
            cur = cur->next;
            i++;
        }
        // Si on a trouvé une position valide pour insérer
        if (cur != NULL) {
            SNode *pnew = ds_slit_create_node(value);
            if (!pnew) return 0; // Échec d'allocation
            
            // Lier le nouveau nœud au nœud qui était à la position cible
            pnew->next = cur->next;
            // Lier le nœud précédent au nouveau nœud
            cur->next = pnew;
            return 1; // Succès
        }
    }
    return 0; // Index invalide
}

// Supprimer le premier nœud de la liste et retourner sa valeur
// Complexité temporelle: O(1)
// Retourne 1 si succès, 0 si la liste est vide
int ds_slist_remove_head(SList *list, int *out) {
    if (ds_slist_is_empty(list)) {
        return 0; // Liste vide, rien à supprimer
    }
    
    SNode *old_head = list->head;
    if (out) {
        *out = old_head->data; // Sauvegarder la valeur avant suppression
    }
    list->head = old_head->next; // Mettre à jour la tête
    free(old_head); // Libérer la mémoire
    return 1; // Succès
}

// Supprimer le dernier nœud de la liste et retourner sa valeur
// Complexité temporelle: O(n) car on doit parcourir jusqu'à la fin
// Retourne 1 si succès, 0 si la liste est vide
int ds_slist_remove_tail(SList *list, int *out) {
    if (ds_slist_is_empty(list)) {
        return 0; // Liste vide
    }
    
    // Cas spécial: un seul élément
    if (list->head->next == NULL) {
        if (out) {
            *out = list->head->data;
        }
        free(list->head);
        list->head = NULL;
        return 1;
    }
    
    // Parcourir jusqu'à l'avant-dernier nœud
    SNode *cur = list->head;
    while (cur->next->next != NULL) {
        cur = cur->next;
    }
    
    // cur pointe maintenant vers l'avant-dernier nœud
    if (out) {
        *out = cur->next->data;
    }
    free(cur->next); // Libérer le dernier nœud
    cur->next = NULL; // Mettre à jour le pointeur
    return 1;
}

// Supprimer la première occurrence d'une valeur dans la liste
// Complexité temporelle: O(n) dans le pire cas
// Retourne 1 si la valeur a été trouvée et supprimée, 0 sinon
int ds_slist_remove_value(SList *list, int value) {
    if (ds_slist_is_empty(list)) {
        return 0; // Liste vide
    }
    
    // Cas spécial: la valeur est dans la tête
    if (list->head->data == value) {
        SNode *old_head = list->head;
        list->head = old_head->next;
        free(old_head);
        return 1;
    }
    
    // Chercher le nœud précédent celui contenant la valeur
    SNode *cur = list->head;
    while (cur->next != NULL && cur->next->data != value) {
        cur = cur->next;
    }
    
    // Si on a trouvé la valeur
    if (cur->next != NULL) {
        SNode *to_remove = cur->next;
        cur->next = to_remove->next;
        free(to_remove);
        return 1;
    }
    
    return 0; // Valeur non trouvée
}

// Vider complètement la liste (libérer toute la mémoire)
// Complexité temporelle: O(n) où n est le nombre de nœuds
void ds_slist_clear(SList *list) {
    SNode *cur = list->head;
    while (cur != NULL) {
        SNode *next = cur->next; // Sauvegarder le prochain avant de libérer
        free(cur);
        cur = next;
    }
    list->head = NULL; // Réinitialiser la tête
}