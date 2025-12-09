//
// Implémentation de la file (Queue)
//

#include "Queue.h"
#include <stdlib.h>

// Initialiser une file vide
// Complexité: O(1)
void queue_init(Queue *q) {
    q->head = NULL;
    q->tail = NULL;
}

// Vérifier si la file est vide
// Complexité: O(1)
// Note: on vérifie head car si head est NULL, la file est vide (même si tail pourrait être NULL aussi)
int queue_is_empty(const Queue *q) {
    return q->head == NULL;
}

// Enfiler (enqueue) un élément en queue de la file
// Complexité: O(1) grâce au pointeur tail
int queue_enqueue(Queue *q, TNode *tnode) {
    QNode *nouv = (QNode *)malloc(sizeof(QNode));
    if (!nouv) return 0; // Échec d'allocation mémoire
    
    nouv->tnode = tnode;
    nouv->next = NULL;
    
    if (queue_is_empty(q)) {
        // File vide: head et tail pointent vers le nouveau nœud
        q->head = q->tail = nouv;
    } else {
        // Ajouter après la queue actuelle et mettre à jour tail
        q->tail->next = nouv;
        q->tail = nouv;
    }
    
    return 1; // Succès
}

// Défiler (dequeue) un élément de la tête de la file
// Complexité: O(1)
int queue_dequeue(Queue *q, TNode **out) {
    if (queue_is_empty(q)) {
        return 0; // File vide
    }
    
    QNode *h = q->head;
    if (out) {
        *out = (TNode*)h->tnode; // Retourner le nœud d'arbre
    }
    
    q->head = h->next;
    
    // Si la file devient vide, mettre tail à NULL aussi
    if (q->head == NULL) {
        q->tail = NULL;
    }
    
    free(h); // Libérer le nœud de la file
    return 1; // Succès
}
// Vider complètement la file
// Complexité: O(n) où n est le nombre d'éléments
void queue_clear(Queue*q) {
    if (q == NULL) return;
    
    // Dépiler tous les éléments jusqu'à ce que la file soit vide
    while (!queue_is_empty(q)) {
        TNode *dummy;
        queue_dequeue(q, &dummy);
        // Note: on ne libère pas les TNode car ils appartiennent à l'arbre
    }
}