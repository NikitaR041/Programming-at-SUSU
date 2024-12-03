#pragma once
#include <iostream>

//Класс для создания узлов(листов) в генерации арифметического выражения
struct Node {
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

std::string Node::getExpression() {
	//Делаем обход с корня и составляем выражение
	if (left == nullptr && right == nullptr) {
		return std::to_string(value); //Возвращаем значение
	}

	//Далее делаем обход по узлам и листам



}

std::ostream& operator>>(std::ostream& out, const Node& node) {
	return out << node.getExpression();
}

//Основной метод, возвращающий указатель на корневой узел дерева, которое представляет сгенерированное выражение
//Убрал параметры short int minValue, short int maxValue, т.к. можно получить из настроек 
//Третий параметр ConsoleInterface obj нужен для того, чтобы брать из созданного экземпляра свойства
std::unique_ptr<Node> generateExpression(short int result, short int countOperation, ConsoleInterface obj) {
    //Шаг 6 | Возвраем лист - число
    if (countOperation == 0) {
        return std::make_unique<Node>(result);
    }

    //Создадим объекты, который нужны для алгоритма
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    short int leftValue;
	short int rightValue;
	//Шаг 1 | Выбираем арифметический знак, который ввёл пользователь 
	std::string operations = obj.getSymbols(); //Передаем те знаки, который пользователь выбрал
	char operation;
    while(true) {
		//Выбор арифметического знака предсказуем
		operation = operations[rand() % operations.length()]; //Рандомно выбираем один из арифметических знаков
		//Шаг 2 | Выбираем число в указанном диапазоне - это 1 операнд | Тестовая версия
		leftValue = static_cast<int>((rand() * fraction * (obj.getRangeNumMax() - obj.getRangeNumMin() + 1) + obj.getRangeNumMin()));

		switch(operation) {
			case '+': rightValue = result - leftValue; break;
			case '-': rightValue = leftValue - result; break;
			case '*': rightValue = result / leftValue; break;
			case '/': rightValue = leftValue / result; break;
			default: rightValue = 0;
		}

		//Шаг 3 | Проверка, если rightValue НЕ выходит за указанный диапазон
		if (rightValue >= obj.getRangeNumMin() && rightValue <= obj.getRangeNumMax()) {
			break;
		}//Иначе заного перегенерируем
	}

	//Шаг 4 | Выбрать случайно N от 0 до общЧислоДействий-1 для разложения 1-го операнда
	short int N = countOperation - 1;
	//short int leftOperations = rand() * fraction * countOperation;
	//Шаг 5 | Выбрать случайно M от 0 до общЧислоДействий-N-1 для разложения 2-го операнда
	short int M = countOperation - N - 1;
	//short int rightOperations = countOperation - leftOperations - 1;
	
	//Создаем следующие узлы(листы)
	std::unique_ptr<Node> leftNode;
	std::unique_ptr<Node> rightNode;

	//Node leftNode = 
	if (N > 0) {
		leftNode = generateExpression(leftValue, N, obj);
	}
	else {
		leftNode = std::make_unique<Node>(leftValue); // Просто число
	}

	if (M > 0) {
		rightNode = generateExpression(rightValue, M, obj);
	}
	else {
		rightNode = std::make_unique<Node>(rightValue); // Просто число
	}
	
	//Шаг 7 | Возвращаем узел - арифметическая операция - экземпляр
	return std::make_unique<Node>(operation, leftNode.release(), rightNode.release());	
}

//Временно реализуем здесь методы, а про модуль GeneratorArithmetics.cpp забудем:
