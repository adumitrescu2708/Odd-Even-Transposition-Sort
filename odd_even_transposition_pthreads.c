/*
    nume:   Dumitrescu Alexandra  
    grupa:  343C1  
    tema:   Odd Even Transposition Sort  
    data:   Decembrie 2023

*/

#include "odd_even_transposition_helper.h"
#include <pthread.h>
#include <sys/time.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

/* structs used for computing execution time */
struct timeval start, end;

/* number of threads - it can be varied for Tema3 */
int NUM_THREADS = 4;

/* used for sinchronizing threads between odd phase and even phase */
pthread_barrier_t barrier;

/* given number of elements in array */
int N;

/* initial array */
int *v;

/*
    Descriere solutie:

    1) Se imparte vectorul initial la NUM_THREADS threaduri in mod egal
    2) Fiecare thread se va ocupa de bucata asignata lui
    3) Pot aparea probleme la capetele intervalului, deoarece un thread poate accesa cu o casuta
    in plus fata de zona asignata. Exemplu concret:

    [A]
        v = [1, 2, 3, 4, 5, 6]
        NUM_THREADS = 2

        v = [1, 2, 3, 4, 5, 6]
        THREAD_1 = [1, 2, 3]
        THREAD_2 = [4, 5, 6]

        Faza para:
        THREAD_1 = [1, 2, 3] -> (1, 2) (3, 4) [THREAD_1 acceseaza elementul 4 al THREAD_2]
        THREAD_2 = [4, 5, 6] -> (5, 6)

        Faza impara:
        THREAD_1 = [1, 2, 3] -> (2, 3)
        THREAD_2 = [4, 5, 6] -> (4, 5) [THREAD_2 acceseaza elementul 4 modificat anterior de THREAD_1]
         
        Din acest motiv este nevoie sa se foloseasca o bariera la sfarsitul unei faze pare/impare
    

*/

void *compare(void *arg) {
    /* get index */
    int idx = *(int *) arg;
    /* based on the index get the corresponding start & end indexes after splitting the vector equally to all threads */
    int start_idx = idx * (double) N/NUM_THREADS;
    int end_idx = MIN((idx + 1) * (double) N/NUM_THREADS, N);
    
    /* starting indexes of odd and even phases */
    int start_par, start_impar;
    
    /* depending on the parity of start_index we will compute a starting index for odd phase and
    a starting index for even phase - check header */
    start_par       = compute_start_even_idx(start_idx);
    start_impar     = compute_start_odd_idx(start_idx);

    for(int i = 0; i < N; i++) {
        if(i % 2 == 0) {
            for(int j = start_par; j < end_idx; j+=2) {
                if(!in_vector_limits(j + 1, N)) {
                    continue;
                }
                
                if(v[j] > v[j + 1]) {
                    swap(&v[j], &v[j + 1]);
                }
            }
        } else {
            for(int j = start_impar; j < end_idx; j+=2) {
                if(!in_vector_limits(j + 1, N)) {
                    continue;
                }

                if(v[j] > v[j + 1]) {
                    swap(&v[j], &v[j + 1]);
                }
            }            
        }
        pthread_barrier_wait(&barrier); 
    }
    pthread_exit(NULL);
}

void solve_oets() {
    /* thread vector and thread data - each thread will receive its index */
    pthread_t threads[NUM_THREADS + 1];
    int threads_data[NUM_THREADS + 1];

    /* the barrier would be used for case described in (A) */
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    /* create threads */
    for(int i = 0; i < NUM_THREADS; i++) {
        threads_data[i] = i;
        int r = pthread_create(&threads[i], NULL, compare, (void *) (&threads_data[i]));
        /* check for possible errors */
        if (r) {
            printf("Error while creating thread!");
            exit(-1);
        }       
    }
    /* join threads */
    for (int j = 0; j < NUM_THREADS; j++) {
        int r = pthread_join(threads[j], NULL);
        /* check for possible errors */
        if (r) {
            printf("Error while joining!");
            exit(-1);
        }
    }

    /* free barrier */
    pthread_barrier_destroy(&barrier);
}

int main(int argc, char **argv) {
    /* used for getting start time */
    gettimeofday(&start, NULL);

    /* check correct arguments */
    if(argc != ARGC) {
        printf("Invalid parameters! Try: ./serial <file.in>");
        return -1;
    }

    /* read input */
    read_input_data(argv[1]);
    
    if(N == 1) {
        print_output();
        free_memory();
        return 0;        
    }

    /* solve OETS */
    solve_oets();

    /* print result */
    print_output();

    /* free used memory */
    free_memory();

    /* compute execution time */
    gettimeofday(&end, NULL);
    double elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;

    /* print execution time to stderr*/
    fprintf(stderr, "%f\n", elapsedTime);
}