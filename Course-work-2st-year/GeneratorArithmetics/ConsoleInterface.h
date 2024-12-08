#pragma once
#include <memory>
#include <vector>

//����������� ��������������� ����� ConsoleInterface
class ConsoleInterface {
    unsigned short int count_arith_expres; //���������� �������������� ���������
    unsigned short int count_operations; //���������� �������������� �������� + - * / -(-)
    short int range_num_min; //�������� �����, �������
    short int range_num_max; //�������� �����, ��������
    std::unique_ptr<char[]> symbols; //����� �������������� �������� - ������

public:
    ConsoleInterface(unsigned short int count_arith_expres = 0, unsigned short int count_operations = 0, short int range_num_min = 0, short int range_num_max = 0, std::unique_ptr<char[]> symbols) :
        count_arith_expres(count_arith_expres), count_operations(count_operations), range_num_min(range_num_min), range_num_max(range_num_max), symbols{ std::make_unique<char[]>(5) } {}

    ~ConsoleInterface() {}    

    //������, ������� �������� �������� �� �����
    unsigned short int getCountArithExpres() const { return this->count_arith_expres; }
    unsigned short int getCountOperation() const { return this->count_operations; }
    short int getRangeNumMin() const { return this->range_num_min; }
    short int getRangeNumMax() const { return this->range_num_max; }
    const char* getSymbols() const { return this->symbols.get(); }

    void setSymbols(const std::vector<char>& selectSymb); //����� ��� ������� �������� 
    
    void setConfigureInterface(); //����� ��� ������� �������� �����
};

