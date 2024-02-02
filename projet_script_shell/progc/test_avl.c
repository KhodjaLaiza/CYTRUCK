#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <test_avl.h>

#include <tree_avl.h>

//========================================================================
//Test 1
//========================================================================
void testAVL1(){
	printf("\n\n");
	printf("	**============== LE DÉBUT des TESTS ==================**\n");

	struct Node *root = NULL;

	setKeyValueType(AVL_KEY_INT);
	
	root = insertNode(root, 33.25);
	root = insertNode(root, 61);
	root = insertNode(root, 53);
	root = insertNode(root, 21);
	root = insertNode(root, 11);
	root = insertNode(root, 8);
	root = insertNode(root, 9);
	root = insertNode(root, 13);
	root = insertNode(root, 36);
	root = insertNode(root, 99);
	root = insertNode(root, 12);
	root = insertNode(root, 2);
	root = insertNode(root, 199);
	root = insertNode(root, 212);
	root = insertNode(root, 32);
	

	printf("\n\n Nombre d'élément de l'arbre est :%d\n\n", getSize(root));

	/*
	printf("\n\nAffichage de l'AVL in Prefixe : ");
	printPreOrder(root);
	printf("\n\n");

	printf("Affichage de l'AVL in Postfixe : ");
	printPostOrder(root);
	printf("\n\n");
	*/

	printf("Affichage de l'AVL in Prefixe : \n");
	printPreOrder(root);
	printf("\n\n");

	printf("Affichage de l'AVL in Infixe : \n");
	printInOrder(root);
	printf("\n\n");

	printf("Affichage de l'AVL in Postfixe : \n");
	printPostOrder(root);
	printf("\n\n");

	printf("------------------------------------------\n\n");

	int i = 0;

	printf("Avoir les valeurs in Prefixe : \n");
	Array *aPrefix = getPreOrder(root, 0);
	for (i=0; i<aPrefix->size; i++)
	{
		 printNode(aPrefix->tab[i]);
	}
	printf("\n\n");

	printf("Avoir les valeurs in Infixe : \n");
	Array *aInfix = getInOrder(root, 0);
	for (i=0; i<aInfix->size; i++)
	{
		printNode(aInfix->tab[i]);
	}
	printf("\n\n");

	printf("Avoir les valeurs in Postfixe : \n");
	Array *aPostfix = getPostOrder(root, 0);
	for (i=0; i<aPostfix->size; i++)
	{
		printNode(aPostfix->tab[i]);
	}


	printf("\n\n");
	printf("	**============== LA FIN des TESTS ==================** ");
	printf("\n\n");

	//root = deleteNode(root, 3);

	//printf("\nAfter deletion: \n");
	//printPreOrder(root);
}


//========================================================================
//Test 2
//========================================================================
void testAVL2(){
	printf("\n\n");
	printf("	**============== LE DÉBUT des TESTS (Right To Left) ==================**\n");

	struct Node *root = NULL;

	setKeyValueType(AVL_KEY_INT);
	
	root = insertNode(root, 33.25);
	root = insertNode(root, 61);
	root = insertNode(root, 53);
	root = insertNode(root, 21);
	root = insertNode(root, 11);
	root = insertNode(root, 8);
	root = insertNode(root, 9);
	root = insertNode(root, 13);
	root = insertNode(root, 36);
	root = insertNode(root, 99);
	root = insertNode(root, 12);
	root = insertNode(root, 2);
	root = insertNode(root, 199);
	root = insertNode(root, 212);
	root = insertNode(root, 32);
	

	printf("\n\n  =>  Nombre d'élément de l'arbre est :%d\n\n", getSize(root));

	printf("Affichage de l'AVL in Prefixe (R2L) : \n");
	printPreOrderR2L(root);
	printf("\n\n");

	printf("Affichage de l'AVL in Infixe (R2L) : \n");
	printInOrderR2L(root);
	printf("\n\n");

	printf("Affichage de l'AVL in Postfixe (R2L) : \n");
	printPostOrderR2L(root);
	printf("\n\n");

	printf("------------------------------------------\n\n");

	int i = 0;

	printf("Avoir les valeurs in Prefixe (R2L) : \n");
	Array *aPrefix = getPreOrderR2L(root, 0);
	for (i=0; i<aPrefix->size; i++)
	{
		 printNode(aPrefix->tab[i]);
	}
	printf("\n\n");

	printf("Avoir les valeurs in Infixe (R2L) : \n");
	Array *aInfix = getInOrderR2L(root, 0);
	for (i=0; i<aInfix->size; i++)
	{
		printNode(aInfix->tab[i]);
	}
	printf("\n\n");

	printf("Avoir les valeurs in Postfixe (R2L) : \n");
	Array *aPostfix = getPostOrderR2L(root, 0);
	for (i=0; i<aPostfix->size; i++)
	{
		printNode(aPostfix->tab[i]);
	}
	printf("\n\n");

	printf("	**============== LA FIN des TESTS ==================** ");
	printf("\n\n");
}


