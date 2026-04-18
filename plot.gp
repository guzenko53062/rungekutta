set datafile separator ","
set terminal png size 1200,800 font "Arial,12"
set key autotitle columnhead
set grid

# === Time Series ===
set output "time.png"
set xlabel "Time (tau)"
set ylabel "Value"
set title "Time Series: xi and y_sys"


set yrange [-5.0:5.0]
set xrange [*:*] 

set offsets 0,0,0,0
set autoscale fix

plot "data.csv" using 2:3 with lines linewidth 2 title "xi", \
     "data.csv" using 2:4 with lines linewidth 2 title "y_sys"

# === Phase Portrait ===
set output "phase.png"
set xlabel "xi"
set ylabel "y_sys"
set title "Phase Portrait"
set key off

set xrange [-5.0:5.0] 
set yrange [-5.0:5.0] 


set offsets 0,0,0,0
set autoscale fix

set border linewidth 1.5
set grid linewidth 0.5

plot "data.csv" using 3:4 with lines linewidth 2
