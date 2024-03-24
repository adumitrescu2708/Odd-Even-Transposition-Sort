import random
import subprocess

NUMBER_OF_TESTS = 10
N_MAX           = 100000
X_MAX           = 5000
FILE            = "test"
IN_EXT          = ".in"
REF_EXT         = ".ref"
IN_DIR          = "./in/"
OUT_DIR         = "./ref/"

SERIAL          = "./../serial"

def generate_solve_test(input_writer):
    N = random.randint(0, N_MAX)
    v = []
    input_writer.write(str(N) + "\n")
    
    for i in range (0, N):
        X = random.randint(0, X_MAX)
        input_writer.write(str(X) + " ")
        v.append(X)
    input_writer.close
        
def solve_test(test_input_name,test_reff_name, time_serial):
    print(f"Solving test: {test_input_name} -> {test_reff_name}")

    try:
        time = open(time_serial, "w")
        reff = open(test_reff_name, "w")
        subprocess.run(SERIAL + " " + test_input_name, stdout=reff, stderr = time, shell=True)
        reff.close
        print("Test solved successfully.")
    except Exception as e:
        print("An unexpected error occurred:", e)
    
def main(): 
    for i in range(1, NUMBER_OF_TESTS + 1):
        test_input_name = IN_DIR + FILE + str(i) + IN_EXT
        input_writer = open(test_input_name, "w")
        generate_solve_test(input_writer)
  
    for i in range(1, NUMBER_OF_TESTS + 1):
        time_serial = "../execution_times/serial/" + FILE + str(i) + REF_EXT
        test_ref = OUT_DIR + FILE + str(i) + REF_EXT
        test_input_name = IN_DIR + FILE + str(i) + IN_EXT
        solve_test(test_input_name, test_ref, time_serial)
    
        
  
if __name__=="__main__": 
    main() 