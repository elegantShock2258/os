#include "./AvlTree.h"

int getHeight(Node *n) {
  if (n == NULL)
    return 0;
  return *(n->height);
}
// return >0 if a>b else <0
int _AVL_comparitor(void *a, void *b);

Node *createNode(void *newNode, u32 *height) {
  Node *node = (Node *)kmalloc(sizeof(Node));
  node->key = newNode;
  node->left = NULL;
  node->right = NULL;
  *height = 1;
  (node->height) = height;
  return node;
}

int getBalanceFactor(Node *n) {
  if (n == NULL)
    return 0;
  return getHeight(n->left) - getHeight(n->right);
}

Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  *y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
  *x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

  return x;
}

Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  *x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
  *y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

  return y;
}

Node *insert(Node *node, void *key, u32 *height) {
  if (node == NULL)
    return createNode(key, height);
  printf("inserting %d\n", *height);
  if (_AVL_comparitor(key, node->key) < 0)
    node->left = insert(node->left, key, height);
  else if (_AVL_comparitor(key, node->key) > 0)
    node->right = insert(node->right, key, height);
  else
    return node;

  *node->height = 1 + max(getHeight(node->left), getHeight(node->right));

  int balance = getBalanceFactor(node);

  if (balance > 1 && _AVL_comparitor(key, node->left->key) < 0)
    return rightRotate(node);

  if (balance < -1 && _AVL_comparitor(key, node->right->key) > 0)
    return leftRotate(node);

  if (balance > 1 && _AVL_comparitor(key, node->left->key) > 0) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && _AVL_comparitor(key, node->right->key) < 0) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}
