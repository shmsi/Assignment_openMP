#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <math.h>

// Assuming the cordinates are between -10 and 10
// The maximal distance will be sqrt(1200)
#define MAX_DIST 3566

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
    double value = (int)(var * 100);
    return (double)value / 100;
}

int get_number_of_lines(FILE *file) {
    int count = 0;
    char c;
    for (c = getc(file); c != EOF; c = getc(file))
        if (c == '\n')
            count = count + 1;
    return count;
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
    file = fopen("cells5", "r");
    int len = get_number_of_lines(file);
    rewind(file);
    Coordinate coordinates[len];
    omp_set_num_threads(num_threads);

    for (int ix = 0; ix < len; ix++) {
        fscanf(file, "%lf %lf %lf", &coordinates[ix].x, &coordinates[ix].y, &coordinates[ix].z);
    }
    fclose(file);

    int *occurences = (int*)calloc(MAX_DIST, sizeof(int));

    unsigned int distance, i, j, n_per_thread;
    n_per_thread = len/num_threads;

    #pragma omp parallel shared(coordinates, len)
    {
        #pragma omp for private (i, j, distance) // schedule(static, n_per_thread)
        for (i = 0; i < len; i++) {
            for (j = i+1; j < len; j++)
            {
                double xdiff = coordinates[i].x - coordinates[j].x;
                double ydiff = coordinates[i].y - coordinates[j].y;
                double zdiff = coordinates[i].z - coordinates[j].z;
                distance = round(sqrt(xdiff*xdiff + ydiff*ydiff + zdiff*zdiff)) * 100;
                occurences[distance]++;
            }
        }
    }

    for(int i = 0; i < MAX_DIST; i++) {
            double a;
            a = ((double)i)/100.0;
            printf("%.2lf %d\n", a, occurences[i]);
    }

    return 0;
}
