#pragma once
#ifndef _CONSOLEINTERFACE_HPP_
#define _CONSOLEINTERFACE_HPP_
#include <vector>
#include <string>

//�����, ����������� ��������� �� ������������
class ConsoleInterface {
    unsigned short int count_arith_expres; //���������� �������������� ���������
    unsigned short int count_operations; //���������� �������������� �������� + - * / -(-)
    short int range_num_min; //�������� �����, �������
    short int range_num_max; //�������� �����, ��������
    std::string symbols; //����� �������������� �������� - ������

public:
    ConsoleInterface(unsigned short int count_arith_expres = 0, unsigned short int count_operations = 0, short int range_num_min = 0, short int range_num_max = 0, std::string symbols = "") :
        count_arith_expres(count_arith_expres), count_operations(count_operations), range_num_min(range_num_min), range_num_max(range_num_max), symbols(symbols) {}

    unsigned short int getCountArithExpres() const { return this->count_arith_expres; } //����� ��� ��������� �������� �� ���� count_arith_expres � ���������� �������������� ���������
    unsigned short int getCountOperation() const { return this->count_operations; } //����� ��� ��������� �������� �� ���� count_operations � ���������� �������������� ��������
    short int getRangeNumMin() const { return this->range_num_min; } //����� ��� ��������� ������������ �������� �� ���� range_num_min
    short int getRangeNumMax() const { return this->range_num_max; } //����� ��� ��������� ������������� �������� �� ���� range_num_max
    
     //�� ����� ���� ����� ������������:
    bool canSymbols(char op); //����� ��� �������� ����������� �������� ???
    std::string getSymbols() { return this->symbols; } // ??
    
    void setSymbols(); //����� ��� ������� �������� 
    void setConfigureInterface(); //����� ����� �������� � �������
};

#endif // !_CONSOLEINTERFACE_HPP_
