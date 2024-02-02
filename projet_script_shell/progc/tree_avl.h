#ifndef __TREE_AVL_H__
#define __TREE_AVL_H__

#define AVL_KEY_INT     0
#define AVL_KEY_FLOAT   1
#define AVL_KEY_DOUBLE  2

// Create Node
struct Node {
  double key;

  void *info;

  struct Node *left;
  struct Node *right;
  int height;
};

typedef struct Array {
  int size;
  void** tab;
} Array;

// Calculate height
int height(struct Node *N);

int max(int a, int b);
int min(int a, int b);

int isIntKey();
int isFloatKey();
int isDoubleKey();

void setKeyValueType(int type);

double setKeyType(struct Node *node);

void printNode(struct Node *node);
//void printValue(void *value);

// Create a node
struct Node *newNodeInfo(double key, void *info);
struct Node *newNode(double key);

// Right rotate
struct Node *rightRotate(struct Node *y);

// Left rotate
struct Node *leftRotate(struct Node *x);

// Get the balance factor
int getBalance(struct Node *N);

// Insert node
struct Node *insertNodeInfo(struct Node *node, double key, void *info);
struct Node *insertNode(struct Node *node, double key);

struct Node *minValueNode(struct Node *node);

// Delete a nodes
struct Node *deleteNode(struct Node *root, double key);

// Avoir le nombre d'éléments de l'arbre AVL
int getSize(struct Node *root);

//Copy b elements to a and free the memory of b
void copyArrays(Array* a, Array* b, int start);


//Trois parcours standard (de gauche vers la droite) en profondeur 

// Get the tree in Pre Order
Array* getPreOrder(struct Node *root, int size);

// Get the tree in Post Order
Array* getPostOrder(struct Node *root, int size);

// Get the tree in In Order
Array* getInOrder(struct Node *root, int size);


//Trois parcours non-standard (de droite vers la gauche) en profondeur 

// Get the tree in Pre Order
Array* getPreOrderR2L(struct Node *root, int size);

// Get the tree in Post Order
Array* getPostOrderR2L(struct Node *root, int size);

// Get the tree in In Order
Array* getInOrderR2L(struct Node *root, int size);


//Affichage avec Trois parcours standard (de gauche vers la droite) en profondeur 

// Print the tree in Pre Order
void printPreOrder(struct Node *root);

// Print the tree in Post Order
void printPostOrder(struct Node *root);

// Print the tree in In Order
void printInOrder(struct Node *root);


//Affichage avec Trois parcours non-standard (de droite vers la gauche) en profondeur 

// Print the tree in Pre Order
void printPreOrderR2L(struct Node *root);

// Print the tree in Post Order
void printPostOrderR2L(struct Node *root);

// Print the tree in In Order
void printInOrderR2L(struct Node *root);

#endif