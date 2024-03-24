/*
    nume:   Dumitrescu Alexandra  
    grupa:  343C1  
    tema:   Odd Even Transposition Sort  
    data:   Decembrie 2023

*/
#include "odd_even_transposition_helper.h"

/* given number of elements in array */
int N;

/* initial array */
int *v;

void solve_serial() {
    /* N phases */
    for(int k = 0; k < N; k++) {
        /* even phase */
        if(k % 2 == 0) {
            /* only check the even indexes in the given array */
            for(int j = 0; j < N - 1; j += 2) {
                if(v[j] > v[j + 1]) {
                    swap(&v[j], &v[j + 1]);
                }
            }
        }
        /* odd phase */
        if(k % 2 == 1) {
            /* only check the odd indexes in the given array */
            for(int j = 1; j < N - 1; j += 2) {
                if(v[j] > v[j + 1]) {
                    swap(&v[j], &v[j + 1]);
                }
            }
        }
    }
}

int main(int argc, char **argv) {
    clock_t begin = clock();
    
    /* check arguments */
    if(argc != ARGC) {
        printf("Invalid parameters! Try: ./serial <file.in>");
        return -1;
    }
    
    /* read input from given file */
    read_input_data(argv[1]);
    
    /* solve problem */
    solve_serial();
    
    /* print results */
    print_output();
    
    /* free memory */
    free_memory();
    
    /* compute and print to stderr execution time */
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr, "%f\n", time_spent);
}