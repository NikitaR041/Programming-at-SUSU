#include "ConsoleInterface.h"
#include <iostream>
#include <vector>
#include <string>

//Здесь должны быть реализованные методы класса ConsoleInterface

//Заполнение арифметических операций в массив для дальнейшего использования
void ConsoleInterface::setSymbols(std::unique_ptr<char[]>& symbols) {
	if (count_operations <= 0) {
		std::cout << "Количетсво действий должно быть от 0 до 5" << '\n';
		return;
	}

	std::cout << "Введите арифметические операции (+, -, *, /): ";
	char symbol;
	for (short int i = 0; i < count_operations; i++) {
		std::cout << "Введите символ в массив в индексе " << i << ' ';
		std::cin >> symbol;
		if (symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/' && symbol != '~') {
			std::cout << "Ошибка" << '\n';
			break;
		}
		symbols[i] = symbol;
	}

	for (short int i = 0; i < count_operations; i++) {
		std::cout << symbols[i] << '\n';
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