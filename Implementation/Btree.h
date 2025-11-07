#ifndef LINKEDLIST_BTREE_H
#define LINKEDLIST_BTREE_H


//session 17/10
typedef struct TNode {int data;struct TNode *left;struct TNode *right;} TNode;
typedef struct BTree{struct TNode *root;}BTree;

/* init — O(1) */
void ds_btree_init(BTree* tree);
/* create node — O(1) */
TNode* ds_btree_create_node(int value);

/* attach left/right — O(1), no overwrite */
int ds_btree_attach_left(TNode* parent, TNode* child);
int ds_btree_attach_right(TNode* parent, TNode* child);
/* is_empty — O(1) */
int ds_btree_is_empty(const BTree* tree);

int ds_btree_size(TNode* node);


//session 7/11/2025

// Function pointer types for tree traversal callbacks
typedef void(*ds_visit_fn)(int value);        // Callback function for visiting node data (int)
typedef void(*ds_visit_node_fn)(TNode* node); // Callback function for visiting entire node

// Tree operations
void ds_btree_clear(BTree* tree); // Clear all nodes in the tree

// Tree traversal functions
void ds_btree_preorder_display(const TNode* pnode); // Display tree in preorder (print to stdout)
void ds_btree_preorder(const TNode* pnode, ds_visit_fn visit); // Preorder traversal with callback
void ds_btree_inorder(const TNode* pnode, ds_visit_fn visit);  // Inorder traversal with callback
void ds_btree_postorder(const TNode* pnode, ds_visit_fn visit); // Postorder traversal with callback

// Node-based traversal functions (visit entire node, not just data)
void ds_btree_preorder_node(const TNode* pnode, ds_visit_node_fn visit);
void ds_btree_inorder_node(const TNode* pnode, ds_visit_node_fn visit);
void ds_btree_postorder_node(const TNode* pnode, ds_visit_node_fn visit);

// Tree utility functions
int ds_btree_height(TNode* pnode);        // Calculate height of tree/subtree
TNode* ds_btree_find(TNode* pnode, int val); // Find node with given value
int ds_btree_depth_of(TNode* pnode, int val); // Find depth of node with given value

void ds_btree_level_order(TNode* pnode, ds_visit_fn visit);
void ds_bsttree_add(BTree* tree, int value);
void ds_bsttree_add_to_node(TNode* cur, int value) ;







#endif //LINKEDLIST_BTREE_H