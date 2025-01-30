#pragma once
#ifndef _MYEXCEPTION_HPP_
#define _MYEXCEPTION_HPP_
#include <iostream>
#include <string>

struct GeneratorOperationError : public std::exception {
	virtual const char* what() const noexcept = 0; //��������� ��� ������
};

struct IncorrectResult : GeneratorOperationError{
        const char* what() const noexcept override { return "������: �������� ��������� ����������!"; }
};

struct UnknownOperation : GeneratorOperationError {
	const char* what() const noexcept override { return "������: ����������� �������������� ��������!"; }
};

struct IncorrectNumOfExamples : GeneratorOperationError {
	const char* what() const noexcept override { return "������: ����������� ������ ���������� ��������!"; }
};

struct IncorrectNumOfActions : GeneratorOperationError {
	const char* what() const noexcept override { return "������: ����������� ������ ���������� �������������� ��������!"; }
};

struct IncorrectNumMinMax : GeneratorOperationError {
	const char* what() const noexcept override { return "������: ����������� ����� �������� ��������! ���������� �������� �� -100000 �� 100000"; }
};

struct IncorrectMinMax : GeneratorOperationError {
	const char* what() const noexcept override { return "������: ����������� ������ ��������� �������� � ���������! ���������, ����� ������������������ ���� ������������!"; }
};

struct IncorrectNameFile : GeneratorOperationError {
	const char* what() const noexcept override { return "������: ����������� ������ ���������� �����, ���� �������� ����� �� �������� ����� 4 ��������!"; }
};
#endif // _MYEXCEPTION_HPP_
