#include "ConsoleInterface.h"
#include <iostream>
#include <vector>
#include <string>

//Здесь должны быть реализованные методы класса ConsoleInterface

//Заполнение арифметических операций в массив для дальнейшего использования
void ConsoleInterface::setSymbols() {
	std::string example;
	std::cout << "Введите арифметические операции (+, -, *, /, ~): ";
	std::cin >> example;
	
	for (short i = 0; i < example.length(); i++) {
		if (example[i] != ' ') symbols.push_back(example[i]);
	}
}


//Ввод данных с консоли 
void ConsoleInterface::setConfigureInterface() {
	std::cout << "Количество примеров: ";
	std::cin >> count_arith_expres;
	std::cout << '\n';

	std::cout << "Количество действий: ";
	std::cin >> count_operations;
	std::cout << '\n';

	std::cout << "Диапазон чисел, минимум: ";
	std::cin >> range_num_min;
	std::cout << '\n';

	std::cout << "Диапазон чисел, максимум: ";
	std::cin >> range_num_max;
	std::cout << '\n';
}