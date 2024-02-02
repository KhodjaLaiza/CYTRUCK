#!/bin/bash

#Vérifier si -h est dans la liste des paramètres

for opt in "$@" 
do
    #echo "Option : $opt";
    if [ "$opt" == "-h" ]; then
      cat "read_me.txt";
      exit 1
    fi;
done

#Vérifier le premier paramètre : fichier data csv
data_csv_file=$1

if [ ! -f "$data_csv_file" ]; then
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

#preparation de dossier demo
demo="./demo/"
if [ ! -d "$demo" ]; then
  mkdir "$demo"
fi

#Vérifier si l'exécutable existe
exec="progc/exec"

if [ ! -f "$exec" ]; then
  #echo "Le programme exec est introuvable => compiler (make) ...."
  cd progc
  make
  cd ..
fi


#Exécuter le Traitement via le script shell :
#traitement d1
for opt1 in "$@"
do
    #echo "Option : $opt";
    # =============================================
    # ============== Option -d1 ===================
    # =============================================
    if [ "$opt1" == "-d1" ]; then
      SECONDS=0
      echo "Début du traitement [D1] (option -d1) : conducteurs avec le plus de trajets"
      echo -e "Heure de debut : $(date +"%T.%N")"


      date_time=$(date +"%Y-%m-%d %H-%M-%S-%3N")

      #préparation des noms des fichiers : les trois fichiers auront le même nom (avec date & heure)
      fichier_resultats=""$demo"traitement_d1___"$date_time".dat"
      fichier_gnuplot=""$demo"traitement_d1___"$date_time".gnu"
      fichier_image=""$images"traitement_d1___"$date_time".png"
      
      #création du fichier gnu (configuration pour gnuplot)
      echo "reset session" >> "$fichier_gnuplot";
      echo "set terminal png size 1000,800" >> "$fichier_gnuplot";
      echo "set output '"$fichier_image"'" >> "$fichier_gnuplot";
      echo "set title 'Option -d1 : Nb routes = f(Driver)'" >> "$fichier_gnuplot";
      echo "set xlabel 'NB ROUTES'" >> "$fichier_gnuplot";
      echo "set ylabel 'DRIVER NAMES'" >> "$fichier_gnuplot";
      echo "set yrange [0:*] reverse    # start at zero, find max from the data" >> "$fichier_gnuplot";
      echo "set datafile separator ';'" >> "$fichier_gnuplot";
      echo "unset key             # turn off all titles" >> "$fichier_gnuplot";
      echo "myBoxWidth = 0.8" >> "$fichier_gnuplot";
      echo "set offsets 0,0,0.5-myBoxWidth/2.,0.5" >> "$fichier_gnuplot";
      echo "set style fill transparent solid 0.5 noborder" >> "$fichier_gnuplot";
      echo "plot '"$fichier_resultats"' using (0.5*\$2):0:(0.5*\$2):(myBoxWidth/2.):(\$0+1):ytic(1) with boxxy lc var" >> "$fichier_gnuplot";
      #fin de la création du fichier gnu

      #sélectionner les deux colonnes 1 (Route_ID : trajet) et 6 (Driver name : nom du chauffeur)
      cut -d ';' -f1,6 "$data_csv_file" | 
      #filtrer les lignes identiques en enlevant les doubles (chaque ligne devient unique)
      perl -ne '$dupicate_lines{$_}++ or print' |
      #compter le nombre de trajet par chauffeur avec le tableau associatif : nb_trajects_by_driver
      awk -F ';' 'NR > 1 {nb_trajects_by_driver[$2]++} END { for (driver in nb_trajects_by_driver) print  driver ";" nb_trajects_by_driver[driver] }' | 
      #trier avec ordre croissant selon le nombre de trajets
      sort -nt ';' -k2 | 
      #prendre les 10 derniers (ayant le plus trajets)
      tail -10 | 
      #inverser les les lignes et envoyer les donnéer vers fichier résultat
      tac > "$fichier_resultats"

      #affichage sur écran des résultats ...
      cat "$fichier_resultats"

      #générer l'image avec gnuplot
      gnuplot "$fichier_gnuplot";

      echo "Fin du traitement -d1"

      echo -e "Heure de fin : $(date +"%T.%N")"
      duration=$SECONDS
      echo "Durée de Traiement : $duration seconds";

      exit 1
    fi;


    # =============================================
    # ============== Option -d2 ===================
    # =============================================
    if [ "$opt1" == "-d2" ]; then
      SECONDS=0
      echo "Début du traitement [D2] (Option -d2) : conducteurs avec les plus grandes distances"
      echo -e "Heure de debut : $(date +"%T.%N")"


      date_time=$(date +"%Y-%m-%d %H-%M-%S-%3N")

      #préparation des noms des fichiers : les trois fichiers auront le même nom (avec date & heure)
      fichier_resultats=""$demo"traitement_d2___"$date_time".dat"
      fichier_gnuplot=""$demo"traitement_d2___"$date_time".gnu"
      fichier_image=""$images"traitement_d2___"$date_time".png"
      
      #création du fichier gnu (configuration pour gnuplot)
      echo "reset session" >> "$fichier_gnuplot";
      echo "set terminal png size 1000,800" >> "$fichier_gnuplot";
      echo "set output '"$fichier_image"'" >> "$fichier_gnuplot";
      echo "set title 'Option -d2 : Distance = f(Driver)'" >> "$fichier_gnuplot";
      echo "set xlabel 'DISTANCES'" >> "$fichier_gnuplot";
      echo "set ylabel 'DRIVER NAMES'" >> "$fichier_gnuplot";
      echo "set yrange [0:*] reverse    # start at zero, find max from the data" >> "$fichier_gnuplot";
      echo "set datafile separator ';'" >> "$fichier_gnuplot";
      echo "unset key             # turn off all titles" >> "$fichier_gnuplot";
      echo "myBoxWidth = 0.8" >> "$fichier_gnuplot";
      echo "set offsets 0,0,0.5-myBoxWidth/2.,0.5" >> "$fichier_gnuplot";
      echo "set style fill transparent solid 0.5 noborder" >> "$fichier_gnuplot";
      echo "plot '"$fichier_resultats"' using (0.5*\$2):0:(0.5*\$2):(myBoxWidth/2.):(\$0+1):ytic(1) with boxxy lc var" >> "$fichier_gnuplot";
      #fin de la création du fichier gnu

      #sélectionner les deux colonnes 5 (Distance) et 6 (Driver name : nom du chauffeur)
      cut -d ';' -f5,6 "$data_csv_file" | 
      #calculer la distance totale (cumul) pour chaque chauffeur avec le tableau associatif : distances_by_driver
      awk -F ';' 'NR > 1 {distances_by_driver[$2] += $1} END { for (driver in distances_by_driver) printf "%s;%.6f\n",driver,distances_by_driver[driver] }' | 
      #trier avec ordre croissant selon la distance totale parcourrue
      sort -nt ';' -k2 | 
      #prendre les 10 derniers (ayant les plus grandes distances)
      tail -10 | 
      #inverser les les lignes et envoyer les donnéer vers fichier résultat
      tac > "$fichier_resultats"

      #affichage sur écran des résultats ...
      cat "$fichier_resultats"

      #générer l'image avec gnuplot
      gnuplot "$fichier_gnuplot";

      echo "Fin du traitement -d2"

      echo -e "Heure de fin : $(date +"%T.%N")"
      duration=$SECONDS
      echo "Durée de Traiement : $duration seconds";

      exit 1
    fi;


    # =============================================
    # ============== Option -l: ===================
    # =============================================
    if [ "$opt1" == "-l" ]; then
      SECONDS=0
      echo "Début du traitement [L] (option -l) : les 10 trajets les plus longs"
      echo -e "Heure de debut : $(date +"%T.%N")"


      date_time=$(date +"%Y-%m-%d %H-%M-%S-%3N")

      #préparation des noms des fichiers : les trois fichiers auront le même nom (avec date & heure)
      fichier_resultats=""$demo"traitement_l___"$date_time".dat"
      fichier_gnuplot=""$demo"traitement_l___"$date_time".gnu"
      fichier_image=""$images"traitement_l___"$date_time".png"
      
      #création du fichier gnu (configuration pour gnuplot)
      echo "reset session" >> "$fichier_gnuplot";
      echo "set terminal png size 1000,800" >> "$fichier_gnuplot";
      echo "set output '"$fichier_image"'" >> "$fichier_gnuplot";
      echo "set title 'Option -l : Distance = f(Routes)'" >> "$fichier_gnuplot";
      echo "set xlabel 'ID ROUTES'" >> "$fichier_gnuplot";
      echo "set ylabel 'DISTANCES'" >> "$fichier_gnuplot";
      echo "set xrange [-0.7:*]    # start at zero, find max from the data" >> "$fichier_gnuplot";
      echo "set yrange [0:*]       # start at zero, find max from the data" >> "$fichier_gnuplot";
      echo "set datafile separator ';'" >> "$fichier_gnuplot";
      echo "unset key             # turn off all titles" >> "$fichier_gnuplot";
      echo "myBoxWidth = 0.8" >> "$fichier_gnuplot";
      echo "set offsets 0,0,0.5-myBoxWidth/2.,0.5" >> "$fichier_gnuplot";
      echo "rgb(r,g,b)=int(255*r)*65536+int(255*g)*256+int(255*b)" >> "$fichier_gnuplot";
      echo "do for [i=1:30] {" >> "$fichier_gnuplot";
      echo "   myrand=rand(int(rand(0)*i*100)+i*100)" >> "$fichier_gnuplot";
      echo "   set style line i linecolor rgb rgb(rand(0),rand(0),rand(0))" >> "$fichier_gnuplot";
      echo "}" >> "$fichier_gnuplot";
      echo "set style fill transparent solid 0.5 noborder" >> "$fichier_gnuplot";
      echo "set style data histograms" >> "$fichier_gnuplot";
      echo "set boxwidth 0.75;" >> "$fichier_gnuplot";
      echo "plot '"$fichier_resultats"' using (\$0):2:(\$0):xticlabels(1) notitle w boxes lc variable" >> "$fichier_gnuplot";
      #fin de la création du fichier gnu

      #sélectionner les deux colonnes 5 (Distance) et 6 (Driver name : nom du chauffeur)
      cut -d ';' -f1,5 "$data_csv_file" | 
      #calculer la distance totale (cumul) pour chaque routes avec le tableau associatif : distances_by_route
      awk -F ';' 'NR > 1 {distances_by_route[$1] += $2} END { for (route_id in distances_by_route) printf "%s;%.6f\n",route_id,distances_by_route[route_id] }' | 
      #trier avec ordre croissant selon la distance totale parcourrue
      sort -nt ';' -k2 | 
      #prendre les 10 derniers (ayant les plus grandes distances)
      tail -10 |
      #trier avec ordre croissant selon l'ID Route
      sort -nt ';' -k1 |
      #inverser le trie
      tac > "$fichier_resultats"

      #affichage sur écran des résultats ...
      cat "$fichier_resultats"

      #générer l'image avec gnuplot
      gnuplot "$fichier_gnuplot";

      echo "Fin du traitement -l"

      echo -e "Heure de fin : $(date +"%T.%N")"
      duration=$SECONDS
      echo "Durée de Traiement : $duration seconds";

      exit 1
    fi;


    # =============================================
    # ============== Option -t: ===================
    # =============================================
    if [ "$opt1" == "-t" ]; then
      SECONDS=0
      echo "Début du traitement [T] (Option -t) : les 10 villes les plus traversées"
      echo -e "Heure de debut : $(date +"%T.%N")"

      date_time=$(date +"%Y-%m-%d %H-%M-%S-%3N")

      #préparation des noms des fichiers : les trois fichiers auront le même nom (avec date & heure)
      fichier_resultats=""$demo"traitement_t___"$date_time".dat"
      fichier_csv_temp=""$temp"traitement_t___"$date_time".csv"
      fichier_gnuplot=""$demo"traitement_t___"$date_time".gnu"
      fichier_image=""$images"traitement_t___"$date_time".png"

      #création du fichier gnu (configuration pour gnuplot)
      echo "reset session" >> "$fichier_gnuplot";
      echo "set terminal png size 1000,800" >> "$fichier_gnuplot";
      echo "set output '"$fichier_image"'" >> "$fichier_gnuplot";
      echo "set title 'Option -t : Nb routes = f(Towns)'" >> "$fichier_gnuplot";
      echo "set xlabel 'TOWN NAMES'" >> "$fichier_gnuplot";
      echo "set ylabel 'NB ROUTES'" >> "$fichier_gnuplot";
      echo "set datafile separator ';'" >> "$fichier_gnuplot";
      echo "set style data histogram" >> "$fichier_gnuplot";
      echo "set style histogram clustered" >> "$fichier_gnuplot";
      echo "set style fill solid border -1" >> "$fichier_gnuplot";
      echo "set boxwidth 0.8" >> "$fichier_gnuplot";
      echo "myBoxWidth = 0.8" >> "$fichier_gnuplot";
      echo "set offsets 0,0,0.5-myBoxWidth/2.,0.5" >> "$fichier_gnuplot";
      echo "set xtic rotate by -45 scale 0" >> "$fichier_gnuplot";
      echo "set yrange [0:*]; set xrange [-0.5:*]" >> "$fichier_gnuplot";
      #echo "set label 1 'Total routes' at graph 0.90, 0.97 right" >> "$fichier_gnuplot";
      #echo "set label 2 'First town' at graph 0.90, 0.94 right" >> "$fichier_gnuplot";
      #echo "plot '$fichier_resultats' u 2 title ' ', '' u ((\$2)/2.0+rand(0)/10.0) title ' ', '' u 0:(0):xticlabel(1) w l title ''" >> "$fichier_gnuplot";
      echo "plot for [COL=2:3] '$fichier_resultats' using COL:xticlabels(1) title 'Total routes','First town'" >> "$fichier_gnuplot";
      #fin de la création du fichier gnu

      #sélectionner les quatre colonnes 1 (Route ID), 2 (Step ID), 3 (Town A) et 4 (Town B)
      cut -d';' -f1,2,3,4 "$data_csv_file" |
      #generer des données contenant : ville , nombre de passage et nombre de fois où cette ville état la ville de départ ...
      awk -v OFS=';' -F ';' 'NR>1 { if (count_start_by_traject[$1][$4]!=1){count_passage[$4]++;} if (count_start[$4] == ""){count_start[$4]=0;}; if($2==1){count_start[$3]++;count_start_by_traject[$1][$3]=1;count_passage[$3]++;} } END { for (town in count_passage) print town, count_passage[town], count_start[town];}' |
      sort -nt ';' -k2 | 
      #prendre les 10 derniers (ayant les plus grandes distances)
      tail -10 |
      #trier avec ordre croissant selon l'ID Route
      sort -nt ';' -k1 > "$fichier_resultats"

      #affichage sur écran des résultats ...
      cat "$fichier_resultats"

      #générer l'image avec gnuplot
      gnuplot "$fichier_gnuplot";

      echo -e "Heure de fin : $(date +"%T.%N")"
      duration=$SECONDS
      echo "Durée de Traiement : $duration seconds";

      exit 1
    fi;


    # =============================================
    # ============== Option -s: ===================
    # =============================================
    if [ "$opt1" == "-s" ]; then
      SECONDS=0
      echo "Début du traitement [S] (Option -s) : statistiques sur les étapes"
      echo -e "Heure de debut : $(date +"%T.%N")"

      date_time=$(date +"%Y-%m-%d %H-%M-%S-%3N")



      #préparation des noms des fichiers : les trois fichiers auront le même nom (avec date & heure)
      fichier_resultats=""$demo"traitement_l___"$date_time".dat"
      fichier_gnuplot=""$demo"traitement_l___"$date_time".gnu"
      fichier_image=""$images"traitement_l___"$date_time".png"


      

      echo -e "Heure de fin : $(date +"%T.%N")"
      duration=$SECONDS
      echo "Durée de Traiement : $duration seconds";

      exit 1
    fi;

done
