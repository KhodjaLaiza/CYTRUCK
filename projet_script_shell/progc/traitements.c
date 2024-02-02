#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <traitements.h>

#include <tree_avl.h>

void traitement(char* csv_file, char* option, char* data_result){
  if (strcmp(option, "-d1") == 0){
    traitement_d1(csv_file, data_result);
  }
  else if (strcmp(option, "-d2") == 0){
    traitement_d2(csv_file, data_result);
  }
  else if (strcmp(option, "-l") == 0){
    traitement_l(csv_file, data_result);
  }
  else if (strcmp(option, "-t") == 0){
    traitement_t(csv_file, data_result);
  }
  else if (strcmp(option, "-s") == 0){
    traitement_s(csv_file, data_result);
  }
  else{
    printf("Erreur pas de traitement pour le paramètre %s", option);
  }
}

void traitement_d1(char* csv_file, char* data_result){
  printf("\n\n =========== Traitement [D1] ===========\n\n");

}

void traitement_d2(char* csv_file, char* data_result){
  printf("\n\n =========== Traitement [D2] ===========\n\n");
  
  FILE *file = fopen(csv_file, "r");
  if (file == NULL) {
      fprintf(stderr, "Erreur lors de l'ouverture du fichier CSV (data).\n");
      return;
  }

  // Lire les données du fichier CSV et mettre à jour les informations sur les villes
  char buffer[1024];
  int totalDrivers = 0;

  struct DriverDistance {
    char dirverName[50];
    double totalDistance;
  };
  //struct DriverDistance *listDD = NULL;
  int MAX_DRIVERS = 30000;
  struct DriverDistance listDD[MAX_DRIVERS];

  //ignorer la première ligne du fichier csv (data)
  fgets(buffer, sizeof(buffer), file);

  //parcourir le fichier csv (data)
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    int idTraject, idStep;
    char townA[50], townB[50], driver[50];
    float stepDistance;

    sscanf(buffer, "%d;%d;%[^;];%[^;];%f;%[^\n^\r]", &idTraject, &idStep, townA, townB, &stepDistance, driver);
    //printf("%d  -  %d  - from : %s  to : %s    ::::  %s ==> %f\n", idTraject, idStep, townA, townB, driver, stepDistance);

    int i;
    int index = -1;

    //Il y a un parcours ...
    for (i=0; i<totalDrivers; i++)
    {
      if (strcmp(listDD[i].dirverName, driver) == 0){
        index = i;
        break;
      }
    }

    if (index == -1)
    {
      totalDrivers++;

      strcpy(listDD[totalDrivers-1].dirverName , driver);
      listDD[totalDrivers-1].totalDistance = stepDistance;
      //printf("\n New Driver : %s => %lf", driver, listDD[totalDrivers-1].totalDistance);
    }
    else{
      listDD[index].totalDistance += stepDistance;

      //printf("\n Found Driver : %s => %lf", driver, listDD[totalDrivers-1].totalDistance);
    }


    /*
    if (listDD == NULL){
      listDD = (struct DriverDistance*)malloc( sizeof(struct DriverDistance) );
      totalDrivers = 1;

      strcpy(listDD[0].dirverName , driver);
      listDD[0].totalDistance = stepDistance;
    }
    else{
      int i;
      int index = -1;

      for (i=0; i<totalDrivers; i++)
      {
        if (strcmp(listDD[i].dirverName, driver) == 0){
          index = i;
          break;
        }
      }

      if (index != -1)
      {
        listDD[index].totalDistance += stepDistance;
      }
      else{
        totalDrivers++;
        listDD = (struct DriverDistance*)realloc(listDD, totalDrivers*sizeof(struct DriverDistance) );

        strcpy(listDD[totalDrivers-1].dirverName , driver);
        listDD[totalDrivers-1].totalDistance = stepDistance;
      }
    }
    */
  }

  printf("\n\nTotal Drivers : %d", totalDrivers);
  printf("\nDistances");
  int i;
  for (i=0; i<totalDrivers; i++)
  {
    printf("\n\tDirver : %s => Total Distance : %lf", listDD[i].dirverName, listDD[i].totalDistance);
  }


  fclose(file);
}

void traitement_l(char* csv_file, char* data_result){
  printf("\n\n =========== Traitement [L] ===========\n\n ");
}

void traitement_t(char* csv_file, char* data_result){
  printf("\n\n =========== Traitement [T] ===========\n\n ");
}

void traitement_s(char* csv_file, char* data_result){
  printf("\n\n =========== Traitement [S] ===========\n\n ");
}