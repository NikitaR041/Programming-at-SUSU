#include <iostream>
#include "ConsoleInterface.h"

int main() {
	bool is_while = true;
	std::unique_ptr<char[]> symbols;

	ConsoleInterface obj(0,0,0,0);

	//Вызываем 
	obj.setConfigureInterface();
	obj.setSymbols(symbols);

	return 0;
	//while (is_while) {
	//	obj.setConfigureInterface();
	//	//Здесь работает основная 
	//}
}