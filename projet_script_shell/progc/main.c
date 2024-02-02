#include <stdio.h>
	#include <stdlib.h>
#include <string.h>

#include <traitements.h>

#include <tree_avl.h>

#include <test_avl.h>

int main(int argc, char** argv){
	printf("============== LE DÉBUT DU PROGRAMME ================== ");
	printf("\n\n");

	//testAVL1();
	//testAVL2();
	//testAVL3();
	//testAVL4();

	/*
	if (1){
		return 0;
	}
	*/

	/*
	int i;
	for (i=0; i<argc; i++){
		printf("Argument N° %d : %s\n", i, argv[i]);
	}
	*/

	if (argc != 4){
		printf("Erreur : le nombre de paramètre doit ête égale 3\n");
		printf("  - Argument 1 : data csv file\n");
		printf("  - Argument 2 : option (-d1, -d2, -l, -t, -s \n");
		printf("  - Argument 3 : Les données résultats ....");

		return 1;
	}

	traitement(argv[1], argv[2], argv[3]);

	printf("\n\n");
	printf("============== LA FIN DU PROGRAMME ================== ");
	printf("\n\n");

	return 0;
}