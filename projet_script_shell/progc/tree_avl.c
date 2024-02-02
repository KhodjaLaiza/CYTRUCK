#include <stdio.h>
#include <stdlib.h>

#include <tree_avl.h>

int avlKeyType = AVL_KEY_INT;

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

int isIntKey()
{
  return avlKeyType == AVL_KEY_INT;
}

int isFloatKey(){
  return avlKeyType == AVL_KEY_FLOAT;
}

int isDoubleKey(){
  return avlKeyType == AVL_KEY_DOUBLE;
}

void setKeyValueType(int type){
  avlKeyType = (type % 3);
}

double getKeyValue(struct Node *node)
{
  double value = -1;

  if (isIntKey())
  {
    value = (int)node->key;
  }
  else if (isFloatKey())
  {
    value = (float)node->key;
  }
  else if (isDoubleKey())
  {
    value = node->key;
  }

  return value;
}

void printNode(struct Node *node){
  if (isIntKey())
    printf("%d ", (int)(node->key));
  else if (isFloatKey())
    printf("%f ", (float)(node->key));
  else if (isDoubleKey())
    printf("%lf ", node->key);
}

/*
void printValue(void *value){
  if (isIntKey())
    printf( "%d ", (int) (*((double*)value)) );
  else if ( isFloatKey())
    printf( "%f ", (float)(*((double*)value)) );
  else if ( isDoubleKey())
    printf( "%lf ", (double) (*((double*)value)) );
}
*/

// Create a node
struct Node *newNodeInfo(double key, void *info)
{
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));

  node->key = key;
  node->info = info;
  

  node->left = NULL;
  node->right = NULL;
  node->height = 1;

  return (node);
}

struct Node *newNode(double key) 
{
  return newNodeInfo(key, NULL);
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
struct Node *insertNode(struct Node *node, double key) 
{
  return insertNodeInfo(node, key, NULL);
}

struct Node *insertNodeInfo(struct Node *node, double key, void *info)
{
  // Find the correct position to insertNode the node and insertNode it
  if (node == NULL)
    return (newNodeInfo(key, info));

