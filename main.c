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

int readInput() {
    FILE *file;
    file = fopen("coords.txt", "r");
    int length = getNumberOfLines(file);
    printf("%d\n", length); 

    Coordinate coordinates [length];
    return length;

}

int getNumberOfLines(FILE *file) {
    int count = 0; 
    char c;
    // Extract characters from file and store in character c 
    for (c = getc(file); c != EOF; c = getc(file)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1; 
    return count;
} 

Coordinate parseCoordinate() {
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("ERROR: Wrong number of argumnets. \n");
        printf("Usage: -t<int>. \n");
        return -1;
    }

    int num_threads = parseArgs(argv);
    int len = readInput();

    printf("%d\n", len); 
    return 0;
}


