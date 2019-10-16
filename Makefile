CC = gcc
FLAGS = -lm -fopenmp

cell_distances: cell_distances.c
	$(CC) -march=native -O2 cell_distances.c -o cell_distances $(FLAGS)  

#cell_distances.o: cell_distances.c
#	$(CC) -c cell_distances.c $(FLAGS)

clean:
	rm -f *.o cell_distances *.out *.tar.gz
