
CC = gcc
FLAGS = -lm -fopenmp

output: cell_distances.o
	$(CC) cell_distances.o -o output $(FLAGS)

cell_distances.o: cell_distances.c
	$(CC) -c cell_distances.c $(FLAGS)

clean:
	rm *.o output *.out

