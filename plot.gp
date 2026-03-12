# Настройка формата данных
set datafile separator ","
set grid xtics ytics ls 12 lc rgb '#dddddd'

# Настройка терминала (качественный PNG)
set term pngcairo size 1000, 800 font "Arial,12"

# === ГРАФИК 1: ФАЗОВЫЙ ПОРТРЕТ (Пункты 3-a, 3-b, 3-d) ===
# Здесь мы видим структуру системы: фокусы, седла и макрообласть
set output "phase_portrait.png"
set title "Фазовый портрет системы (Вариант 13)"
set xlabel "xi (Координата)"
set ylabel "y (Скорость)"

# Рисуем линии. Если в файле несколько траекторий через пустую строку, 
# Gnuplot сам поймет, где начинать новую линию.
plot "out.csv" using 3:4 with lines lw 2 lc rgb "blue" title "Траектория y(xi)"

# === ГРАФИК 2: ЗАВИСИМОСТЬ ОТ ВРЕМЕНИ (Пункт 3-c) ===
# Позволяет увидеть динамику: затухание, рост или колебания
set output "time_series.png"
set title "Зависимость координат от времени tau"
set xlabel "tau (Время)"
set ylabel "Значение"

plot "out.csv" using 2:3 with lines lw 2 lc rgb "red" title "xi(tau)", \
     "out.csv" using 2:4 with lines lw 2 lc rgb "green" title "y(tau)"
