import subprocess

NUMBER_OF_TESTS = 10
FILE            = "test"

IN_EXT          = ".in"
OUT_EXT         = ".out"
REF_EXT         = ".ref"

IN_DIR          = "./in/"
OUT_DIR         = "./out/"
REF_DIR         = "./ref/"

PTHREADS        = "../oets_pthread"
OPEN_MPI        = "../oets_openmpi"
OPEN_MP         = "../oets_openmp"
HIBRID_1        = "../oets_hybrid_1"
HIBRID_2        = "../oets_hybrid_2"
MODES = [PTHREADS, OPEN_MP, OPEN_MPI, HIBRID_1, HIBRID_2]
MODES_NAMES = ["PTHREADS", "OPEN-MP", "OPEN-MPI", "HIBRID MPI-MP", "HIBRID MPI-PTHREADS"]

RUN_MPI = "mpirun -np 4 "
def check(input_filename, output_filename, ref_filename, filename):
    idx = 0
    for mode in MODES:
        print("Checking " + MODES_NAMES[idx] + "...", end = " ")
        time = None
        if idx == 1:
            time = "../execution_times/openmp/" + filename
        if idx == 0:
            time = "../execution_times/pthreads/" + filename
        if idx == 2:
            time = "../execution_times/openmpi/" + filename
        if idx == 3:
            time = "../execution_times/hibrid_mp_mpi/" + filename
        if idx == 4:
            time = "../execution_times/hibrid_pthreads_mpi/" + filename
        time_file = open(time, "w")
        args = [input_filename]        
        try:
            with open(output_filename, "w") as output:
                if idx == 2:
                    subprocess.run(['mpirun', '-np', str(4), './../oets_openmpi', input_filename], stdout=output, stderr=time_file, check=True)
                else:
                    if idx == 3:
                        subprocess.run(['mpirun', '-np', str(2), './../oets_hybrid_1', input_filename], stdout=output, stderr=time_file, check=True)
                    else:
                        subprocess.run([mode] + args, stdout=output, stderr=time_file)
        except Exception as e:
            print("An unexpected error occurred:", e)
        
        reff_reader = open(ref_filename, "r")
        output_reader = open(output_filename, "r")
        import re

        reff = ([int(num) for num in re.findall('\d+', reff_reader.read())])   
        output = [int(num) for num in re.findall('\d+', output_reader.read())]
        idx += 1

        if reff != output:
            print("FAIL\n")
        else:
            print("PASS\n")


def main(): 
    for i in range(1, NUMBER_OF_TESTS):
        input_filename = IN_DIR + FILE + str(i) + IN_EXT
        output_filename = OUT_DIR + FILE + str(i) + OUT_EXT 
        ref_filename = REF_DIR + FILE + str(i) + REF_EXT
        time_ref = FILE + str(i) + REF_EXT
        print("Running test" + str(i) + "...\n")
        check(input_filename, output_filename, ref_filename, time_ref)
        
  
if __name__=="__main__": 
    main() 