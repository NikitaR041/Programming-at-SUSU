import numpy as np
import matplotlib.pyplot as plt

# Параметры
N = 10  # Количество членов ряда Фурье
L = 1   # Полупериод функции
T = 2 * L  # Период функции

# Коэффициенты A_n и B_n
def A_n(n):
    return 2 / (np.pi**2 * n**2)

def B_n(n):
    return (1 / (np.pi * n)) * (-2 + (-1)**n)

# Частичная сумма ряда Фурье
def S_N(x, N):
    sum_f = 0.5  # A_0 / 2 = 1/2
    for n in range(1, N + 1):
        sum_f += A_n(n) * np.cos(n * np.pi * x / L) + B_n(n) * np.sin(n * np.pi * x / L)
    return sum_f

# Создаем сетку точек на [-3, 3]
x = np.linspace(-3, 3, 1000)
y = S_N(x % T - L, N)  # Периодическое продолжение

# График
plt.figure(figsize=(10, 6))
plt.plot(x, y, label=f'Частичная сумма S_N(x), N={N}', color='b')
plt.title("График суммы ряда Фурье на отрезке [-3, 3]")
plt.xlabel("x")
plt.ylabel("S_N(x)")
plt.grid()
plt.legend()
plt.show()
