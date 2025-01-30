#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Math_for_calc.h"
#include <string>

const int N = 45; //������ ������������ ������� | 45 - ���������� ����� ������
extern int is_check_deg_rag; //�������� �� ������ �� DEG � RAG � �������� (�� ��������� DEG)

//����� ����������� �� �����
void draw_buts();

//�������� ���� ������
void clear_the_input(my_stack& m, stack_char& b);

//�������� ������, '�����' ������ � ���� ���������� ������ ����� ������� ��� �� ���������� ����
void clear_bufer(int* mass, int* jndex, int* count_mass);

//�������� ������ ���� �� DEG � RAG � �������� (�� ��������� ��� DEG)
void replace_deg_rag(int* is_check_deg_rag);

//������� �� ������ ����� '-' �� '+' ��� ���.����. abs
void draw_template_abs(std::string& output_result);

//��������� �������
void draw_template(std::string& output_result, int index, int num);

//"������" - ����� ���������� ������� ������
void about_but(int* mass, int* count_mass, std::string& output_result, std::string& result_str, my_stack& m, stack_char& b);

#endif // _BUTTON_H_