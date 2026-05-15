# AvlTree.c

## Description
Implementation of a generic, self-balancing AVL Tree. Used by the window manager to maintain the Z-order of windows.

## Imports
- [[AvlTree.h.md]]

## Functions
- `int getHeight(Node *n)`
- `Node *createNode(void *newNode, u32 *height)`
- `int getBalanceFactor(Node *n)`
- `Node *rightRotate(Node *y)`
- `Node *leftRotate(Node *x)`
- `Node *insert(Node *node, void *key, u32 *height)`: Inserts a node and balances the tree.
