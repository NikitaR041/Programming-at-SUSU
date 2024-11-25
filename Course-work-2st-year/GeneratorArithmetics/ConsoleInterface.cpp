#include "ConsoleInterface.h"
#include <iostream>
#include <vector>
#include <string>

//Здесь должны быть реализованные методы класса ConsoleInterface

void setSymbols(const std::vector<char>& selectSymb) {
	
	
}

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

	//Здесь вызывается метод setSymbols
	std::cout << "Введите арифметические операции (+, -, *, /): ";
}