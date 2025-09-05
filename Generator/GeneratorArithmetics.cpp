#include "GeneratorArithmetics.hpp"
#include "ConsoleInterface.hpp"
#include "MyException.hpp"
#include <cstdlib>
#include <string>
#include <memory>
#include <random>

extern std::mt19937 gen;

short int parentOperationAction = 0; //ѕеременна€, котора€ нужна дл€ опредлени€ приоритетности у родительского узла
bool flagParentNode = false; //ѕеременна€, котора€ нужна дл€ определени€ нахождении родительского узла

//ћетод дл€ получени€ приоритетности операций
inline int Node::actionPriority() const {
	if (sym == '+' || sym == '-' || sym == '~') return 1;
	if (sym == '*' || sym == '/') return 2;
	return 0; //»наче если попадаетс€ число
}

//ћетод дл€ преобразовани€ выражени€ из рекурсивного дерева в строку с учетом приоритетности операций 
std::string Node::getExpression() const {
        //¬озвращаем лист
	if (this->left == nullptr && this->right == nullptr) { 
		if (value < 0) { 
                   return '(' + std::to_string(value) + ')'; }
		else { 
                   return std::to_string(value); }
	}
        //”знаем приоритет у родительского узла
	if (flagParentNode == false) {
		parentOperationAction = actionPriority(); 
		flagParentNode = true;
	}
        //”знаем приоритет у текущего узла
	short int nodePriority = actionPriority(); 
	
	std::string leftExpression = (this->left != nullptr) ? left->getExpression() : ""; //–ассматриваем случай дл€ смены знака -(-number)
        std::string rightExpression = right->getExpression(); 
        
	std::string result;
	if(sym == '~'){
            result = rightExpression[0] == '-' ? leftExpression + '-' + rightExpression : leftExpression + "(-" + rightExpression + ')'; //Ќапример: result = -2, тогда right = -(-2) {добавл€тс€ знак - после скобок после скобок (-2)}           
        }else if (parentOperationAction == nodePriority || parentOperationAction != nodePriority) {
            result = '(' + leftExpression + ' ' + sym + ' ' + rightExpression + ')';	
        }
	return result;
}

//¬озвращаем в консоль отформированную строку
std::ostream& operator<<(std::ostream& out, const Node& node) {
	out << node.getExpression();
	return out;
}

//ћетод, который возвращает массив делителей числа
std::vector<int> findDivisors(int result) {	
	std::vector<int> divisors;
	std::vector<int> neg_divisors;
	for (int i = 1; i <= std::sqrt(std::abs(result)); ++i) {
		if (result % i == 0) {
			divisors.push_back(i);
			if (i != result / i) {  // »збегаем дублировани€ делителей
				divisors.push_back(result / i);
			}
		}
	}

	for (const int elem : divisors) {
		neg_divisors.push_back(-elem);
	}
	divisors.insert(divisors.end(), neg_divisors.begin(), neg_divisors.end());
	return divisors;
}

//ћетод, генерирующий узлы и листы
std::unique_ptr<Node> generateExpression(int result, unsigned short int countOperation, ConsoleInterface obj) {
	if (countOperation == 0) return std::make_unique<Node>(result); //¬озвращение листа
        int NumMin = obj.getRangeNumMin(), NumMax = obj.getRangeNumMax();
        if(!(NumMin <= result && result <= NumMax)) throw IncorrectResult();
	int leftValue = 0, rightValue = 0;
	int deltaNumA = 0, deltaNumB = 0;
        short int N = 0, M = 0;

	std::string operations = obj.getSymbols();
	std::shuffle(operations.begin(), operations.end(), gen);

	std::vector<int> duplicate_divisors;

	std::uniform_int_distribution<int> distribLeftValue;
	std::uniform_int_distribution<int> iteration;

	for (char operation : operations) {
		//¬ случа€х, если дл€ '*' будет пустой список делителей числа result, либо если дл€ '/' будет деление на ноль, то пропускаем этот знак
		if ((operation == '*' || operation == '/') && result == 0) continue;
		
		switch (operation) {
		case '+':
			deltaNumA = std::max(NumMin, result - NumMax); //Ћевый край отрезка
			deltaNumB = std::min(NumMax, result - NumMin); //ѕравый край отрезка
			if (deltaNumA > deltaNumB) continue;		
			distribLeftValue = std::uniform_int_distribution<int>(deltaNumA, deltaNumB);
			leftValue = distribLeftValue(gen);
			rightValue = result - leftValue;
			break;
		case '-':
			deltaNumA = std::max(NumMin, NumMin + result); 
			deltaNumB = std::min(NumMax, NumMax + result); 
			if (deltaNumA > deltaNumB) continue;
			distribLeftValue = std::uniform_int_distribution<int>(deltaNumA, deltaNumB);
			leftValue = distribLeftValue(gen);
			rightValue = leftValue - result;
			break;
		case '*':
			duplicate_divisors = findDivisors(result);
			std::erase_if(duplicate_divisors, [=](int x) {return x < NumMin || x > NumMax || result / x < NumMin || result / x > NumMax; }); //‘ильтр делителей
			if (duplicate_divisors.empty()) continue;
                        iteration = std::uniform_int_distribution<int>(0, static_cast<int>(duplicate_divisors.size()) - 1);
			leftValue = duplicate_divisors[iteration(gen)];
			rightValue = result / leftValue;
			break;
		case '/':
			deltaNumA = static_cast<int>(std::max<double>(NumMin, (double)result * NumMin)); 
			deltaNumB = static_cast<int>(std::min<double>(NumMax, (double)result * NumMax)); 
			
			if (deltaNumA > deltaNumB) continue;
			
			distribLeftValue = std::uniform_int_distribution<int>(deltaNumA, deltaNumB); 
			leftValue = distribLeftValue(gen);

			rightValue = result * leftValue;
			if (leftValue == 0 || rightValue == 0) continue;

			if (!(NumMin <= rightValue && rightValue <= NumMax)) continue;
			break;
		case '~':
			rightValue = -result;
			if (rightValue < NumMin || rightValue > NumMax) continue;
			N = 0;
			M = countOperation - N - 1;
			return std::make_unique<Node>('~', nullptr, generateExpression(rightValue, M, obj));
		default:
			throw UnknownOperation();
		}
                
		if (NumMin <= rightValue && rightValue <= NumMax) {
			std::uniform_int_distribution<int> distribDecN(0, countOperation - 1);
			N = distribDecN(gen);
			M = countOperation - N - 1;

			std::unique_ptr<Node> leftNode;
			std::unique_ptr<Node> rightNode;


			leftNode = (N > 0) ? generateExpression(leftValue, N, obj) : std::make_unique<Node>(leftValue);// –екурси€ дл€ левого узла
			rightNode = (M > 0) ? generateExpression(rightValue, M, obj) : std::make_unique<Node>(rightValue); // –екурси€ дл€ правого узла

			return std::make_unique<Node>(operation, std::move(leftNode), std::move(rightNode));
		}
	}
	throw std::runtime_error("Ќет доступных операций дл€ генерации выражени€");
}