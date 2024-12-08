#include <iostream>
#include "ConsoleInterface.hpp"
#include "GeneratorArithmetics.hpp"

int main() {
	setlocale(LC_ALL, "Rus");

	ConsoleInterface obj(0, 0, 0, 0, ""); //Создаем объект

	//Вводим с консоли 
	obj.setConfigureInterface();
	obj.setSymbols();

	//Результат на консоли
	short int count = obj.getCountOperation();
	while (count != 0) {
		short int result = static_cast<int>((rand() * fraction * (obj.getRangeNumMax() - obj.getRangeNumMin() + 1) + obj.getRangeNumMin()));
		std::unique_ptr<Node> expression = generateExpression(result, obj.getCountOperation(), obj);
		count--;

		std::cout << "Сгенерированное выражение: " << *expression << " Ответ: " << result << '\n';
	}

	return 0;
}