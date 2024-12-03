#include <iostream>
#include "ConsoleInterface.h"

int main() {
	setlocale(LC_ALL, "Rus");
	bool is_while = true;

	ConsoleInterface obj(0, 0, 0, 0, ""); //Создаем объект

	obj.setConfigureInterface();
	obj.setSymbols();

	return 0;
}