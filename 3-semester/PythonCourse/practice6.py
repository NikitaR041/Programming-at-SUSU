#Романов Никита ET-212 | Практическая работа 7. Работа с библиотеками

import numpy as np
import matplotlib.pyplot as plt
import sympy as sp

# --- 1 ---
#Создать вектор (одномерный массив) размера 10, заполненный нулями

vec1 = np.zeros(10, dtype="int")
print(vec1)

# --- 2 ---
#Создать вектор размера 10, заполненный единицами

vec2 = np.ones(10, dtype="int")
print(vec2)

# --- 3 ---
#Создать вектор размера 10, заполненный нулями, но пятый элемент равен 1

vec3 = np.zeros(10, dtype="int")
vec3[4] = 1
print(vec3)

# --- 4 ---
#Создать вектор со значениями от 10 до 49
s = [i for i in range(10, 50, 1)]
vec4 = np.array(s)
print(vec4)

# --- 5 ---
#Найти индексы ненулевых элементов в [1,2,0,0,4,0]

vec5 = np.array([1,2,0,0,4,0])
for i in range(vec5.size):
    if vec5[i] != 0:
        print(i)

# --- 6 ---
#Создать 3x3 единичную матрицу

vec6 = np.zeros((3,3), dtype="int")
print(vec6)

# --- 7 ---
#Создать массив 3x3x3 со случайными значениями

vec7 = np.random.random((3,3,3))
print(vec7)

# --- 8 ---
#Создать массив 10x10 со случайными значениями, найти минимум и максимум

vec8 = np.random.random((10,10))
print(f"Максимальное значене в массиве: {vec8.max()}")
print(f"Минимальное значение в массиве: {vec8.min()}")

# --- 9 ---
#Создать 8x8 матрицу и заполнить её в шахматном порядке

vec9 = np.zeros((8,8), dtype="int")
for i in range(8):
    for j in range(8):
        if (i+j)%2 == 1:
            vec9[i, j] = 1
print(vec9) 

# --- 10 ---
#Перемножить матрицы 5x3 и 3x2

A = np.array([[1,2,3], [4,5,6], [8,9,10], [11,12,13], [14,15,16]])
B = np.array([[1,2],[3,4],[5,6]])
print(np.dot(A,B))

# --- 11 ---
#Дан массив, поменять знак у элементов, значения которых между 3 и 8
vec11 = np.array([[1,2],[3,4],[5,6],[7,8], [9,10]])
for i in range(vec11.shape[0]):
    for j in range(vec11.shape[1]):
        if(vec11[i,j] >= 3 and vec11[i,j] <= 8):
            vec11[i,j] = vec11[i,j] * (-1)
    
print(vec11)

# --- 12 ---
#Создать вектор размера 10 со значениями от 0 до 1, не включая ни то, ни другое

#.linspace () в Python используется для генерации последовательности чисел в линейном пространстве с одинаковым размером шага.

vec12 = np.linspace(0, 1, 12)[1:-1]
print(vec12)

# --- 13 ---
#Отсортировать вектор

vec13 = np.array([5,2,1,4,5,2,1,2,2,4,5,6,2,0])
veec13 = np.array([[5,1],[4,2],[8,7]])
vec13.sort()
veec13.sort(1) #Аргумент в методе sort(1) означает по-какому столбцу сортировать вектор veec13 
print(vec13)
print(veec13)

# --- 14 ---
#Заменить максимальный элемент на ноль

#Функция .where(arr == i) Здесь arr — это массив NumPy, а i — элемент, для которого нужно получить индекс.

vec14 = np.array([5,2,1,4,5,2,1,2,2,4,10,6,2,1])
if(0<= vec14.max() < 1000):
    index = np.where(vec14 == vec14.max())
    vec14[index] = 0

print(vec14)

# --- 15 ---
#Замените все нечетные числа в одномерном массиве на -1

vec15 = np.array([5,2,1,4,5,2,1,2,2,4,10,6,2,1])
for i in range(vec15.size):
    if vec15[i] % 2 != 0:
        vec15[i] = -1

print(vec15)

# --- 16 ---
# Изобразить функцию f(x) = 1/(10+x^3), x принадлежит [0;20;0.1]

x = np.linspace(0, 20, int((20 - 0) / 0.1) + 1)
y = 1/(10+x**3)
plt.plot(x,y,'k--')
plt.xlabel('x')  
plt.ylabel("f(x)")  
plt.title("f(x) = 1/(10+x^3)")  
plt.grid(True)  # Включаем сетку на графике
plt.show()

# --- 17 ---
# Изобразить функцию f(x) = sin(5x)*cos(x), x принадлежит [0;20;0.1]

x = np.linspace(0, 20, int((20 - 0) / 0.1) + 1)
y = np.sin(5*x)*np.cos(x)
plt.plot(x,y,'k--')
plt.xlabel('x')  
plt.ylabel("f(x)")  
plt.title("f(x) = 1/(10+x^3)")  
plt.grid(True)  # Включаем сетку на графике
plt.show()

# --- 18 ---
#Напишите программу поиска производной второго порядка для уравнения f = 2a^2 + a*b + b^2

x = sp.symbols('x')
y = sp.symbols('y')

f = 2*(x**2)+x*y+(y**2)

dif1 = sp.diff(f, y) #Пусть частная производная по букве Y
dif2 = sp.diff(dif1, x) #Пусть частная производная по букве X

print(dif1)
print(dif2)

# --- 19 ---
#Написать функцию поиска производной n-го порядка. (1)
#Параметрами будет сама функция, которую пользователь задает и порядок вычисления производной. (2)
#Построить графики функции и всех производных. (3)

# Функция для вычисления производной n-го порядка (1)
def df(func, D, n):
    func_example = func
    for _ in range(n):
        func_example = sp.diff(func_example, D)
    return func_example

n = int(input("Введите n - порядок производной: "))
user_st = input("Введите уравнение [например: x**2 или x+2*sin(x)]: ")

x = sp.symbols('x')
func = sp.sympify(user_st)

# Вычисляем производные вплоть до n-го порядка
derivatives = [func]  # Включаем саму функцию
for i in range(1, n + 1):
    derivatives.append(df(func, x, i))

# Графики функции и её производных (2)-(3)
x_vals = np.linspace(-10, 10, 400)  # Определяем диапазон для графика
plt.figure(figsize=(10, 6))

# Построение графиков для функции и производных
for index, deriv in enumerate(derivatives):
    # Преобразуем символьное выражение в числовую функцию для графика
    func_np = sp.lambdify(x, deriv, "numpy")
    y_vals = func_np(x_vals)
    
    # Название линии на графике
    label = f"{index}-я производная" if index > 0 else "Функция"
    plt.plot(x_vals, y_vals, label=label)

# Оформление графика
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.title(f"Функция и её производные до {n}-го порядка")
plt.grid(True)
plt.show()

# --- 20 ---
#Напишите функцию поиска точного значения производной f(x) в заданной точке,
#параметры которой будет функция, заданная пользователем и точка х.

def search_exact_value(func_user, tochka):
    x = sp.symbols('x') #Область дифференцированния
    func = sp.sympify(func_user)# Преобразуем строку в математическое выражение SymPy
    derivative = sp.diff(func, x)
    derivative_value = derivative.subs(x, tochka)    
    return derivative_value

func_user = input("Введите вашу фунцию [Например: sin(x)] ")
tochka = int(input("Введите конктретную точку для вашей функции: "))

print(search_exact_value(func_user, tochka))