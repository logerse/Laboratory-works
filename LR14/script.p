set terminal png size 500,500
set output 'data/result.png
plot 'data.dat' matrix with image
