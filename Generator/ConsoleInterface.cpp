#include "ConsoleInterface.hpp"
#include "MyException.hpp"
#include <iostream>
#include <vector>
#include <string>

//���������� �������������� �������� � ������ ��� ����������� �������������
void ConsoleInterface::setSymbols() {
	std::string example;
	std::cout << "������� �������������� �������� (+, -, *, /, ~): ";
	std::cin >> example;
	std::cout << '\n';
	std::cout << "��� ����� ��� ������: ";
	
        for (char elem : example){
                if (elem != '+' && elem != '-' && elem != '*' && elem != '/' && elem != '~') continue;
                if (elem != ' ') symbols.push_back(elem);
         }
}


//���� ������ � ������� 
void ConsoleInterface::setConfigureInterface() {
	std::cout << "���������� ��������: ";
	std::cin >> count_arith_expres;
	if (count_arith_expres <= 0) throw IncorrectNumOfExamples();
	std::cout << '\n';

	std::cout << "���������� ��������: ";
	std::cin >> count_operations;
	if (count_operations <= 0) throw IncorrectNumOfActions();
	std::cout << '\n';

	std::cout << "�������� �����, �������: ";
	std::cin >> range_num_min;
	if(-100000 > range_num_min) throw IncorrectNumMinMax();
	std::cout << '\n';

	std::cout << "�������� �����, ��������: ";
	std::cin >> range_num_max;
	if (range_num_max > 100000) throw IncorrectNumMinMax();
	std::cout << '\n';

	if (range_num_min > range_num_max) throw IncorrectMinMax();
}