//
// Pile (Stack) - Structure LIFO (Last In First Out)
// Implémentée avec une liste simplement chainée
//

#ifndef LINKEDLIST_STACK_H
#define LINKEDLIST_STACK_H

// Structure d'un nœud pour la pile
typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

// Structure de la pile
typedef struct Stack {
    StackNode *top;  // Pointeur vers le sommet de la pile
    int size;        // Nombre d'éléments dans la pile (optionnel, pour O(1) size)
} Stack;

// Initialiser une pile vide
void ds_stack_init(Stack *stack);

// Créer une nouvelle pile vide
Stack ds_stack_create(void);

// Vérifier si la pile est vide
int ds_stack_is_empty(const Stack *stack);

// Obtenir la taille de la pile
int ds_stack_size(const Stack *stack);

// Empiler (push) un élément au sommet - O(1)
int ds_stack_push(Stack *stack, int value);

// Dépiler (pop) un élément du sommet - O(1)
int ds_stack_pop(Stack *stack, int *out);

// Consulter (peek) l'élément au sommet sans le retirer - O(1)
int ds_stack_peek(const Stack *stack, int *out);

// Afficher la pile
void ds_stack_print(const Stack *stack);

// Vider la pile
void ds_stack_clear(Stack *stack);

#endif //LINKEDLIST_STACK_H

