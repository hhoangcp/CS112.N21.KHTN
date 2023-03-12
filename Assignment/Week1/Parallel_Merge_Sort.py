import time
import random
from multiprocessing import Pool, cpu_count

def merge(left, right):
    sorted_list = []
    
    left_size = len(left)
    right_size = len(right)
    left_curr = right_curr = 0
    
    while left_curr < left_size and right_curr < right_size:
        if left[left_curr] < right[right_curr]:
            sorted_list.append(left[left_curr])
            left_curr += 1
        else:
            sorted_list.append(right[right_curr])
            right_curr += 1
    
    if left_curr == left_size:
        sorted_list.extend(right[right_curr : ])
        
    if right_curr == right_size:
        sorted_list.extend(left[left_curr : ])
        
    return sorted_list

def sequential_merge_sort(array):
    length = len(array)
    
    if length <= 1:
        return array
    
    middle = length // 2
    
    left = sequential_merge_sort(array[ : middle])
    right = sequential_merge_sort(array[middle : ])
    
    return merge(left, right)

def parallel_merge_sort(array):
    # processes = 2 ** n <= cpu_count()
    processes = 1
    while (processes < cpu_count()):
        processes <<= 1  
    if processes > cpu_count():
        processes >>= 1
        
    # Creates a pool
    pool = Pool(processes = processes)

    # Split the initial array into partitions, and perform a sequential merge sort across each partition.
    length = len(array) // processes
    results = []
    for i in range(processes):
        if i < processes - 1:
            results.append(array[i * length : (i + 1) * length])
        else:
            results.append(array[i * length : ])
            
    results = pool.map(sequential_merge_sort, results)
        
    # Each partition is now sorted - we now just merge them
    while len(results) > 1:
        results = [merge(results[i], results[i + 1]) for i in range(0, len(results), 2)]
                
    return results[0]

if __name__ == '__main__':
    # Create a random array with length = 400000
    length = 400000
    unsorted_array = [random.randint(0, 1e9) for n in range(length)]  
          
    # Test
    for sort in parallel_merge_sort, sequential_merge_sort:
        start = time.time()
        sorted_array = sort(unsorted_array)
        end = time.time()
        print(sort.__name__, end - start, sorted(unsorted_array) == sorted_array)
