#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Math_for_calc.h"
#include <string>

const int N = 45; //Размер структурного массива | 45 - количество всего кнопок
extern int is_check_deg_rag; //Проверка на замену из DEG в RAG и наоборот (По умолчанию DEG)

//Вывод изображения на экран
void draw_buts();

//Очищение двух стеков
void clear_the_input(my_stack& m, stack_char& b);

//Очищение буфера, 'буфер' хранит в себе координаты кнопки после нажатия ЛКМ на диалоговое окно
void clear_bufer(int* mass, int* jndex, int* count_mass);

//Проверка замены типа из DEG в RAG и наоборот (По умолчанию тип DEG)
void replace_deg_rag(int* is_check_deg_rag);

//Функция по замене знака '-' на '+' для мат.функ. abs
void draw_template_abs(std::string& output_result);

//Рисование шаблона
void draw_template(std::string& output_result, int index, int num);

//"Сердце" - здесь происходит процесс работы
void about_but(int* mass, int* count_mass, std::string& output_result, std::string& result_str, my_stack& m, stack_char& b);

#endif // _BUTTON_H_