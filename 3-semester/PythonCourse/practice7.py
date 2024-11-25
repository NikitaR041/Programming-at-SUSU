#Романов Никита ЕТ-212 | Работа с классами 

#Задание 1 
#Создайте класс «Мебель» с полями «Марка», «Название», «Цена» и методом для вывода подробной информации о предмете.

class Furniture():
    def __init__(self, mark, name, price):
        self.mark = mark
        self.name = name
        self.price = price
    #Метод вывода подробной информации
    def display_console(self):
        print(f"Марка мебеля: {self.mark} \n Название мебели {self.name} \n Цена {self.price} \n")
    
obj1 = Furniture("Germany", "Leran", 8500)
obj2 = Furniture("Russia", "Mishka", 5000)

Furniture.display_console(obj1)
Furniture.display_console(obj2)

#Задание 2
# Николаю требуется проверить, возможно ли из представленных отрезков условной длины сформировать треугольник. 
# Для этого он решил создать класс TriangleChecker, принимающий только положительные числа. 
# С помощью метода is_triangle() возвращаются следующие значения (в зависимости от ситуации): 
# – Ура, можно построить треугольник!; 
# – С отрицательными числами ничего не выйдет!; 
# – Нужно вводить только числа!; 
# – Жаль, но из этого треугольник не сделать.

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
        
#Задание 3
# Создать класс «Одномерный массив» 
# Класс содержит поле для задания количества элементов и поле для хранения элементов массива. 
# Методы: 
# – ввод и вывод даных, 
# – поиск максимального и минимального элементов, 
# – сортировка массива, 
# – поиск суммы элементов,
# – перегрузка оператора + (добавление элемента) 
# – перегрузка оператора * умножение элементов массива на число.

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


