#pragma once
#ifndef _MATH_FOR_CALC_H_
#define _MATH_FOR_CALC_H_

#include <string>

//Костантные значения числа PI - Пифагора и E - Эйлера
const double PI = 3.14159265358979323846;
const double E = 2.718281828459045;

//----Стек, в котором хранится числа типа double----
typedef struct{
	int top;
	double mass[1001];
}my_stack;
//----Стек, в котором хранится числа типа double----

//----Функции стека c типом double----
void stack_init(my_stack* a);
void stack_push(my_stack* a, double v);
void stack_pop(my_stack* a);
double stack_top(my_stack* a);
double stack_isempty(my_stack* a);
//----Функции стека c типом double----

//--------stack_char, в котором хранятся арифметичексие знаки,мат.функции и скобки--------
typedef struct {
	int top;
	char mass_char[1001];
}stack_char;
//--------stack_char, в котором хранятся арифметичексие знаки,мат.функции и скобки--------

//--------stack_char с типом char--------
void stack_init(stack_char* b);
void stack_push(stack_char* b, char v);
void stack_pop(stack_char* b);
int stack_top(stack_char* b);
int stack_isempty(stack_char* b);
//--------stack_char с типом char--------


double sum_digits(double a, double b);
double sub_digits(double a, double b);
double mul_digits(double a, double b);
double div_digits(double  a, double b, std::string& output_result);

//---------------------------Математические функции---------------------------

//Рядом с функциями обозначены на латинице в алфавитном порядке их краткое обозначение
//Нужно для сохранения этих мат.функций в арифметическом стеке

double sqrt2(double a, std::string& output_result); // A
double sqrtn(double a, double b, std::string& output_result); //B
double pow2(double a); //C
double pown(double a, double b); //D
double fact(double a, std::string& output_result); // E
double log_2(double a, std::string& output_result); //F
double logn(double a, double b, std::string& output_result); // G
double ln(double a, std::string& output_result); //H
double lg(double a, std::string& output_result); // I
double pow10n(double a); //K
double sinus(double a, int* check_DEG_RAG); //L
double cosinus(double a, int* check_DEG_RAG); //M
double tangent(double a, int* check_DEG_RAG, std::string& output_result); //N
double cotangent(double a, int* check_DEG_RAG, std::string& output_result); //O
double arcsinus(double a, std::string& output_result); //P
double arccosinus(double a, std::string& output_result); //Q
double arctangent(double a, int* check_DEG_RAG); //R
double arccotangent(double a, int* check_DEG_RAG); //S
double modul(double a); //T
double MOD(double a, double b); //V
double exponenta(double a); //W
double delete_1(double a, std::string& output_result); //X
//---------------------------Математические функции---------------------------


#endif // _MATH_FOR_CALC_H_