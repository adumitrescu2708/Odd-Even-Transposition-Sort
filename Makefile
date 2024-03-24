build: serial oets_pthread oets_openmp oets_openmpi oets_hybrid_1 oets_hybrid_2

serial: odd_even_transposition_serial.c
	gcc odd_even_transposition_serial.c -o serial

oets_pthread: odd_even_transposition_pthreads.c
	gcc odd_even_transposition_pthreads.c -lpthread -o oets_pthread

oets_openmpi: odd_even_transposition_MPI.c
	mpicc odd_even_transposition_MPI.c -o oets_openmpi

oets_openmp: odd_even_transposition_MP.c
	gcc odd_even_transposition_MP.c -fopenmp -o oets_openmp

oets_hybrid_1: odd_even_transposition_hybrid_1.c
	mpicc odd_even_transposition_hybrid_1.c -fopenmp -o oets_hybrid_1 -lmpi

oets_hybrid_2: odd_even_transposition_hybrid_2.c
	mpicc odd_even_transposition_hybrid_2.c -lpthread -o oets_hybrid_2

clean:
	rm serial oets_pthread oets_openmp oets_openmpi oets_hybrid_1 oets_hybrid_2