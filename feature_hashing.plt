set terminal png
set title "Performance of Fast Adaboost with increasing number of hash bits"
set xrange [10:10000]
set logscale x 10
set yrange [0:0.4]
set y2range [10:50]
set ytics
set y2tics
set xlabel "number of hash bits"
set ylabel "Error rate"
set y2label "Running time"
set output "feature_hashing.png"

plot "feature_hashing.dat" using 1:2 title col with lp, '' using 1:3 ti col axes x1y2 with lp