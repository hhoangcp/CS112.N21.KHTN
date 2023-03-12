import time
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

def sequential_merge_sort(*args):
    array, size = args[0] if len(args) == 1 else args
    
    if size <= 1:
        return array
    
    middle = size // 2
    
    left = sequential_merge_sort(array[ : middle], middle)
    right = sequential_merge_sort(array[middle : ], size - middle)
    
    return merge(left, right)

def parallel_merge_sort(array, size):
    # processes = 2 ** n <= cpu_count()
    processes = 1
    while (processes < cpu_count()):
        processes <<= 1  
    if processes > cpu_count():
        processes >>= 1
        
    # Creates a pool
    pool = Pool(processes = processes)

    # Split the initial array into partitions, and perform a sequential merge sort across each partition.
    results = []
    for i in range(processes):
        if i < processes - 1:
            results.append((array[i * (size // processes) : (i + 1) * (size // processes)], size // processes))
        else:
            results.append((array[i * (size // processes) : size], size - i * (size // processes)))
            
    results = pool.map(sequential_merge_sort, results)
        
    # Each partition is now sorted - we now just merge them
    while len(results) > 1:
        results = [merge(results[i], results[i + 1]) for i in range(0, len(results), 2)]
                
    return results[0]

if __name__ == '__main__':
    n = int(input('Size: '))
    unsorted_array = list(map(int, input('Array elements: ').strip().split()))[:n]
    print('')
          
    # Test
    for sort in parallel_merge_sort, sequential_merge_sort:
        start = time.time()
        sorted_array = sort(unsorted_array, n)
        end = time.time()
        
        print('Algorithm: ', sort.__name__)
        print('Array after sort: ', sorted_array)
        print('Time to sort: ', end - start)
        print('Array is sorted: ', sorted(unsorted_array) == sorted_array)
        print('')
