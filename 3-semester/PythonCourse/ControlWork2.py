#Вариант 18 - Романов Никита ЕТ-212

#Задание 1
#Построить график функции одной переменной, x принадлежит [-5;5]. 
#Оформить графики

import numpy as np
import matplotlib.pyplot as plt
import sympy as sp

#График
#y= –0,00185x**5+0,008x**4+0,27x**3–1,01x**2–4,80x+3,56 

x = np.linspace(-5, 5)
y = -0.00185*(x**5)+0.008*(x**4)+0.27*(x**3)-1.01*(x**2)-4.80*x+3.56 
plt.plot(x,y,'k--')
plt.xlabel('x')  
plt.ylabel("f(x)")  
plt.title("f(x)=-0.00185*(x**5)+0.008*(x**4)+0.27*(x**3)-1.01*(x**2)-4.80*x+3.56")  
plt.grid(True)  # Включаем сетку на графике
plt.show()

#Задание 2
# Построить 2 графика в одном окне, так, чтобы у каждого графика была своя область построения. 
# Оформить графики
# x принадлежит [–2;2], шаг 01: 
# y = sin(2x)*cos(3x) – cos2(x) 
# z = (1 + x)/(1+ 2x3) при х >1 


#Диапазон с шагом 0.1
x = np.arange(-2, 2.1, 0.1)

# Первая функция: y = sin(2x)*cos(3x) - cos^2(x)
y = np.sin(2 * x) * np.cos(3 * x) - np.cos(x)**2
# Вторая функция: z = (1 + x) / (1 + 2x^3) при x > 1
x2 = x[x > 1]
z = (1 + x2) / (1 + 2 * x2**3)

# Первый график
plt.subplot(1, 2, 1)
plt.plot(x, y, label='y = sin(2x)*cos(3x) - (cos(x))^2', color='blue')
plt.title('График функции y', fontsize=14)
plt.xlabel('x', fontsize=12)
plt.ylabel('y', fontsize=12)
plt.grid(True)
plt.legend()

# Второй график
plt.subplot(1, 2, 2)
plt.plot(x2, z, label='z = (1 + x) / (1 + 2x^3)', color='green')
plt.title('График функции z', fontsize=14)
plt.xlabel('x', fontsize=12)
plt.ylabel('z', fontsize=12)
plt.grid(True)
plt.legend()

# Отображение графиков
plt.show()

#Задание 3
# Написать 2 класса
# 1. 
# Николаю требуется проверить, возможно ли из представленных отрезков условной длины сформировать треугольник. 
# Для этого он решил создать класс TriangleChecker, принимающий только положительные числа. 
# С помощью метода is_triangle() возвращаются следующие значения (в зависимости от ситуации): 
# – Ура, можно построить треугольник!; 
# – С отрицательными числами ничего не выйдет!; 
# – Нужно вводить только числа!; 
# – Жаль, но из этого треугольник не сделать. 
# 
# 
# 2. Создать класс «Одномерный массив» 
# Класс содержит поле для задания количества элементов и поле для хранения 
# элементов массива. 
# Методы: 
# – ввод и вывод даных, 
# – поиск максимального и минимального элементов, 
# – сортировка массива, 
# – поиск суммы элементов 
# – перегрузка оператора + (добавление элемента) 
# – перегрузка оператора * умножение элементов массива на число.

# Number 1
class TriangleChecker():
    def __init__(self, line1, line2, line3):
        self.line1 = line1
        self.line2 = line2
        self.line3 = line3
    
    def is_triangle(self):
        if(isinstance(self.line1, int) == False or isinstance(self.line2, int) == False or isinstance(self.line3, int) == False):
            print("Нужно вводить только числа!")
        elif(self.line1 < 0 or self.line2 < 0 or self.line3 < 0):
            print("С отрицательными числами ничего не выйдет!")
        elif((self.line1 >= self.line2+self.line3) or (self.line2 >= self.line1+self.line3) or (self.line3 >= self.line1+self.line2)):
            print("Жаль, но из этого треугольник не сделать")
        else:
            print("Ура, можно построить треугольник!")

obj1 = TriangleChecker('123', '12412', '3123')
obj2 = TriangleChecker(12, 14, 27)
obj3 = TriangleChecker(3, 4, 5)
obj4 = TriangleChecker(-1, 4, -4)

TriangleChecker.is_triangle(obj1)
TriangleChecker.is_triangle(obj2)
TriangleChecker.is_triangle(obj3)
TriangleChecker.is_triangle(obj4)

#Number 2
class OneLineArray():
    #Конструктор
    def __init__(self, countElem):
        self.countElem = countElem
        self.mass = [0] * countElem #Инициализация массива нулями

    #Ввод данных
    def inputData(self):
        is_working = True
        i = 0
        print("Вы сейчас находитесь на этапе ввода элементов в массив: ")
        while(is_working):
            if (i == self.countElem): 
                is_working = False
                break
            c = input("Введите число для вашего элемента: ")
            if(isinstance(int(c), int) == False):
               is_working = False
               print("Ошибка! Перезапустите заного компиляцию программы!")
               break
            self.mass[i] = int(c)
            i += 1

    
    #Вывод данных
    def printData(self):
        print(f"Вот ваш массив: {self.mass}")
    
    #Поиск максимального элемента
    def maxElem(self):
        print(f"Максимальный элемент в массиве: {max(self.mass)}")

    #Поиск минимального элемента
    def minElen(self):
        print(f"Минимальный элемент в массиве: {min(self.mass)}")

    #сортировка массива
    def sortMass(self):
        self.mass.sort()
        print(f"Вот ваш отсортированный массив: {self.mass}")

    #поиск суммы элементов
    def sumElem(self):
        print(f"Сумма элементов массива: {sum(self.mass)}")

    #перегрузка оператора + (добавление элемента)
    def __add__(self, value):
        self.mass.append(value) 
        self.countElem += 1
        return self
        
    #перегрузка оператора * умножение элементов массива на число
    def __mul__(self, number):
        for i in range(self.countElem):
            self.mass[i] *= number
        return self

c = int(input("Ввдеите размер массива: "))
obj = OneLineArray(c)
obj.inputData()
obj.printData()
obj.maxElem()
obj.minElen()
obj.sumElem()
obj.sortMass()

num1 = int(input("Придумайте число, чтобы добавить его в конец массива: "))
obj += num1
obj.printData()

num2 = int(input("Придумайте число, чтобы каждый элемент домножился на какое-нибудь число: "))
obj = obj * num2
obj.printData()

