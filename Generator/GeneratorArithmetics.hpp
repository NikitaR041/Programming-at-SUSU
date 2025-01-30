#pragma once
#ifndef _GENERATORARITHMETICS_HPP_
#define _GENERATORARITHMETICS_HPP_
#include <iostream>
#include <memory>
#include "ConsoleInterface.hpp"

//����� ��� �������� �����(������) � ��������� ��������������� ���������
struct Node {
    int value; //�������� � ���� ���� int
    char sym; //�������� (��������, '+', '-', '*', '/', '-(-)')
    std::unique_ptr<Node> left; //����� ����(����)
    std::unique_ptr<Node> right; //������ ����(����)

    //������ ����������� - �����
    Node(int value) : value(value), sym('\0'), left(nullptr), right(nullptr) {}
    //������ ����������� - �������������� ��������
    Node(char sym, std::unique_ptr<Node> left, std::unique_ptr<Node> right) : value(0), sym(sym), left(std::move(left)), right(std::move(right)) {}

    int actionPriority() const; //����� ��� ��������� ��������������

    std::string getExpression() const;//����� ��� �������������� ������ � ������-���������
    friend std::ostream& operator<<(std::ostream& out, const Node& node); // ��������������� ��������� ������ � ����� ��������������� ��������� 
};

//������� ��� ��������� ���������
std::unique_ptr<Node> generateExpression(int result, unsigned short int countOperation, ConsoleInterface obj);

#endif // ! _GENERATORARITHMETICS_HPP_
