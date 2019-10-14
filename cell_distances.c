#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <math.h>


typedef struct Coordinate
{
    double x;
    double y;
    double z;
} Coordinate;

int parseArgs(char *argv[])
{
    char *c = argv[1];
    if (c[1] == 't')
        return atoi(&c[2]);
    else
        return -1;
}

double round(double var) {
 double value = (int)(var * 100 + .5);
 return (double)value / 100;
}


int getNumberOfLines(FILE *file) {
    int count = 0;
    char c;
    for (c = getc(file); c != EOF; c = getc(file))
        if (c == '\n')
            count = count + 1;
    return count-1;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("ERROR: Wrong number of argumnets. \n");
        printf("Usage: -t<int>. \n");
        return -1;
    }
    int num_threads = parseArgs(argv);
    FILE *file;
    file = fopen("coords.txt", "r");
    int len = getNumberOfLines(file);
    rewind(file);
    Coordinate coordinates[len];

    for (int i = 0; i < len; i++)
        fscanf(file, "%lf %lf %lf", &coordinates[i].x, &coordinates[i].y, &coordinates[i].z);
    fclose(file);

    int *occurences = (int*)calloc(10000, sizeof(int));

    unsigned int distance, i, j, n_per_thread;
    omp_set_num_threads(num_threads);
    n_per_thread = len/num_threads;

    #pragma omp parallel shared(coordinates, len)
    {
        #pragma omp for private (i, j, distance) schedule(static, n_per_thread)
        for (i = 0; i < len; i++) {
            for (j = i+1; j < len; j++)
            {
                distance = round(sqrt(pow(coordinates[i].x - coordinates[j].x, 2) +
                            pow(coordinates[i].y - coordinates[j].y, 2) +
                            pow(coordinates[i].z - coordinates[j].z, 2) * 1.0)) * 100;
                occurences[distance]++;
            }
        }
    }

    for(int i = 0; i < 10000; i++) {
        if(occurences[i] != 0) {
            double a;
            a = ((double)i)/100.0;
            printf("%.2lf %d\n", a, occurences[i]);
        }
    }

    return 0;
}
