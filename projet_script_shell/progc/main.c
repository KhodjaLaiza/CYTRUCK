#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <traitements.h>

int main(int argc, char** argv){
	int i;

	/*
	for (i=0; i<argc; i++){
		printf("Argument N° %d : %s\n", i, argv[i]);
	}
	*/

	if (argc != 2){
		printf("Erreur : le nombre de paramètre doit ête égale 2");
	}

	traitement(argv[1]);

	return 0;
}