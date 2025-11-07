#include "Btree.h"
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

//session 17/10
#include <stdlib.h>  /* malloc, free */

// Initialize an empty binary tree
// Time complexity: O(1)
void ds_btree_init(BTree* tree) {
    tree->root = 0;
}

// Create a new tree node with given value
// Allocates memory on heap and initializes node
// Returns pointer to new node, or NULL if allocation fails
// Time complexity: O(1)
TNode* ds_btree_create_node(int value) {
    TNode* n = (TNode*)malloc(sizeof(TNode)); // Allocate memory for entire TNode struct
    if (!n) return NULL; // Return NULL if malloc fails
    
    // Initialize node fields
    n->data = value;  // Set node data
    n->left = NULL;   // Initialize left child pointer to NULL
    n->right = NULL;  // Initialize right child pointer to NULL
    return n;         // Return pointer to newly created node
}

// Attach a child node to the left of parent node
// Returns 1 if successful, 0 if parent is NULL or left child already exists
// Time complexity: O(1), no overwrite protection
int ds_btree_attach_left(TNode* parent, TNode* child) {
    if (!parent || parent->left) return 0; // Fail if parent is NULL or left already exists
    parent->left = child; // Attach child to left
    return 1; // Success
}

// Attach a child node to the right of parent node
// Returns 1 if successful, 0 if parent is NULL or right child already exists
// Time complexity: O(1), no overwrite protection
int ds_btree_attach_right(TNode* parent, TNode* child) {
    if (!parent || parent->right) return 0; // Fail if parent is NULL or right already exists
    parent->right = child; // Attach child to right
    return 1; // Success
}

// Check if tree is empty
// Returns 1 if empty (root is NULL), 0 otherwise
// Time complexity: O(1)
int ds_btree_is_empty(const BTree* tree) {
    return tree->root == 0;
}



//session 7/11/25


// Calculate the size (number of nodes) in the tree/subtree
// Time complexity: O(n) where n is number of nodes
int ds_btree_size(TNode* node) {
    if (!node) return 0; // Base case: empty tree has size 0
    // Recursive case: current node (1) + size of left subtree + size of right subtree
    return 1 + ds_btree_size(node->left) + ds_btree_size(node->right);
}

// Display tree in preorder traversal (Root -> Left -> Right)
// Prints node data directly to stdout
void ds_btree_preorder_display(const TNode* pnode) {
    if (pnode != NULL) {
        printf("%d ", pnode->data);              // Visit root first
        ds_btree_preorder_display(pnode->left);  // Then traverse left subtree
        ds_btree_preorder_display(pnode->right); // Finally traverse right subtree
    }
}

// Preorder traversal with callback function (Root -> Left -> Right)
// Allows custom visit function instead of just printing
void ds_btree_preorder(const TNode* pnode, ds_visit_fn visit) {
    if (pnode != NULL) {
        visit(pnode->data);                      // Visit root first
        ds_btree_preorder(pnode->left, visit);   // Then traverse left subtree
        ds_btree_preorder(pnode->right, visit); // Finally traverse right subtree
    }
}

// Inorder traversal with callback function (Left -> Root -> Right)
// For BST, this visits nodes in sorted order
void ds_btree_inorder(const TNode* pnode, ds_visit_fn visit) {
    if (pnode != NULL) {
        ds_btree_inorder(pnode->left, visit);    // First traverse left subtree
        visit(pnode->data);                      // Then visit root
        ds_btree_inorder(pnode->right, visit);   // Finally traverse right subtree
    }
}

// Postorder traversal with callback function (Left -> Right -> Root)
// Useful for deleting tree (children before parent)
void ds_btree_postorder(const TNode* pnode, ds_visit_fn visit) {
    if (pnode != NULL) {
        ds_btree_postorder(pnode->left, visit);  // First traverse left subtree
        ds_btree_postorder(pnode->right, visit); // Then traverse right subtree
        visit(pnode->data);                      // Finally visit root
    }
}
// Calculate the height of the tree/subtree
// Height: number of edges from root to deepest leaf
// Empty tree has height -1, single node has height 0
int ds_btree_height(TNode* pnode) {
    if (pnode == NULL) return -1; // Base case: empty tree has height -1
    int hl = ds_btree_height(pnode->left);  // Height of left subtree
    int hr = ds_btree_height(pnode->right); // Height of right subtree
    return ((hl > hr) ? hl : hr) + 1;       // Return max height + 1 (current level)
}