//========================================================================
//Test 3
//========================================================================
void testAVL3(){
	printf("\n\n");
	printf("	**============== LE DÉBUT des TESTS (Ordre Croissant & Décroissant) ==================**\n");

	struct Node *root = NULL;

	setKeyValueType(AVL_KEY_FLOAT);
	
	root = insertNode(root, 33.25);
	root = insertNode(root, 61);
	root = insertNode(root, 53);
	root = insertNode(root, 21);
	root = insertNode(root, 11);
	root = insertNode(root, 12.33);
	root = insertNode(root, 8);
	root = insertNode(root, 9);
	root = insertNode(root, 13);
	root = insertNode(root, 36);
	root = insertNode(root, 99);
	root = insertNode(root, 11.99);
	root = insertNode(root, 12);
	root = insertNode(root, 2);
	root = insertNode(root, 199);
	root = insertNode(root, 212);
	root = insertNode(root, 32);
	

	printf("\n\n  =>  Nombre d'élément de l'arbre est :%d\n\n", getSize(root));

	printf("Affichage de l'AVL in Infixe (Ordre croissant) : \n");
	printInOrder(root);
	printf("\n\n");

	printf("Affichage de l'AVL in Infixe (R2L : Ordre décroissant) : \n");
	printInOrderR2L(root);
	printf("\n\n");


	printf("------------------------------------------\n\n");

	int i = 0;

	printf("Avoir les valeurs in Infixe (Ordre croissant) : \n");
	Array *aInfix = getInOrder(root, 0);
	for (i=0; i<aInfix->size; i++)
	{
		printNode(aInfix->tab[i]);
	}
	printf("\n\n");

	
	printf("Avoir les valeurs in Infixe (R2L : Ordre décroissant) : \n");
	Array *aInfixR2L = getInOrderR2L(root, 0);
	for (i=0; i<aInfixR2L->size; i++)
	{
		printNode(aInfixR2L->tab[i]);
	}
	printf("\n\n");

	

	printf("	**============== LA FIN des TESTS ==================** ");
	printf("\n\n");
}


//========================================================================
//Test 4
//========================================================================
void testAVL4(){
	printf("\n\n");
	printf("	**============== LE DÉBUT des TESTS ==================**\n");

	struct Node *root = NULL;

	setKeyValueType(AVL_KEY_INT);

	struct Valeurs {
		char nom[100];
	};
	
	/*
	struct Valeurs* info = (struct Valeurs*)malloc( sizeof(struct Valeurs) );
	strcpy(info->nom, "Mohammed");
	*/

	root = insertNodeInfo(root, 33.25, "Laiza");
	root = insertNodeInfo(root, 61, "Mohammed");
	root = insertNodeInfo(root, 53, "Sara");
	root = insertNodeInfo(root, 21, "Muamed");
	root = insertNodeInfo(root, 11, "info");
	root = insertNodeInfo(root, 8, "info12");
	root = insertNodeInfo(root, 9, "info33");
	root = insertNodeInfo(root, 13, "info");
	root = insertNodeInfo(root, 36, "info6");
	root = insertNodeInfo(root, 99, "info-ing");
	root = insertNodeInfo(root, 12, "info-réseau");
	root = insertNodeInfo(root, 2, "info-gl");
	root = insertNodeInfo(root, 199, "GL");
	root = insertNodeInfo(root, 212, "Développeur");
	root = insertNodeInfo(root, 32, "Redoaune");
	

	printf("\n\n Nombre d'élément de l'arbre est :%d\n\n", getSize(root));

	/*
	printf("\n\nAffichage de l'AVL in Prefixe : ");
	printPreOrder(root);
	printf("\n\n");

	printf("Affichage de l'AVL in Postfixe : ");
	printPostOrder(root);
	printf("\n\n");
	*/

	printf("Affichage de l'AVL in Prefixe : \n");
	printPreOrder(root);
	printf("\n\n");

	printf("Affichage de l'AVL in Infixe : \n");
	printInOrder(root);
	printf("\n\n");

	printf("Affichage de l'AVL in Postfixe : \n");
	printPostOrder(root);
	printf("\n\n");

	printf("------------------------------------------\n\n");

	int i = 0;

	printf("Avoir les valeurs in Prefixe : \n");
	Array *aPrefix = getPreOrder(root, 0);
	for (i=0; i<aPrefix->size; i++)
	{
		 printNode(aPrefix->tab[i]);
	}
	printf("\n\n");

	printf("Avoir les valeurs in Infixe : \n");
	Array *aInfix = getInOrder(root, 0);
	for (i=0; i<aInfix->size; i++)
	{
		printNode(aInfix->tab[i]);
	}
	printf("\n\n");

	printf("Avoir les valeurs in Postfixe : \n");
	Array *aPostfix = getPostOrder(root, 0);
	for (i=0; i<aPostfix->size; i++)
	{
		printNode(aPostfix->tab[i]);
		printf("(%s)  ", ((struct Node*)(aPostfix->tab[i]))->info);
	}


	printf("\n\n");
	printf("	**============== LA FIN des TESTS ==================** ");
	printf("\n\n");

	//root = deleteNode(root, 3);

	//printf("\nAfter deletion: \n");
	//printPreOrder(root);
}