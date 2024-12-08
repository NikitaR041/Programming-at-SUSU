#pragma once
#ifndef _GENERATORARITHMETICS_HPP_
#define _GENERATORARITHMETICS_HPP_
#include <iostream>
#include "ConsoleInterface.hpp"

//Класс для создания узлов(листов) в генерации арифметического выражения
static constexpr double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

struct Node {
    short int value; //Значение в узле типа short int
    char sym; //Оператор (например, '+', '-', '*', '/', '-(-)')
    std::unique_ptr<Node> left; //Левый узел(лист)
    std::unique_ptr<Node> right; //Правый узел(лист)

    //Первый конструктор - число
    Node(short int value) : value(value), sym('\0'), left(nullptr), right(nullptr) {}
    //Второй конструктор - математическая операция
    Node(char sym, Node* left, Node* right) : value(0), sym(sym), left(left), right(right) {}

    //char action() const; //Получение арифметической операции из узла
    int actionPriority() const; //Получение приоритетности

    std::string getExpression(int parentPriority) const; //Преобразование дерева в строку-выражение  -  сохранение в файл
    friend std::ostream& operator<<(std::ostream& out, const Node& node); // Переопределение оператора вывода в вывод арифметического выражения 
};

//Метод для генерации выражений
std::unique_ptr<Node> generateExpression(short int result, short int countOperation, ConsoleInterface obj);

#endif // ! _GENERATORARITHMETICS_HPP_
