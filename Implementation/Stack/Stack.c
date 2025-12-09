//
// Implémentation de la pile (Stack)
//

#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

// Initialiser une pile vide
// Complexité: O(1)
void ds_stack_init(Stack *stack) {
    stack->top = NULL;
    stack->size = 0;
}

// Créer une nouvelle pile vide
// Complexité: O(1)
Stack ds_stack_create(void) {
    Stack stack;
    stack.top = NULL;
    stack.size = 0;
    return stack;
}

// Vérifier si la pile est vide
// Complexité: O(1)
int ds_stack_is_empty(const Stack *stack) {
    return stack->top == NULL;
}

// Obtenir la taille de la pile
// Complexité: O(1) grâce au compteur, sinon O(n)
int ds_stack_size(const Stack *stack) {
    return stack->size;
}

// Empiler (push) un élément au sommet
// Complexité: O(1)
int ds_stack_push(Stack *stack, int value) {
    StackNode *new_node = (StackNode *)malloc(sizeof(StackNode));
    if (!new_node) return 0; // Échec d'allocation
    
    new_node->data = value;
    new_node->next = stack->top; // Le nouveau nœud pointe vers l'ancien sommet
    stack->top = new_node;        // Mettre à jour le sommet
    stack->size++;
    
    return 1; // Succès
}

// Dépiler (pop) un élément du sommet
// Complexité: O(1)
int ds_stack_pop(Stack *stack, int *out) {
    if (ds_stack_is_empty(stack)) {
        return 0; // Pile vide
    }
    
    StackNode *old_top = stack->top;
    if (out) {
        *out = old_top->data;
    }
    
    stack->top = old_top->next; // Mettre à jour le sommet
    stack->size--;
    free(old_top);
    
    return 1; // Succès
}

// Consulter (peek) l'élément au sommet sans le retirer
// Complexité: O(1)
int ds_stack_peek(const Stack *stack, int *out) {
    if (ds_stack_is_empty(stack)) {
        return 0; // Pile vide
    }
    
    if (out) {
        *out = stack->top->data;
    }
    
    return 1; // Succès
}

// Afficher la pile (du sommet vers le bas)
// Complexité: O(n)
void ds_stack_print(const Stack *stack) {
    if (ds_stack_is_empty(stack)) {
        printf("[] (pile vide)\n");
        return;
    }
    
    StackNode *cur = stack->top;
    printf("[");
    while (cur) {
        printf("%d", cur->data);
        if (cur->next != NULL) {
            printf(" | ");
        }
        cur = cur->next;
    }
    printf("] (top)\n");
}

// Vider la pile
// Complexité: O(n)
void ds_stack_clear(Stack *stack) {
    while (!ds_stack_is_empty(stack)) {
        int dummy;
        ds_stack_pop(stack, &dummy);
    }
    stack->size = 0;
}

