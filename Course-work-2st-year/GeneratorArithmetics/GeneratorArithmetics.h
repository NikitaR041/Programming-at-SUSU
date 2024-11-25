#pragma once
#include <iostream>

//Разработаем предварительный класс GeneratorArithmetic
struct Node {
    short int value; //Значение в узле типа short int
    char sym; //Оператор (например, '+', '-', '*', '/', '-(-)')
    std::unique_ptr<Node> left; //Левый узел(лист)
    std::unique_ptr<Node> right; //Правый узел(лист)

    //Первый конструктор - число
    Node(short int value) : value(value), sym('\0'), left(nullptr), right(nullptr) {}
    //Второй конструктор - математическая операция
    Node(char sym, Node* left, Node* right) : value(0), sym(sym), left(left), right(right) {}
    ~Node() {}

    char action() const; //Получение арифметической операции из узла
    int actionPriority() const; //Получение приоритетности
};

class GenericArithmetics { 
    std::unique_ptr<Node> root;//Корень дерева - родитель
public:
    GenericArithmetics() : root(nullptr) {}
   
    void generateExpression(); //Основной метод для генерации дерева - генерация из полученных параметров из класса ConsoleInterface
    std::string getExpression(); //Преобразование дерева в строку-выражение  -  сохранение в файл
    friend std::ostream& operator<<(std::ostream& out, const GenericArithmetics& other); // Переопределение оператора вывода в вывод арифметического выражения 
};
