nume:   Dumitrescu Alexandra  
grupa:  343C1  
tema:   Odd Even Transposition Sort  

## Odd Even Transposition Sort

### Cuprins
- Surse
- Teste - Checker
- Varianta seriala
- Varianta - pthreads
- Varianta - OpenMP
- Varianta - OpenMPI
- Varianta - OpenMP - OpenMPI - hibrid #1
- Varianta - Pthreads - OpenMPI - hibrid #2
- Rezultate  
- Linkuri utile


### Surse
<pre>
|_ execution_times/                   -> folder in care checkerul creaza cate un fisier pentru fiecare metoda  
|        |                                si printeaza timpii de executie, care vor fi folositi in etapa 2  
|        |_ openmp/                    -> fiecare metoda de rezolvare are cate un folder separat
|        |_ openmpi/
|        |_ pthreads/
|        |_ serial/
|        |_ hibrid_mp_mpi/
|
|_ tests/
|       |_ in/  -> folder in care test_generator.py genereaza random datele de intrare
|       |_ ref/ -> dupa ce s-au generat datele de intrare, se apeleaza varianta seriala si se scriu referinte aici
|       |_ out/
|       |_ test_generator.py -> genereaza folderele in/ ref/
|       |_ checker.py -> verifica metodele si scrie timpii in execution_times/
|
|_ Makefile
|_ odd_even_transposition.h -> cuprinde functii utilizate de toate variantele
|_ odd_even_transposition_serial.c
|_ odd_even_transposition_pthreads.c
|_ odd_even_transposition_MP.c
|_ odd_even_transposition_MPI.c

</pre>


### Teste - Checker
**Pentru generarea de teste am scris tests/test_generator.py** unde se genereaza 10 teste, primind ca parametru dimensiunea maxima a datelor.  
Astfel, pentru ultima etapa a proiectului se va putea modifica cu usurinta N_MAX, X_MAX. Scriptul genereaza random date pe care  
le scrie in /tests/in iar apoi apeleaza varianta seriala si obtine timpii pentru varianta seriala pe care ii scrie in /execution_times/serial  
si datele sortate pe care le scrie in tests/ref.  

**Pentru validarea testelor am scris tests/checker.py** unde se apeleaza fiecare metoda implementata pe datele de intrare generate se afiseaza  
PASS/FAIL daca rezultatele coincid si se mai testeaza o data si sa fie vectorul sortat si se scriu timpii de rulare in execution_times/metoda/test.ref 

**Rularea celor 2 scripturi se face astfel** - mai intai se da make in root apoi:
<pre>
cd tests/
python3 checker.py
</pre>



### Varianta seriala
Pentru varianta seriala am folosit pseudocodul descris in sursele [1], [2].

### Varianta pthreads
Pentru varianta in care am paralelizat folosind pthreads am folosit urmatoarea idee:  
1) Se imparte vectorul initial la NUM_THREADS threaduri in mod egal  
2) Fiecare thread se va ocupa de bucata asignata lui din vectorul partajat   
3) Pot aparea probleme la capetele intervalului, deoarece un thread poate accesa cu o casuta
in plus fata de zona asignata (zona necesara altui thread la urmatoarea faza).  
Astfel, la sfarsitul unei faze pare/impare se foloseste o bariera pentru a ne asigura ca toate thread-urile si-au terminat blocurile.  

NUM_THREADS va putea fi modificat pentru analize la Tema3.


### Varianta - OpenMP
Pentru varianta in care am paralelizat folosind OpenMP am folosit urmatoarea idee:   
1) Pornind de la solutia initala seriala, m-am folosit de paralel for pentru a paraleliza  
fiecare iteratie intr-o faza para/impara  


### Varianta - OpenMPI
Pentru varianta in care am paralelizat folosind OpenMPI am folosit urmatoarea idee:   
1) Vectorul initial va fi impartit egal la numarul de procese (incluzand MASTER)  
2) Fiecare proces va calcula pentru sine indexii de start pe paritate, start pe imparitate si final  
3) Procesul MASTER va avea un pas de preprocesare in care va calcula pentru fiecare proces indexii  
mentionati anteriori si ii va retine in cate un array.  
4) Fiecare proces (incluzand MASTER) isi face modificarile in functie de paritatea fazei pe bucata sa de cod  
5) Dupa ce s-a terminat de inspectat blocul, fiecare proces trimite update-uri la MASTER  
6) MASTER merge-uieste toate updateurile  


### Varianta - OpenMP - OpenMPI - hibrid #1
Pentru varianta in care am paralelizat folosind prima varianta hibrida1 am folosit urmatoarea idee:   
1) Pornind de la varianta de OpenMP am paralelizat for-urile in care fiecare proces isi modifica
portiunea sa asiignata din vector.

### Varianta - Pthreads - OpenMPI - hibrid #2
Pentru varianta in care am paralelizat folosind prima varianta hibrida2 am folosit urmatoarea idee:  
1) Am modificat varianta OpenMPI prin crearea unor threaduri care sa proceseze in paralel
portiunea asignata din vector


### Rezultate
<pre>
Running test1...

Checking PTHREADS... PASS

Checking OPEN-MP... PASS

Checking OPEN-MPI... PASS

Checking HIBRID MPI-MP... PASS

Checking HIBRID MPI-PTHREADS... PASS

Running test2...

Checking PTHREADS... PASS

Checking OPEN-MP... PASS

Checking OPEN-MPI... PASS

Checking HIBRID MPI-MP... PASS

Checking HIBRID MPI-PTHREADS... PASS

Running test3...

Checking PTHREADS... PASS

Checking OPEN-MP... PASS

Checking OPEN-MPI... PASS

Checking HIBRID MPI-MP... PASS

Checking HIBRID MPI-PTHREADS... PASS

Running test4...

Checking PTHREADS... PASS

Checking OPEN-MP... PASS

Checking OPEN-MPI... PASS

Checking HIBRID MPI-MP... PASS

Checking HIBRID MPI-PTHREADS... PASS

Running test5...

Checking PTHREADS... PASS

Checking OPEN-MP... PASS

Checking OPEN-MPI... PASS

Checking HIBRID MPI-MP... PASS

Checking HIBRID MPI-PTHREADS... PASS

Running test6...

Checking PTHREADS... PASS

Checking OPEN-MP... PASS

Checking OPEN-MPI... PASS

Checking HIBRID MPI-MP... PASS

Checking HIBRID MPI-PTHREADS... PASS

Running test7...

Checking PTHREADS... PASS

Checking OPEN-MP... PASS

Checking OPEN-MPI... PASS

Checking HIBRID MPI-MP... PASS

Checking HIBRID MPI-PTHREADS... PASS

Running test8...

Checking PTHREADS... PASS

Checking OPEN-MP... PASS

Checking OPEN-MPI... PASS

Checking HIBRID MPI-MP... PASS

Checking HIBRID MPI-PTHREADS... PASS

Running test9...

Checking PTHREADS... PASS

Checking OPEN-MP... PASS

Checking OPEN-MPI... PASS

Checking HIBRID MPI-MP... PASS

Checking HIBRID MPI-PTHREADS... PASS
</pre>

### Linkuri utile
[1] https://www.sciencedirect.com/topics/computer-science/transposition-sort  
[2] https://www.geeksforgeeks.org/odd-even-transposition-sort-brick-sort-using-pthreads/   
[3] https://mobylab.docs.crescdi.pub.ro/docs/parallelAndDistributed/laboratory3/oddEvenTranspositionSort  