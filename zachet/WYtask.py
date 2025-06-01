def divide_and_conquer(arr, left, right):
    
    if left == right:
        return arr[left]
    
    mid = (left + right) // 2

    left_max = divide_and_conquer(arr, left, mid)
    right_max = divide_and_conquer(arr, mid + 1, right)
    
    lev_prefix = float('-inf')
    current_sum = 0
    for i in range(mid, left - 1, -1):
        current_sum += arr[i]
        if current_sum > lev_prefix:
            lev_prefix = current_sum
    
    prav_prefix = float('-inf')
    current_sum = 0
    for i in range(mid + 1, right + 1):
        current_sum += arr[i]
        if current_sum > prav_prefix:
            prav_prefix = current_sum

    cross_max = lev_prefix + prav_prefix
 
    return max(left_max, right_max, cross_max)

n = int(input().strip())
arr = list(map(int, input().split()))
while len(arr) < n:
    arr += list(map(int, input().split()))
arr = arr[:n]

if n <= 0:
    print(0)

else:
    result = divide_and_conquer(arr, 0, n - 1)
    print(result)