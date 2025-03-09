from ctypes import *
import time

even_counter = CDLL('./practice ten.dll')

array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
array_ctype = (c_int * len(array))(*array)

even_counter.countEvenNumbers.argtypes = [POINTER(c_int), c_int]
even_counter.countEvenNumbers.restype = c_int

def run_iterations(iterations):
    start_time = time.time()

    for _ in range(iterations):
        even_count = even_counter.countEvenNumbers(array_ctype, len(array))
    
    end_time = time.time()
    time_taken = end_time - start_time

    print(f'The number of even numbers in the array: {even_count}')
    print(f'Time taken for {iterations} iterations: {time_taken:.6f} seconds')

run_iterations(1000000)