// Helper function to free a single node
// Used as callback in ds_btree_clear
static void free_node(TNode* node) {
    if (node) free(node); // Free the node if it's not NULL
}

// Clear all nodes in the tree (free memory)
// Uses postorder traversal to free children before parent
void ds_btree_clear(BTree* tree) {
    if (tree && tree->root) {
        ds_btree_postorder_node(tree->root, free_node); // Traverse and free all nodes
        tree->root = NULL; // Set root to NULL after clearing
    }
}

// Find a node with the given value in the tree/subtree
// Returns pointer to node if found, NULL otherwise
TNode* ds_btree_find(TNode* pnode, int val) {
    if (pnode == NULL) return NULL; // Base case: not found
    if (pnode->data == val) return pnode; // Found!
    
    // Search in left subtree
    TNode* left_result = ds_btree_find(pnode->left, val);
    if (left_result) return left_result;
    
    // Search in right subtree
    return ds_btree_find(pnode->right, val);
}

// Find the depth of a node with the given value
// Depth: number of edges from root to target node
// Returns depth if found, -1 if not found
int ds_btree_depth_of(TNode* pnode, int val) {
    if (pnode == NULL) return -1; // Base case: not found
    if (pnode->data == val) return 0; // Found at current level (depth 0)
    
    // Search in left subtree
    int left_depth = ds_btree_depth_of(pnode->left, val);
    if (left_depth >= 0) return left_depth + 1; // Found in left subtree
    
    // Search in right subtree
    int right_depth = ds_btree_depth_of(pnode->right, val);
    if (right_depth >= 0) return right_depth + 1; // Found in right subtree
    
    return -1; // Not found
}

// Preorder traversal visiting entire nodes (Root -> Left -> Right)
// visit function receives the entire node pointer, not just data
void ds_btree_preorder_node(const TNode* pnode, ds_visit_node_fn visit) {
    if (pnode != NULL) {
        visit(pnode);                                    // Visit root first
        ds_btree_preorder_node(pnode->left, visit);     // Then traverse left subtree
        ds_btree_preorder_node(pnode->right, visit);    // Finally traverse right subtree
    }
}

// Inorder traversal visiting entire nodes (Left -> Root -> Right)
// visit function receives the entire node pointer, not just data
void ds_btree_inorder_node(const TNode* pnode, ds_visit_node_fn visit) {
    if (pnode != NULL) {
        ds_btree_inorder_node(pnode->left, visit);      // First traverse left subtree
        visit(pnode);                                    // Then visit root
        ds_btree_inorder_node(pnode->right, visit);     // Finally traverse right subtree
    }
}

// Postorder traversal visiting entire nodes (Left -> Right -> Root)
// visit function receives the entire node pointer, not just data
// Useful for operations that need children processed before parent (e.g., freeing memory)
void ds_btree_postorder_node(const TNode* pnode, ds_visit_node_fn visit) {
    if (pnode != NULL) {
        ds_btree_postorder_node(pnode->left, visit);    // First traverse left subtree
        ds_btree_postorder_node(pnode->right, visit);    // Then traverse right subtree
        visit(pnode);                                    // Finally visit root
    }
}

void ds_btree_level_order(TNode* pnode, ds_visit_fn visit) {
    if (pnode != NULL&& visit != NULL) {
        Queue q;
        queue_init(&q);
        queue_enqueue(&q, pnode);
        while (! queue_is_empty(&q)) {
            TNode* cur;
            queue_dequeue(&q, &cur);
            visit(cur->data);
            if (cur->left != NULL) queue_enqueue(&q, cur->left);
            if (cur->right != NULL) queue_enqueue(&q, cur->right);
        }

    }
}
void ds_bsttree_add(BTree* tree, int value) {

    if (ds_btree_is_empty(tree)) {
        tree->root = ds_btree_create_node(value);;
    }
    else {
        TNode* cur = tree->root;
        if (value < cur->data) {
            if (cur->left == NULL) cur->left = ds_btree_create_node(value);
            else ds_bsttree_add(tree,value);
        }
        else {
            if (cur->right == NULL) cur->right = ds_btree_create_node(value);
            else ds_bsttree_add(tree,value);
        }
    }
}

void ds_bsttree_add_to_node(TNode* cur, int value) {

    if (cur){
        if (value < cur->data) {
            if (cur->left == NULL) cur->left = ds_btree_create_node_to_node(value);
            else ds_bsttree_add(tree,value);
        }
        else {
            if (cur->right == NULL) cur->right = ds_btree_create_node_to_node(value);
            else ds_bsttree_add(tree,value);
        }
    }
}






