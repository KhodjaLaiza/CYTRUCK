reset session
set terminal png size 1000,800
set output './images/traitement_t___2024-02-02 18-53-45-353.png'
set title 'Option -t : Nb routes = f(Towns)'
set xlabel 'TOWN NAMES'
set ylabel 'NB ROUTES'
set datafile separator ';'
set style data histogram
set style histogram clustered
set style fill solid border -1
set boxwidth 0.8
myBoxWidth = 0.8
set offsets 0,0,0.5-myBoxWidth/2.,0.5
set xtic rotate by -45 scale 0
set yrange [0:*]; set xrange [-0.5:*]
set label 1 'Total routes' at graph 0.90, 0.97 right
set label 2 'First town' at graph 0.90, 0.94 right
plot for [COL=2:3] './demo/traitement_t___2024-02-02 18-53-45-353.dat' using COL:xticlabels(1)
