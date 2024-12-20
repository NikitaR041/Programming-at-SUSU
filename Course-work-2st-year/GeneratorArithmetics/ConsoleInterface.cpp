#include "ConsoleInterface.hpp"
#include <iostream>
#include <vector>
#include <string>

//����� ������ ���� ������������� ������ ������ ConsoleInterface

//���������� �������������� �������� � ������ ��� ����������� �������������
void ConsoleInterface::setSymbols() {
	std::string example;
	std::cout << "������� �������������� �������� (+, -, *, /, ~): ";
	std::cin >> example;
	
	for (short i = 0; i < example.length(); i++) {
		//���� ������������ �� ���� ���������� ��������, �� ���������� ���
		if (example[i] != '+' && example[i] != '-' && example[i] != '*' && example[i] != '/' && example[i] != '~') continue;
		if (example[i] != ' ') symbols.push_back(example[i]);
	}
}


//���� ������ � ������� 
void ConsoleInterface::setConfigureInterface() {
	std::cout << "���������� ��������: ";
	std::cin >> count_arith_expres;
	std::cout << '\n';

	std::cout << "���������� ��������: ";
	std::cin >> count_operations;
	std::cout << '\n';

	std::cout << "�������� �����, �������: ";
	std::cin >> range_num_min;
	std::cout << '\n';

	std::cout << "�������� �����, ��������: ";
	std::cin >> range_num_max;
	std::cout << '\n';
}