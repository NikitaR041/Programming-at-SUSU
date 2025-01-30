#include "GeneratorArithmetics.hpp"
#include "ConsoleInterface.hpp"
#include "MyException.hpp"
#include <cstdlib>
#include <string>
#include <memory>
#include <random>

extern std::mt19937 gen;

short int parentOperationAction = 0; //����������, ������� ����� ��� ���������� �������������� � ������������� ����
bool flagParentNode = false; //����������, ������� ����� ��� ����������� ���������� ������������� ����

//����� ��� ��������� �������������� ��������
inline int Node::actionPriority() const {
	if (sym == '+' || sym == '-' || sym == '~') return 1;
	if (sym == '*' || sym == '/') return 2;
	return 0; //����� ���� ���������� �����
}

//����� ��� �������������� ��������� �� ������������ ������ � ������ � ������ �������������� �������� 
std::string Node::getExpression() const {
        //���������� ����
	if (this->left == nullptr && this->right == nullptr) { 
		if (value < 0) { 
                   return '(' + std::to_string(value) + ')'; }
		else { 
                   return std::to_string(value); }
	}
        //������ ��������� � ������������� ����
	if (flagParentNode == false) {
		parentOperationAction = actionPriority(); 
		flagParentNode = true;
	}
        //������ ��������� � �������� ����
	short int nodePriority = actionPriority(); 
	
	std::string leftExpression = (this->left != nullptr) ? left->getExpression() : ""; //������������� ������ ��� ����� ����� -(-number)
        std::string rightExpression = right->getExpression(); 
        
	std::string result;
	if(sym == '~'){
            result = rightExpression[0] == '-' ? leftExpression + '-' + rightExpression : leftExpression + "(-" + rightExpression + ')'; //��������: result = -2, ����� right = -(-2) {���������� ���� - ����� ������ ����� ������ (-2)}           
        }else if (parentOperationAction == nodePriority || parentOperationAction != nodePriority) {
            result = '(' + leftExpression + ' ' + sym + ' ' + rightExpression + ')';	
        }
	return result;
}

//���������� � ������� ��������������� ������
std::ostream& operator<<(std::ostream& out, const Node& node) {
	out << node.getExpression();
	return out;
}

//�����, ������� ���������� ������ ��������� �����
std::vector<int> findDivisors(int result) {	
	std::vector<int> divisors;
	std::vector<int> neg_divisors;
	for (int i = 1; i <= std::sqrt(std::abs(result)); ++i) {
		if (result % i == 0) {
			divisors.push_back(i);
			if (i != result / i) {  // �������� ������������ ���������
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

//�����, ������������ ���� � �����
std::unique_ptr<Node> generateExpression(int result, unsigned short int countOperation, ConsoleInterface obj) {
	if (countOperation == 0) return std::make_unique<Node>(result); //����������� �����
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
		//� �������, ���� ��� '*' ����� ������ ������ ��������� ����� result, ���� ���� ��� '/' ����� ������� �� ����, �� ���������� ���� ����
		if ((operation == '*' || operation == '/') && result == 0) continue;
		
		switch (operation) {
		case '+':
			deltaNumA = std::max(NumMin, result - NumMax); //����� ���� �������
			deltaNumB = std::min(NumMax, result - NumMin); //������ ���� �������
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
			std::erase_if(duplicate_divisors, [=](int x) {return x < NumMin || x > NumMax || result / x < NumMin || result / x > NumMax; }); //������ ���������
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


			leftNode = (N > 0) ? generateExpression(leftValue, N, obj) : std::make_unique<Node>(leftValue);// �������� ��� ������ ����
			rightNode = (M > 0) ? generateExpression(rightValue, M, obj) : std::make_unique<Node>(rightValue); // �������� ��� ������� ����

			return std::make_unique<Node>(operation, std::move(leftNode), std::move(rightNode));
		}
	}
	throw std::runtime_error("��� ��������� �������� ��� ��������� ���������");
}