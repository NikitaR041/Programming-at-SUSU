#pragma once
#include <iostream>

//����������� ��������������� ����� GeneratorArithmetic
struct Node {
    short int value; //�������� � ���� ���� short int
    char sym; //�������� (��������, '+', '-', '*', '/', '-(-)')
    std::unique_ptr<Node> left; //����� ����(����)
    std::unique_ptr<Node> right; //������ ����(����)

    //������ ����������� - �����
    Node(short int value) : value(value), sym('\0'), left(nullptr), right(nullptr) {}
    //������ ����������� - �������������� ��������
    Node(char sym, Node* left, Node* right) : value(0), sym(sym), left(left), right(right) {}
    ~Node() {}

    char action() const; //��������� �������������� �������� �� ����
    int actionPriority() const; //��������� ��������������
};

class GenericArithmetics { 
    std::unique_ptr<Node> root;//������ ������ - ��������
public:
    GenericArithmetics() : root(nullptr) {}
   
    void generateExpression(); //�������� ����� ��� ��������� ������ - ��������� �� ���������� ���������� �� ������ ConsoleInterface
    std::string getExpression(); //�������������� ������ � ������-���������  -  ���������� � ����
    friend std::ostream& operator<<(std::ostream& out, const GenericArithmetics& other); // ��������������� ��������� ������ � ����� ��������������� ��������� 
};
