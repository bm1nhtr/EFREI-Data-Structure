//
// Liste simplement chainée avec head uniquement
// Chaque nœud pointe uniquement vers le nœud suivant
//

#ifndef LINKEDLIST_SLIST_H
#define LINKEDLIST_SLIST_H

// Structure d'un nœud de la liste simplement chainée
// Contient une donnée (int) et un pointeur vers le nœud suivant
typedef struct SNode {
    int data;                    // Donnée stockée dans le nœud
    struct SNode *next;          // Pointeur vers le nœud suivant (NULL si dernier)
} SNode;

// Structure de la liste simplement chainée
// Contient uniquement un pointeur vers la tête (premier nœud)
typedef struct SList {
    SNode *head;                 // Pointeur vers le premier nœud (NULL si liste vide)
} SList;

// Créer un nouveau nœud avec la valeur donnée
SNode *ds_slit_create_node(int data);

// Initialiser une liste vide (passer par pointeur)
void ds_slist_init(SList *plist);

// Créer une nouvelle liste vide (retourner par valeur)
SList ds_slist_create();

// Vérifier si la liste est vide
int ds_slist_is_empty(const SList *plist);

// Insérer un élément en tête de liste - O(1)
int ds_slist_insert_head(SList *plist, int value);

// Insérer un élément en queue de liste - O(n) car on doit parcourir jusqu'à la fin
int ds_slist_insert_tail(SList *plist, int value);

// Afficher la liste
void ds_slist_print(const SList *plist);

// Afficher récursivement à partir d'un nœud
void ds_slist_print_recursive(const SNode *pnode);

// Afficher la liste en utilisant la fonction récursive
void ds_slist_print_v1(const SList *plist);

// Supprimer le premier élément - O(1)
int ds_slist_remove_head(SList *list, int *out);

// Supprimer le dernier élément - O(n)
int ds_slist_remove_tail(SList *list, int *out);

// Supprimer la première occurrence d'une valeur - O(n)
int ds_slist_remove_value(SList *list, int value);

// Vider complètement la liste - O(n)
void ds_slist_clear(SList *list);

// Trouver un nœud avec une valeur donnée - O(n)
SNode* ds_slist_find(const SList *list, int value);

// Trouver récursivement un nœud avec une valeur donnée à partir d'un nœud
SNode *ds_slist_first_rec_fronode(const SNode *start, int value);

// Insérer un élément à un index donné - O(n)
int ds_slist_insert_at(SList *list, int index, int value);



#endif //LINKEDLIST_SLIST_H

