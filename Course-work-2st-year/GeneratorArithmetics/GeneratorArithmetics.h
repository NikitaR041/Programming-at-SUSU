#pragma once
#include <iostream>

//Класс для создания узлов(листов) в генерации арифметического выражения
class Node {
    short int value; //Значение в узле типа short int
    char sym; //Оператор (например, '+', '-', '*', '/', '-(-)')
    std::unique_ptr<Node> left; //Левый узел(лист)
    std::unique_ptr<Node> right; //Правый узел(лист)

    //Первый конструктор - число
    Node(short int value) : value(value), sym('\0'), left(nullptr), right(nullptr) {}
    //Второй конструктор - математическая операция
    Node(char sym, Node* left, Node* right) : value(0), sym(sym), left(left), right(right) {}

    char action() const; //Получение арифметической операции из узла
    int actionPriority() const; //Получение приоритетности

    std::string getExpression(); //Преобразование дерева в строку-выражение  -  сохранение в файл
    friend std::ostream& operator<<(std::ostream& out, const Node& node); // Переопределение оператора вывода в вывод арифметического выражения 
};

//Основной метод, возвращающий указатель на корневой узел дерева, которое представляет сгенерированное выражение
std::unique_ptr<Node> generateExpression(short int result, short int countOperation,short int minValue, short int maxValue);
