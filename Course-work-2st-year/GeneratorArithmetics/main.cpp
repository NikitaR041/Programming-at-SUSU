#include <iostream>
#include "ConsoleInterface.h"

int main() {
	setlocale(LC_ALL, "Rus");
	bool is_while = true;
	//size_t count_elem = ConsoleInterface.count_operations;
	
	ConsoleInterface obj(0, 0, 0, 0); // Создаем экземпляр
	obj.setConfigureInterface(); //Передаем аргументы 

	std::unique_ptr<char[]> symbols = std::make_unique<char[]>(obj.getCountOperation()); //Создаем указатель на массив символов

	obj.setSymbols(symbols); //Передайем параметры арифметических символов

	return 0;
}