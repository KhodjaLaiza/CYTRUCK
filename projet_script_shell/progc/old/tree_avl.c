#include <stdio.h>
#include <stdlib.h>

#include <tree_avl.h>

// Calculate height
int height(struct Node *N) 
{
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) 
{
  return (a > b) ? a : b;
}

int min(int a, int b) 
{
  return (a < b) ? a : b;
}

// Create a node
struct Node *newNode(int key) 
{
  struct Node *node = (struct Node *)
    malloc(sizeof(struct Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Right rotate
struct Node *rightRotate(struct Node *y) 
{
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Left rotate
struct Node *leftRotate(struct Node *x) 
{
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(struct Node *N) 
{
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Insert node
struct Node *insertNode(struct Node *node, int key) 
{
  // Find the correct position to insertNode the node and insertNode it
  if (node == NULL)
    return (newNode(key));

  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  if (balance > 1 && key > node->left->key) 
  {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key) 
  {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

struct Node *minValueNode(struct Node *node) 
{
  struct Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

// Delete a nodes
struct Node *deleteNode(struct Node *root, int key) 
{
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);

  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else 
  {
    if ((root->left == NULL) || (root->right == NULL)) 
    {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) 
      {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } 
    else 
    {
      struct Node *temp = minValueNode(root->right);

      root->key = temp->key;

      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) 
  {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) 
  {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

// Avoir le nombre d'éléments de l'arbre AVL
int getSize(struct Node *root)
{
  if (root == NULL)
  {
    return 0;
  }

  return 1 + getSize(root->left) + getSize(root->right);
}

void copyArrays(Array *a, Array *b, int start)
{
  int i;

  for (i=start; i<=start+b->size-1; i++)
      a->tab[i] = b->tab[i-start];

  free(b->tab);
  free(b);
}

//***********************************************************************
//Trois parcours standard (de gauche vers la droite) en profondeur 
//***********************************************************************

// Get the tree in Pre Order
Array* getPreOrder(struct Node *root, int size) 
{
  int n = getSize(root);
  if (size > 0)
  {
    n = min(n, size);
  }

  Array *array = (Array*)malloc( sizeof(Array) );

  array->tab = (void*)malloc( n * sizeof(void*));
  array->size = n;

  if (root != NULL) 
  {
    array->tab[0] = &root->key;

    Array *aL = getPreOrder(root->left, size-1);
    int sizeL = aL->size;

    copyArrays(array, aL, 1);

    if ( (sizeL+1 < size) || (size<=0) )
    {
      Array *aR = getPreOrder(root->right, size-1-sizeL);
      copyArrays(array, aR, 1+sizeL);
    }
  }

  return array;
}

// Get the tree in Post Order
Array getPostOrder(struct Node *root, int size) 
{
  if (root != NULL) 
  {
    getPostOrder(root->left, size);
    getPostOrder(root->right, size);
    printf("%d ", root->key);
  }
}

// Get the tree in In Order
Array getInOrder(struct Node *root, int size) 
{
  if (root != NULL) 
  {
    getInOrder(root->left, size);
    printf("%d ", root->key);
    getInOrder(root->right, size);
  }
}

//***********************************************************************
//Trois parcours non-standard (de droite vers la gauche) en profondeur 
//***********************************************************************

// Get the tree in Pre Order
Array getPreOrderR2L(struct Node *root, int size) 
{
  if (root != NULL) 
  {
    printf("%d ", root->key);
    getPreOrderR2L(root->right, size);
    getPreOrderR2L(root->left, size);
  }
}

// Get the tree in Post Order
Array getPostOrderR2L(struct Node *root, int size) 
{
  if (root != NULL) 
  {
    getPostOrderR2L(root->right, size);
    getPostOrderR2L(root->left, size);
    printf("%d ", root->key);
  }
}

// Get the tree in In Order
Array getInOrderR2L(struct Node *root, int size) 
{
  if (root != NULL) 
  {
    getInOrderR2L(root->right, size);
    printf("%d ", root->key);
    getInOrderR2L(root->left, size);
  }
}

//***********************************************************************************
//Affichage avec Trois parcours standard (de gauche vers la droite) en profondeur 
//***********************************************************************************

// Print the tree in Pre Order
void printPreOrder(struct Node *root)
{
  if (root != NULL) 
  {
    printf("%d ", root->key);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

// Print the tree in Post Order
void printPostOrder(struct Node *root)
{
  if (root != NULL) 
  {
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->key);
  }
}

// Print the tree in In Order
void printInOrder(struct Node *root)
{
  if (root != NULL) 
  {
    printInOrder(root->left);
    printf("%d ", root->key);
    printInOrder(root->right);
  }
}


//***********************************************************************************
//Affichage avec Trois parcours non-standard (de droite vers la gauche) en profondeur
//*********************************************************************************** 

// Print the tree in Pre Order
void printPreOrderR2L(struct Node *root)
{
  if (root != NULL) 
  {
    printf("%d ", root->key);
    printPreOrderR2L(root->right);
    printPreOrderR2L(root->left);
  }
}

// Print the tree in Post Order
void printPostOrderR2L(struct Node *root)
{
  if (root != NULL) 
  {
    printPostOrderR2L(root->right);
    printPostOrderR2L(root->left);
    printf("%d ", root->key);
  }
}

// Print the tree in In Order
void printInOrderR2L(struct Node *root)
{
  if (root != NULL) 
  {
    printInOrderR2L(root->right);
    printf("%d ", root->key);
    printInOrderR2L(root->left);
  }
}