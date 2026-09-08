# Алгоритм поиск количества дубликатов в одномерном массиве
import time
import random

arr = [random.randint(1, 100000) for _ in range(10000)]
def my_func(arr):
    count = 0
    for i in range(len(arr)):
        for j in range(i+1, len(arr)):
            if arr[i] == arr[j]:
                count+=1
    return count
start = time.time()
c = my_func(arr)
finish = (time.time() - start) * 1000
print(f"Количество дубликатов в массиве {c}")
print(f"Время работы алгоритма на Python: {finish:.2f} миллисекунд")