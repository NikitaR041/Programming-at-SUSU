#include "ConsoleInterface.h"
#include <iostream>
#include <vector>
#include <string>

//����� ������ ���� ������������� ������ ������ ConsoleInterface

void setSymbols(const std::vector<char>& selectSymb) {
	
	
}

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

	//����� ���������� ����� setSymbols
	std::cout << "������� �������������� �������� (+, -, *, /): ";
}