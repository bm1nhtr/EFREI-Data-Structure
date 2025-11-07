//
// Created by minhm on 11/10/2025.
//

#ifndef LINKEDLIST_SLIST_H
#define LINKEDLIST_SLIST_H


typedef struct SNode { int data; struct SNode *next; } SNode; // Snode pointer Snode
// struct SNode :  define a structure which is called SNode
// it has 2 elements: int data  and struct SNode *next (which is a pointer to an another SNode)
// typedef structure .... {} allias (typedef create an alias for the structure now called SNode)
typedef struct SList { SNode *head; } SList; 
// struct SList :  define a structure which is called SList
// it has 1 element: SNode *head (which is a pointer to the head of the list)

SNode *ds_slit_create_node(int data); // function declaration which return an instance of SNode
                                      // * function declaration which return a pointer to an instance of SNode

// Session 11-10-25
void ds_slist_init(SList *);
SList ds_slist_create();

int ds_slist_is_empty(const SList *plist);
int ds_slist_insert_head(SList *plist, int value);
int ds_slist_insert_tail(SList *plist, int value); /* O(n) en head-only */

void ds_slist_print(const SList *plist);
void ds_slist_print_recursive(const SNode *pnode);
void ds_slist_print_v1(const SList *plist);

int ds_slist_remove_head(SList *list, int *out);
int ds_slist_remove_tail(SList *list, int *out); /* O(n) */
int ds_slist_remove_value(SList *list, int value);
void ds_slist_clear(SList *list);
// session 17/10
SNode* ds_slist_find(const SList *list, int value); // function declaration which return an instance of SNode
                                                     // * function declaration which return a pointer to an instance of SNode
SNode *ds_slist_first_rec_fronode(const SNode *start,int value);
int ds_slist_insert_at(SList *list, int index, int value);



#endif //LINKEDLIST_SLIST_H