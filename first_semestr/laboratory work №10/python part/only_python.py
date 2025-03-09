import time

def calculate_even_n_times(N):

    start_time = time.time()

    for i in range(N+1):
        
        def count_even_numbers(array):
        
            count = 0
            for num in array:
                if num % 2 == 0:
                    count += 1
            return count
        
        array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
        even_count = count_even_numbers(array)

        # print(f'The number of even numbers in the array: {even_count}')

    end_time = time.time()
    time_taken = end_time - start_time

    print(f'The number of even numbers in the array: {even_count}')
    print(f'Time taken for {i} iterations: {time_taken:.6f} seconds')

calculate_even_n_times(1000000)

