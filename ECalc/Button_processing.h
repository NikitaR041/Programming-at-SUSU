#pragma once
#ifndef _BUTTON_PROCESSING_H_
#define _BUTTON_PROCESSING_H_

#include <string>

//����� ��������� ��� ������ �� �����
void out_result(std::string& output_result, my_stack& m);
void out_expression(std::string& output_result, char type);
void out_error(std::string& output_result, std::string error);
void out_expression_str(std::string& output_result, const std::string type);

//����� �������������� ��������� �� �����
void out_bottom_result_str(std::string& result_str,char symb);

//�������� ����� ��������� ��� ����������� ���� | ����������� ��� ������ �������������� ��������
void delete_expression(std::string& num_str, my_stack& m);

//����������� ���. �������
void switch_binary_func(char type, double a, double b, int* is_check_error, std::string& output_result, my_stack& m);
void switch_unary_func(char type, double a, int* is_check_error, int* check_DEG_RAG, std::string& output_result, my_stack& m);

//����������� ��������������� ����� � ���������� ��� � �������������� ����
void arith_switch(char type, int* priority, stack_char& b);
void switch_arith_push(char type, stack_char& b);

//����� ������� �� ������ '=', ���������� ������� ���������� ���������
void operation_result(char type_symbol, std::string& output_result, int* is_check_del, my_stack& m, stack_char& b);

//������� ����������
void is_singular(my_stack& m, stack_char& b, int* priority, int* priority_skb_o, std::string& output_result);
void merging_two_numbers(int* priority, my_stack& m, stack_char& b, std::string& output_result);

//���������� ����� �� ������
void savestr(std::string& num_str, my_stack& m);

//������ ����� '-' �� '+'
void delete_sub_unary(int* priority, stack_char& b);
void delete_sub(int* priority, my_stack& m, stack_char& b);
#endif // _BUTTON_PROCESSING_H_