  if (key < node->key)
    node->left = insertNodeInfo(node->left, key, info);
  else if (key > node->key)
    node->right = insertNodeInfo(node->right, key, info);
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
struct Node *deleteNode(struct Node *root, double key) 
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

// Get the tree in Pre Order (get values with limit : size)
Array* getPreOrder(struct Node *root, int size) 
{
  int n = getSize(root);

  Array *array = (Array*)malloc( sizeof(Array) );
  array->size = 0;

  if (n == 0){
    return array;
  }
  
  if (size > 0)
  {
    n = min(n, size);
  }

  array->size = n;
  array->tab = (void*)malloc( n * sizeof(void*));

  if (root != NULL) 
  {
    //Put the root in index=0
    //array->tab[0] = &(root->key);
    array->tab[0] = root;

    if (size != 1)
    {
      Array *aLeft = getPreOrder(root->left, size-1);
      int sizeLeft = aLeft->size;

      //Put the left side string from index=1
      copyArrays(array, aLeft, 1);

      if ( size<=0 || sizeLeft+1 < size )
      {
        Array *aRight = getPreOrder(root->right, size-1-sizeLeft);
        //Put the right side string from index=1+sizeLeft
        copyArrays(array, aRight, 1+sizeLeft);
      }
    }
  }

  return array;
}

// Get the tree in Post Order
Array* getPostOrder(struct Node *root, int size) 
{
  int n = getSize(root);

  Array *array = (Array*)malloc( sizeof(Array) );
  array->size = 0;

  if (n == 0){
    return array;
  }

  if (size > 0)
  {
    n = min(n, size);
  }

  array->size = n;
  array->tab = (void*)malloc( n * sizeof(void*));

  if (root != NULL) 
  {
    Array *aLeft  = getPostOrder(root->left, size);
    int sizeLeft  = aLeft->size;
    int sizeRight = 0;

    //Put the left side string from index=0
    copyArrays(array, aLeft, 0);

    if ( size<=0 || sizeLeft < size )
    {
      Array *aRight = getPostOrder(root->right, size-sizeLeft);
      int sizeRight = aRight->size;
      //Put the right side string from index=sizeLeft
      copyArrays(array, aRight, sizeLeft);

      if ( size<=0 || sizeLeft+sizeRight < size )
      {
        //Put the root in index=sizeLeft + sizeRight
        //array->tab[sizeLeft+sizeRight] = &(root->key);
        array->tab[sizeLeft+sizeRight] = root;
      }
    }
  }

  return array;
}

// Get the tree in In Order
Array* getInOrder(struct Node *root, int size) 
{
  int n = getSize(root);

  Array *array = (Array*)malloc( sizeof(Array) );
  array->size = 0;

  if (n == 0){
    return array;
  }

  if (size > 0)
  {
    n = min(n, size);
  }

  array->size = n;
  array->tab = (void*)malloc( n * sizeof(void*));

  if (root != NULL) 
  {
    Array *aLeft = getInOrder(root->left, size);
    int sizeLeft = aLeft->size;
//printf("n = %d ==> ", n);printValue(&root->key); 
//printf("   ::::   Size : %d\n", size); printf("\n");
    //Put the left side string from index=0
    copyArrays(array, aLeft, 0);

    if ( size <= 0 || sizeLeft < size )
    {
      //Put the root in index=sizeLeft
      //array->tab[sizeLeft] = &(root->key);
      array->tab[sizeLeft] = root;

      if ( (sizeLeft < size) || (size<=0) )
      {
        //Put the right side string from index=1+sizeL
        Array *aRight = getInOrder(root->right, size-sizeLeft-1);
        copyArrays(array, aRight, 1+sizeLeft);
      }
    }
  }

  return array;
}

//***********************************************************************
//Trois parcours non-standard (de droite vers la gauche) en profondeur 
//***********************************************************************

// Get the tree in Pre Order
Array* getPreOrderR2L(struct Node *root, int size) 
{
  int n = getSize(root);

  Array *array = (Array*)malloc( sizeof(Array) );
  array->size = 0;

  if (n == 0){
    return array;
  }
  
  if (size > 0)
  {
    n = min(n, size);
  }

  array->size = n;
  array->tab = (void*)malloc( n * sizeof(void*));

  if (root != NULL) 
  {
    //Put the root in index=0
    //array->tab[0] = &(root->key);
    array->tab[0] = root;

    Array *aRight = getPreOrderR2L(root->right, size-1);
    int sizeRight = aRight->size;

    //Put the right side string from index=1
    copyArrays(array, aRight, 1);

    if ( (sizeRight+1 < size) || (size<=0) )
    {
      Array *aLeft = getPreOrderR2L(root->left, size-1-sizeRight);
      //Put the left side string from index=1+sizeLeft
      copyArrays(array, aLeft, 1+sizeRight);
    }
  }

  return array;
}

// Get the tree in Post Order
Array* getPostOrderR2L(struct Node *root, int size) 
{
  int n = getSize(root);

  Array *array = (Array*)malloc( sizeof(Array) );
  array->size = 0;

  if (n == 0){
    return array;
  }

  if (size > 0)
  {
    n = min(n, size);
  }

  array->size = n;
  array->tab = (void*)malloc( n * sizeof(void*));

  if (root != NULL) 
  {
    Array *aRight  = getPostOrderR2L(root->right, size);
    int sizeRight  = aRight->size;
    int sizeLeft = 0;

    //Put the right side string from index=0
    copyArrays(array, aRight, 0);

    if ( (sizeRight < size) || (size<=0) )
    {
      Array *aLeft = getPostOrderR2L(root->left, size-sizeRight);
      int sizeLeft = aLeft->size;
      //Put the left side string from index=sizeRight
      copyArrays(array, aLeft, sizeRight);

      if ( (sizeLeft+sizeRight < size)  || (size<=0) )
      {
        //Put the root in index=sizeLeft + sizeRight
        //array->tab[sizeLeft+sizeRight] = &(root->key);
        array->tab[sizeLeft+sizeRight] = root;
      }
    }
  }

  return array;
}

// Get the tree in In Order
Array* getInOrderR2L(struct Node *root, int size) 
{
  int n = getSize(root);

  Array *array = (Array*)malloc( sizeof(Array) );
  array->size = 0;

  if (n == 0){
    return array;
  }

  if (size > 0)
  {
    n = min(n, size);
  }

  array->size = n;
  array->tab = (void*)malloc( n * sizeof(void*));

  if (root != NULL) 
  {
    Array *aRight = getInOrderR2L(root->right, size);
    int sizeRight = aRight->size;

    //Put the right side string from index=0
    copyArrays(array, aRight, 0);

    if ( (sizeRight+1 < size)  || (size<=0) )
    {
      //Put the root in index=sizeRight
      //array->tab[sizeRight] = &(root->key);
      array->tab[sizeRight] = root;
    }

    if ( (sizeRight < size) || (size<=0) )
    {
      //Put the left side string from index=1+sizeL
      Array *aLeft = getInOrderR2L(root->left, size-sizeRight-1);
      copyArrays(array, aLeft, 1+sizeRight);
    }
  }

  return array;
}

//***********************************************************************************
//Affichage avec Trois parcours standard (de gauche vers la droite) en profondeur 
//***********************************************************************************

// Print the tree in Pre Order
void printPreOrder(struct Node *root)
{
  if (root != NULL) 
  {
    printNode(root);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

// Print the tree in Post Order (ASCENDENTE)
void printPostOrder(struct Node *root)
{
  if (root != NULL) 
  {
    printPostOrder(root->left);
    printPostOrder(root->right);
    printNode(root);
  }
}

// Print the tree in In Order
void printInOrder(struct Node *root)
{
  if (root != NULL) 
  {
    printInOrder(root->left);
    printNode(root);
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
    printNode(root);
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
    printNode(root);
  }
}

// Print the tree in In Order Right to Left (DESCENDENT)
void printInOrderR2L(struct Node *root)
{
  if (root != NULL) 
  {
    printInOrderR2L(root->right);
    printNode(root);
    printInOrderR2L(root->left);
  }
}