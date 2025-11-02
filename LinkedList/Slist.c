//
// Created by minhm on 11/10/2025.
//

#include "Slist.h"

#include <stdio.h>
#include <stdlib.h>

//int ds_slist_insert_at(SList *plist, int index, int value) CHECK !!!!!



// Session 11-10-25
// Function to create a new node for a singly linked list
SNode *ds_slit_create_node(int data) { // 1
    // Allocate memory for a new SNode on heap
    // malloc(sizeof(SNode)) requests memory for ENTIRE struct (data + next fields)
    // Returns void* pointer to allocated memory block
    SNode *pnode = (SNode *)malloc(sizeof(SNode)); // Cast void* to SNode*
                                                    // pnode now stores address of allocated memory
                                                    // *pnode would give us the ENTIRE struct at that address
    
    // Access and set individual fields using -> operator
    pnode->data = data; // Set the data field of the new node to the given value
                        // Equivalent to: (*pnode).data = data
    
    pnode->next = NULL; // Initialize the next pointer to NULL since this node
                        // is not linked to any other node yet
                        // Equivalent to: (*pnode).next = NULL
    
    return pnode; // Return the pointer (address) to the newly created node
                  // Caller can use this pointer to access the node via -> operator
}


void ds_slist_init(SList* plist) { //2
    // plist is a pointer to SList → contains address of an SList struct
    // *plist would dereference to get the ENTIRE SList struct (which contains head field)
    
    plist->head = NULL; // Access the 'head' field of SList using -> operator
                        // Equivalent to: (*plist).head = NULL
                        // This sets the head field of the SList to NULL (empty list)
                        // plist points to the struct, -> accesses its head field
}
SList ds_slist_create() { //3
    SList list;
    list.head = NULL;
    return list;
}
int ds_slist_is_empty(const SList *plist) {//4
    return plist->head == NULL;
}

// int ds_slist_is_empty(SList list) {
//     return list->head == NULL;
// }


int ds_slist_insert_head(SList *plist, int value) {
    SNode *new_node = ds_slit_create_node(value); //1
    new_node->next = plist->head;
    plist->head = new_node;
}

int ds_slist_insert_tail(SList *plist, int value) {
    SNode *new_node = ds_slit_create_node(value);
    // j;aurais du retourner
    if (ds_slist_is_empty(plist)) {
        plist->head = new_node;
    }
    else {
        SNode *cur = plist->head;
        while (cur->next != NULL) { // til there is no next then End so cur is tail
            cur = cur->next;
        }
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

//session 17/10
SNode* ds_slist_find(const SList *plist, int value) { //why we need to use plist instead of list which is initialized in header
    // function declaration which return an instance of SNode
    // * function declaration which return a pointer to an instance of SNode
    SNode *res = NULL;
    SNode *cur = plist->head;
    while (cur && res == NULL) {
        if (cur->data == value) {
            res = cur;
        }
        cur = cur->next; // ??
    }
    return res;
}

SNode *ds_slist_first_rec_fronode(const SNode *start,int value) {
    if (start == NULL) return NULL;
    if (start->data ==value) return start;
    return ds_slist_first_rec_fronode(start->next,value);
}

int ds_slist_insert_at(SList *plist, int index, int value) {
    int ok = 0;
    if (index == 0) {
        // Insert at the beginning of the list
        ok = ds_slist_insert_head(plist, value);
    }
    else if (index > 0 && !ds_slist_is_empty(plist)) {
        // Start from the head node
        SNode *cur = plist->head;
        // CHECK DEBUG !!!!!! 17/10
        printf(cur->next);
        int i = 0;
        // Move to the node at position (index - 1)
        // We need to stop at the node before the insertion point
        while (cur && i < index - 1) {
            cur = cur->next; // Move to the next node in each iteration
            i++;
        }
        // If we found a valid position to insert
        if (cur) {
            SNode *pnew = ds_slit_create_node(value);
            // Link the new node to the node that was at the target position
            pnew->next = cur->next;
            // Link the previous node to the new node
            cur->next = pnew;
            ok = 1;
        }
    }
    return ok;
}