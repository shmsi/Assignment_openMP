CC = gcc
FLAGS = -lm -fopenmp

cell_distances: cell_distances.o
	$(CC) cell_distances.o -o cell_distances $(FLAGS)

cell_distances.o: cell_distances.c
	$(CC) -c cell_distances.c $(FLAGS)

clean:
	rm *.o cell_distances *.out *.tar.gz