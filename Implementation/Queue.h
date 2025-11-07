//
// Created by minhm on 07/11/2025.
//

#ifndef LINKEDLIST_QUEUE_H
#define LINKEDLIST_QUEUE_H


#include "Btree.h"
#include "Slist.h"


//session 7/11/25
typedef struct QNode {const TNode *tnode;struct QNode *next;}QNode;
typedef struct Queue {QNode *head;QNode *tail;}Queue;

//todo list
void queue_init(Queue*q);
int queue_is_empty(const Queue*q);
int queue_enqueue(Queue*q, TNode *tnode);
int queue_dequeue(Queue*q, TNode**out);
void queue_clear(Queue*q);



















#endif //LINKEDLIST_QUEUE_H