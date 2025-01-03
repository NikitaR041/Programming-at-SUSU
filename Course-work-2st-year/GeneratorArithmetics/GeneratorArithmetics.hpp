#pragma once
#ifndef _GENERATORARITHMETICS_HPP_
#define _GENERATORARITHMETICS_HPP_
#include <iostream>
#include "ConsoleInterface.hpp"

//����� ��� �������� �����(������) � ��������� ��������������� ���������
static constexpr double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

struct Node {
    short int value; //�������� � ���� ���� short int
    char sym; //�������� (��������, '+', '-', '*', '/', '-(-)')
    std::unique_ptr<Node> left; //����� ����(����)
    std::unique_ptr<Node> right; //������ ����(����)

    //������ ����������� - �����
    Node(short int value) : value(value), sym('\0'), left(nullptr), right(nullptr) {}
    //������ ����������� - �������������� ��������
    Node(char sym, Node* left, Node* right) : value(0), sym(sym), left(left), right(right) {}

    //char action() const; //��������� �������������� �������� �� ����
    int actionPriority() const; //��������� ��������������

    std::string getExpression(int parentPriority) const; //�������������� ������ � ������-���������  -  ���������� � ����
    friend std::ostream& operator<<(std::ostream& out, const Node& node); // ��������������� ��������� ������ � ����� ��������������� ��������� 
};

//����� ��� ��������� ���������
std::unique_ptr<Node> generateExpression(short int result, short int countOperation, ConsoleInterface obj);

#endif // ! _GENERATORARITHMETICS_HPP_
