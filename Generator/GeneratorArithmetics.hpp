#pragma once
#ifndef _GENERATORARITHMETICS_HPP_
#define _GENERATORARITHMETICS_HPP_
#include <iostream>
#include <memory>
#include "ConsoleInterface.hpp"

//Класс для создания узлов(листов) в генерации арифметического выражения
struct Node {
    int value; //Значение в узле типа int
    char sym; //Оператор (например, '+', '-', '*', '/', '-(-)')
    std::unique_ptr<Node> left; //Левый узел(лист)
    std::unique_ptr<Node> right; //Правый узел(лист)

    //Первый конструктор - число
    Node(int value) : value(value), sym('\0'), left(nullptr), right(nullptr) {}
    //Второй конструктор - математическая операция
    Node(char sym, std::unique_ptr<Node> left, std::unique_ptr<Node> right) : value(0), sym(sym), left(std::move(left)), right(std::move(right)) {}

    int actionPriority() const; //Метод для получения приоритетности

    std::string getExpression() const;//Метод для преобразование дерева в строку-выражение
    friend std::ostream& operator<<(std::ostream& out, const Node& node); // Переопределение оператора вывода в вывод арифметического выражения 
};

//Функция для генерации выражений
std::unique_ptr<Node> generateExpression(int result, unsigned short int countOperation, ConsoleInterface obj);

#endif // ! _GENERATORARITHMETICS_HPP_
