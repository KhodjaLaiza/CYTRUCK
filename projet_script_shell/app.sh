#!/bin/bash

#Vérifier si -h est dans la liste des paramètres

for opt in "$@" 
do
    #echo "Option : $opt";
    if [ "$opt" == "-h" ]; then
      cat "manuel.txt";
      exit 1
    fi;
done

#Vérifier le premier paramètre : fichier csv
csv_file=$1

if [ ! -f "$csv_file" ]; then
  echo "Erreur, pas de fichier CSV";
  exit 1
fi;

#argument à passer au programme C
arg=$2

#vérifier les dossiers temp et images ...
temp="./temp/"
images="./images/"

#Traiter le dossier temp
if [ -d "$temp" ]; then
  #If faut vider le dossier temp
  rm -rf "$temp"/*
else
  mkdir "$temp"
fi

#creer le dossier iamges
if [ ! -d "$images" ]; then
  mkdir "$images"
fi

#Vérifier le dossier progc
if [ ! -d "progc" ]; then
  echo "Erreur, pas de dossier du programme C";
  exit 1
fi

#Vérifier si l'exécutable C existe
exec="progc/exec"

if [ ! -f "$exec" ]; then
  #If faut vider le dossier temp
  #echo "Le programme C exec est introuvable ...."
  cd progc
  make
  cd ..
fi

#Lancer l'exécutable C

$exec "$arg";



