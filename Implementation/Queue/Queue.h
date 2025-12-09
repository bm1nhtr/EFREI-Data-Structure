//
// File (Queue) - Structure FIFO (First In First Out)
// Implémentée avec une liste simplement chainée avec head et tail
// Utilisée pour le parcours en largeur (BFS) des arbres
//

#ifndef LINKEDLIST_QUEUE_H
#define LINKEDLIST_QUEUE_H

#include "../Trees/Btree/Btree.h"
#include "../Lists/Slist/Slist.h"

// Structure d'un nœud de la file
// Contient un pointeur vers un nœud d'arbre (TNode) et un pointeur vers le nœud suivant
typedef struct QNode {
    const TNode *tnode;  // Pointeur vers un nœud d'arbre (const car on ne modifie pas le nœud)
    struct QNode *next;  // Pointeur vers le nœud suivant dans la file
} QNode;

// Structure de la file
// Contient un pointeur vers la tête (premier élément) et la queue (dernier élément)
typedef struct Queue {
    QNode *head;  // Pointeur vers le premier élément (sortie)
    QNode *tail;  // Pointeur vers le dernier élément (entrée)
} Queue;

// Initialiser une file vide
void queue_init(Queue *q);

// Vérifier si la file est vide
int queue_is_empty(const Queue *q);

// Enfiler (enqueue) un élément en queue - O(1)
int queue_enqueue(Queue *q, TNode *tnode);

// Défiler (dequeue) un élément de la tête - O(1)
int queue_dequeue(Queue *q, TNode **out);

// Vider complètement la file - O(n)
void queue_clear(Queue *q);



















#endif //LINKEDLIST_QUEUE_H