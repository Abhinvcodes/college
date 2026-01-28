def optimized_bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break
    return arr
n = int(input('how many numbers '))
numbers = [int(input(f'enter {i+1} num ')) for i in range(n)]
sorted_numbers = optimized_bubble_sort(numbers)
print(f"Sorted list: {sorted_numbers}")
