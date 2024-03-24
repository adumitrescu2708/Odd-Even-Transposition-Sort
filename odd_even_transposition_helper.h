#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ARGC 2

extern int N;
extern int *v;

void read_input_data(char *filename) {
    FILE *input = fopen(filename, "r");

    if(!input) {
        printf("File not found %s!", filename);
        exit;
    }
    
    fscanf(input, "%d", &N);
    v = (int *) malloc(N * sizeof(int));

    if(v == NULL) {
        printf("Malloc error!\n");
        exit;
    }
    
    for(int i = 0; i < N; i++) {
        fscanf(input, "%d", &v[i]);
    }
    
    fclose(input);
}

void swap(int *a, int *b) {
    if(!a || !b) {
        return;
    }

    int c = *a;
    *a = *b;
    *b = c;
}

void print_output() {
    for(int i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void free_memory() {
    free(v);
}

int compute_start_even_idx(int idx) {
    return idx + (idx % 2);
}

int compute_start_odd_idx(int idx) {
    return idx + (1 - idx % 2);
}

int in_vector_limits(int idx, int N) {
    if(idx > 0 && idx < N)
        return 1;
    return 0;
}