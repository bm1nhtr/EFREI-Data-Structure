//
// Liste simplement chainée avec head et tail
// Cette structure maintient un pointeur vers la tête ET la queue pour des opérations O(1) en queue
//

#ifndef LINKEDLIST_SLIST_TAIL_H
#define LINKEDLIST_SLIST_TAIL_H

// Structure d'un nœud (identique à Slist.h)
typedef struct SNodeTail {
    int data;
    struct SNodeTail *next;
} SNodeTail;

// Structure de la liste avec head et tail
typedef struct SListTail {
    SNodeTail *head;  // Pointeur vers le premier nœud
    SNodeTail *tail;  // Pointeur vers le dernier nœud
} SListTail;

// Initialisation d'une liste vide
void ds_slist_tail_init(SListTail *list);

// Création d'une nouvelle liste vide
SListTail ds_slist_tail_create(void);

// Vérifier si la liste est vide
int ds_slist_tail_is_empty(const SListTail *list);

// Créer un nouveau nœud
SNodeTail *ds_slist_tail_create_node(int data);

// Insérer un élément en tête - O(1)
int ds_slist_tail_insert_head(SListTail *list, int value);

// Insérer un élément en queue - O(1) grâce au pointeur tail
int ds_slist_tail_insert_tail(SListTail *list, int value);

// Supprimer le premier élément - O(1)
int ds_slist_tail_remove_head(SListTail *list, int *out);

// Supprimer le dernier élément - O(n) car on doit trouver l'avant-dernier
int ds_slist_tail_remove_tail(SListTail *list, int *out);

// Afficher la liste
void ds_slist_tail_print(const SListTail *list);

// Vider la liste
void ds_slist_tail_clear(SListTail *list);

// Trouver un nœud avec une valeur donnée
SNodeTail *ds_slist_tail_find(const SListTail *list, int value);

#endif //LINKEDLIST_SLIST_TAIL_H

