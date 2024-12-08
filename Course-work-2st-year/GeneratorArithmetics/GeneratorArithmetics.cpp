#include "GeneratorArithmetics.hpp"
#include "ConsoleInterface.hpp"
#include <cstdlib>
#include <string>
#include <memory>

//static constexpr double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

//Метод для получения приоритетности операций
int Node::actionPriority() const {
	if (sym == '+' || sym == '-') return 1;
	if (sym == '*' || sym == '/') return 2;
	return 0; //Иначе если попадается число
}

//Метод для преобразования выражения из рекурсивного дерева в строку с учетом приоритетности операций 
std::string Node::getExpression(int parentPriority = 0) const {
	//Возвращаем число, если лист
	if (this->left == nullptr && this->right == nullptr) {
		return std::to_string(value);
	}

	//Рекурсивно вызываем все узлы и листы для построения выражения в строку
	std::string leftExpression = left->getExpression(actionPriority());
	std::string rightExpression = right->getExpression(actionPriority());

	//Расставим скобки - в основном для левого операнда
	if (actionPriority() < parentPriority) {
		leftExpression = '(' + leftExpression + ')';
	}

	//Возвращаем отформированную строку
	return leftExpression + ' ' + sym + ' ' + rightExpression;
}

//Возвращаем в консоль отформированную строку
std::ostream& operator<<(std::ostream& out, const Node& node) {
	out << node.getExpression();
	return out;
}

//Метод для генерации выражений
std::unique_ptr<Node> generateExpression(short int result, short int countOperation, ConsoleInterface obj) {
	//Если попался лист
	if (countOperation == 0) return std::make_unique<Node>(result);

	//fraction нужен для функции rand()
	short int leftValue; // Левый операнд 
	short int rightValue; // Правый операнд

	std::string operations = obj.getSymbols(); //Предаем арфиметические операции из консоли
	char operation; // Выборка операции

	while (true) {
		operation = operations[rand() % operations.length()];
		leftValue = static_cast<int>((rand() * fraction * (obj.getRangeNumMax() - obj.getRangeNumMin() + 1) + obj.getRangeNumMin()));
		
		if (leftValue == 0) continue; //исключительная ситуация

		switch (operation) 
		{
		case '+': rightValue = result - leftValue; break;
		case '-': rightValue = leftValue - result; break;
		case '*': rightValue = result / leftValue; break;
		case '/': rightValue = leftValue / result; break;  
		default: rightValue = 0;
		}

		//Проверка правого операнда, если выходит за диапазон, и левого, если будут повторения нулей
		if (rightValue > obj.getRangeNumMin() && rightValue <= obj.getRangeNumMax() && leftValue != 0) break;
	}

	short int N = countOperation - 1; //  Выбрать случайно N от 0 до общЧислоДействий-1 для разложения 1-го операнда
	short int M = countOperation - N - 1; // Выбрать случайно M от 0 до общЧислоДействий-N-1 для разложения 2-го операнда

	//Создаем следующие узлы(листы)
	std::unique_ptr<Node> leftNode;
	std::unique_ptr<Node> rightNode;

	//Если больше невозмонжо разложить левый операнд, то сохраняем лист
	if (N > 0) {
		leftNode = generateExpression(leftValue, N, obj);
	}
	else {
		leftNode = std::make_unique<Node>(leftValue); //Сохранение числа в объект
	}

	//Аналогично, если больше невозмонжо разложить правый операнд, то сохраняем лист
	if (M > 0) {
		rightNode = generateExpression(rightValue, M, obj);
	}
	else {
		rightNode = std::make_unique<Node>(rightValue); //Сохранение числа в объект
	}

	//Возвращаем узел - арифметическая операция - экземпляр
	return std::make_unique<Node>(operation, leftNode.release(), rightNode.release());
}