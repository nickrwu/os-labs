set xrange[-30:500]
set xtics 64
set boxwidth 10
plot 'read.dat' u 1:3:2:6:5 with candlesticks
set xlabel "Block Size"
set ylabel "Time (ms)"
set yrange[0:*]
set terminal png
set output "read.png"
unset key