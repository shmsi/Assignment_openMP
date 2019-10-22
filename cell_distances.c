#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <math.h>

// Assuming the cordinates are between -10 and 10
// The maximal distance will be sqrt(1200)
#define MAX_DIST 3565

typedef struct Coordinate
{
    short x;
    short y;
    short z;
} Coordinate;

int parseArgs(char *argv[])
{
    char *c = argv[1];
    if (c[1] == 't')
        return atoi(&c[2]);
    else
        return -1;
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
    file = fopen("cells", "r");
    int len = get_number_of_lines(file);
    rewind(file);
    Coordinate coordinates[len];
    omp_set_num_threads(num_threads);

    for (int ix = 0; ix < len; ix++) {
        float x, y, z;
        fscanf(file, "%f %f %f", &x, &y, &z);
        coordinates[ix].x = x * 1000;
        coordinates[ix].y = y * 1000;
        coordinates[ix].z = z * 1000;
    }
    fclose(file);

    long *occurences = (long*)calloc(MAX_DIST, sizeof(long));

    unsigned short distance;
    int i, j;
    #pragma omp parallel shared(coordinates, len)
    {

        #pragma omp for reduction (+: occurences[:MAX_DIST]) private (i, j, distance) schedule(dynamic)
        for (i = 0; i < len; i++) {
            for (j = i+1; j < len; j++)
            {
                short xdiff = coordinates[i].x - coordinates[j].x;
                short ydiff = coordinates[i].y - coordinates[j].y;
                short zdiff = coordinates[i].z - coordinates[j].z;
                distance = (short)(sqrt(xdiff*xdiff + ydiff*ydiff + zdiff*zdiff) / 10);
                occurences[distance]++;
            }
        }
    }

    for(int i = 0; i < MAX_DIST; i++) {
            float a;
            a = ((float)i)/100.0;
            printf("%05.2f %ld\n", a, occurences[i]);
    }

    return 0;
}
