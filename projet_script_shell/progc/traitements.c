#include <stdio.h>
#include <string.h>
#include <traitements.h>

void traitement(char* option){
  if (strcmp(option, "-d1") == 0){
    traitement_d1();
  }
  else if (strcmp(option, "-d2") == 0){
    traitement_d2();
  }
  else if (strcmp(option, "-l") == 0){
    traitement_l();
  }
  else if (strcmp(option, "-t") == 0){
    traitement_t();
  }
  else if (strcmp(option, "-s") == 0){
    traitement_s();
  }
  else{
    printf("Erreur pas de traitement pour le paramètre %s", option);
  }
}

void traitement_d1(){
  printf("Traitement [D1]");
}

void traitement_d2(){
  printf("Traitement [D2]");
}

void traitement_l(){
  printf("Traitement [L]");
}

void traitement_t(){
  printf("Traitement [T]");
}

void traitement_s(){
  printf("Traitement [S]");
}