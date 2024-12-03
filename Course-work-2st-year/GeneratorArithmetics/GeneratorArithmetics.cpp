#include "GeneratorArithmetics.h"
#include "ConsoleInterface.h"
#include <cstdlib> // Необходимо подлючить time()
#include <string>
//Разработка методов

//Преобразование дерева в строку-выражение  -  сохранение в файл
//std::string getExpression() {
//	//После того, как вызывали функцию generateExpression
//	//if ()
//
//}
//std::string Node::getExpression() {
//
//}

// Переопределение оператора вывода в вывод арифметического выражения 
//std::ostream& operator<<(std::ostream& out, const Node& node);
//
////Убрал параметры short int minValue, short int maxValue, т.к. можно получить из настроек
//std::unique_ptr<Node> generateExpression(short int result, short int countOperation, ConsoleInterface obj) {
//	//Шаг 6 | Возвращаем лист - число
//	if (countOperation == 0) {
//		return std::make_unique<Node>(result); // Создание числового узла - экземпляра
//	}
//
//	//Следуем по инструкции алгоритма
//	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
//	short int leftValue;
//	short int rightValue;
//	//Шаг 1 | Выбираем арифметический знак, который ввёл пользователь 
//	std::string operations = obj.getSymbols(); //Передаем те знаки, который пользователь выбрал
//	char operation;
//	//char operation = operations[rand() % operations.length()]; //Рандомно выбираем один из арифметических знаков
//	while(true) {
//		//Выбор арифметического знака предсказуем
//		operation = operations[rand() % operations.length()]; //Рандомно выбираем один из арифметических знаков
//		//Шаг 2 | Выбираем число в указанном диапазоне - это 1 операнд | Тестовая версия
//		leftValue = static_cast<int>((rand() * fraction * (obj.getRangeNumMax() - obj.getRangeNumMin() + 1) + obj.getRangeNumMin()));
//
//		switch(operation) {
//			case '+': rightValue = result - leftValue; break;
//			case '-': rightValue = leftValue - result; break;
//			case '*': rightValue = result / leftValue; break;
//			case '/': rightValue = leftValue / result; break;
//			default: rightValue = 0;
//		}
//
//		//Шаг 3 | Проверка, если rightValue НЕ выходит за указанный диапазон
//		if (rightValue >= obj.getRangeNumMin() && rightValue <= obj.getRangeNumMax()) {
//			break;
//		}//Иначе заного перегенерируем
//	}
//
//	//Шаг 4 | Выбрать случайно N от 0 до общЧислоДействий-1 для разложения 1-го операнда
//	short int leftOperations = rand() * fraction * countOperation;
//	//Шаг 5 | Выбрать случайно M от 0 до общЧислоДействий-N-1 для разложения 2-го операнда
//	short int rightOperations = countOperation - leftOperations - 1;
//
//	//Node leftNode = 
//	auto leftNode = generateExpression(leftValue, leftOperations, obj);
//	auto rightNode = generateExpression(rightValue, rightOperations, obj);
//
//	//Шаг 7 | Возвращаем узел - арифметическая операция - экземпляр
//	return std::make_unique<Node>(operation, leftNode.release(), rightNode.release());
//
//	//Функция вызывает саму себя тем самым создается дерево, но такое нужно записывать в строку
//}
/*
std::unique_ptr<Node> generateExpression(short int result, short int countOperation, ConsoleInterface obj) {

	//Следуем по инстркуции алгоритма
	//Шаг 1 | Выбираем арифметический знак, который ввёл пользователь
	std::string operations = obj.getSymbols(); //Передаем те знаки, который пользователь выбрал
	char operation = operations[rand() % operations.length()]; //Рандомно выбираем один из арифметических знаков

	//Шаг 2 | Выбираем число в указанном диапазоне - это 1 операнд | Тестовая версия
	//1 Вариант
	//short int leftValue = rand() % (maxValue - minValue + 1) + minValue;

	//2 Вариант
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	short int leftValue = static_cast<int>((rand() * fraction * (obj.getRangeNumMax() - obj.getRangeNumMin() + 1) + obj.getRangeNumMin()));
	short int rightValue;

	//Шаг 3 | Проверяем
	switch(operation)
}*/
