#include <stdio.h> 
#include <stdlib.h> 

 typedef struct Coordinate {
    double x; 
    double y;
    double z;
} Coordinate; 

int parseArgs(char* argv[]) {
    char *c  = argv[1];
    if(c[1] == 't') return atoi(&c[2]); else return -1; 
}


int getNumberOfLines(FILE *file) {
    int count = 0; 
    char c;
    for (c = getc(file); c != EOF; c = getc(file)) 
        if (c == '\n')
            count = count + 1; 
    return count-1;
} 

Coordinate* readInput() {
    FILE *file;
    file = fopen("coords.txt", "r");
    int len = getNumberOfLines(file);
    rewind(file);
    Coordinate coordinates[len];

    for(int i = 0; i < len; i++) 
        fscanf(file, "%lf %lf %lf", &coordinates[i].x, &coordinates[i].y, &coordinates[i].z);

    printf("%lf", coordinates[9].z);
    fclose(file); 

    return coordinates;
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("ERROR: Wrong number of argumnets. \n");
        printf("Usage: -t<int>. \n");
        return -1;
    }
    int num_threads = parseArgs(argv);
    readInput(); 
    return 0;

}

