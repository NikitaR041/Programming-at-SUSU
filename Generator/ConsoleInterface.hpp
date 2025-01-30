#pragma once
#ifndef _CONSOLEINTERFACE_HPP_
#define _CONSOLEINTERFACE_HPP_
#include <vector>
#include <string>

//�����, ����������� ��������� �� ������������
class ConsoleInterface {
    short int count_arith_expres; //���������� �������������� ���������
    short int count_operations; //���������� �������������� �������� + - * / -(-)
    int range_num_min; //�������� �����, �������
    int range_num_max; //�������� �����, ��������
    std::string symbols; //����� �������������� �������� - ������

public:
    //����������� 
    ConsoleInterface(short int count_arith_expres = 0, short int count_operations = 0, int range_num_min = 0, int range_num_max = 0, std::string symbols = "") :
        count_arith_expres(count_arith_expres), count_operations(count_operations), range_num_min(range_num_min), range_num_max(range_num_max), symbols(symbols) {}

    short int getCountArithExpres() const { return this->count_arith_expres; } //����� ��� ��������� �������� �� ���� count_arith_expres � ���������� �������������� ���������
    short int getCountOperation() const { return this->count_operations; } //����� ��� ��������� �������� �� ���� count_operations � ���������� �������������� ��������
    int getRangeNumMin() const { return this->range_num_min; } //����� ��� ��������� ������������ �������� �� ���� range_num_min
    int getRangeNumMax() const { return this->range_num_max; } //����� ��� ��������� ������������� �������� �� ���� range_num_max
    
    std::string getSymbols() { return this->symbols; } // ����� ��� ��������� ��������
    
    void setSymbols(); //����� ��� ������� �������� 
    void setConfigureInterface(); //����� ����� �������� � �������
};

#endif // !_CONSOLEINTERFACE_HPP_
