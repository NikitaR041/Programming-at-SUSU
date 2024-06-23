#include <iostream>
#include <cmath>
#include "Math_for_calc.h"
#include "Button_processing.h"


//--------stack_digit--------

//Инициализация численного стека
void stack_init(my_stack *a) {
   a->top = -1;
}

//Добавление значения в численный стек
void stack_push(my_stack *a, double v) {
   if (a->top == 1000) {
      return;
   }
   a->top += 1;
   a->mass[a->top] = v;
}

//Удаление верхнего значения из численного стека
void stack_pop(my_stack *a) {
   a->mass[a->top] = 0;
   a->top -= 1;
}

//Получение верхнего значения из численного стека
double stack_top(my_stack *a) {
   return a->mass[a->top];
}

//Проверка на пустоту численного стека
double stack_isempty(my_stack *a) { // проверить, что стек пуст
   if (a->top == -1) {
      return true;
   }
   else {
      return false;
   }
}
//----------------stack_digit----------------



//----------------stack_char----------------

// Инициализация арифметичексого стека
void stack_init(stack_char *b) {
   b->top = -1;
}

//Добавление значения в арифметический стек
void stack_push(stack_char *b, char v) {
   if (b->top == 1000) {
      return;
   }
   b->top += 1;
   b->mass_char[b->top] = v;
}

//Удаление верхнего значения из арифметического стека
void stack_pop(stack_char *b) {
   b->mass_char[b->top] = 0;
   b->top -= 1;
}

//Получение верхнего значения из арифметического стека
int stack_top(stack_char *b) {
   return b->mass_char[b->top];
}

//Проверка на пустоту арифметического стека
int stack_isempty(stack_char *b) {
   if (b->top == -1) {
      return true;
   }
   else {
      return false;
   }
}
//----------------stack_char----------------

//---------------------------Математические операции---------------------------
double sum_digits(double a, double b) {
   return a + b;
}

double sub_digits(double a, double b) {
   return a - b;
}

double mul_digits(double a, double b) {
   return a * b;
}

double div_digits(double a, double b, std::string &output_result) {
   if (b == 0.0) { // По идеи, что вещественное число b должно быть равно 0.0
      out_error(output_result, "Деление на 0 запрещено!");
      return -1;
   }
   else {
      return a / b;
   }
}
//---------------------------Математические операции---------------------------

//---------------------------Математические функции---------------------------
/*
Функция вычисления факториала от числа a
На вход поступает аргумент a типа double
Также в параметрах есть output_result - нужна для выведения ошибки на экран
Есть дополнительная проверка на ОДЗ
*/
double fact(double a, std::string &output_result) {
   double result = 1;
   if (a < 0) {
      out_error(output_result, "Неверный ввод. Диапазон начинается с нуля.");
      return false;
   }
   for (int i = 1; i <= a; ++i) {
      result *= i;
   }
   return result;
}

//Функция синуса | На вход поступает аргумент a типа double и flag типа int, который означает, что пользователь ввел аргумент в радианах
double sinus(double a, int *check_DEG_RAG) {
   if (*check_DEG_RAG == true) {
      return sin(a); //Из радианов в градусы получаем значение
   }
   else {
      return sin((a) * (PI / 180.0)); //Из градусов в радианы получаем значение
   }
}

//Функция косинуса | На вход поступает аргумент a типа double и flag типа int, который означает, что пользователь ввел аргумент в радианах
double cosinus(double a, int *check_DEG_RAG) {
   if (*check_DEG_RAG == true) {
      return cos(a);//Из радианов в градусы получаем значение
   }
   else {
      return cos((a) * (PI / 180.0)); //Из градусов в радианы получаем значение
   }
}

/*
Функция тангенса
На вход поступает аргумент a типа double и flag типа int, который означает, что пользователь ввел аргумент в радианах
Также в параметрах есть output_result - нужна для выведения ошибки на экран
Есть дополнительная проверка на ОДЗ
*/
double tangent(double a, int *check_DEG_RAG, std::string &output_result) {
   double num = 0;
   //Если дано в градусах
   if (*check_DEG_RAG != true) {
      for (int i = 1; i <= 10; i++) {
         if (a == 90 * i || a == 270 * i) {
            out_error(output_result, "Неверный ввод. Тангенс не существует");
            return -1; //Возвращаем ошибку
         }
         else {
            //Для быстрого выведения из цикла
            if (a < 90 * i && (a) < 270 * i) break;
            //т.е. число больше проверки, нужно добрать и проверить
            continue;
         }
      }
      return  tan((a) * (PI / 180.0)); //Из градусов к радианам и получаем число
   }
   else {
      num = (PI / 2);
      for (int i = 0; i < 10; i++) {
         if (a == num + PI * i || a == 3 * num + PI * i) {
            out_error(output_result, "Неверный ввод. Тангенс не существует");
            return -1; //Возвращаем ошибку
         }
         else {
            if (a < num + PI * i && a < 3 * num + PI * i) break;
            continue;
         }
      }
      return tan(a);
   }
}
/*
Фунцкция котангенса
На вход поступает аргумент a типа double и flag типа int, который означает, что пользователь ввел аргумент в радианах
Также в параметрах есть output_result - нужна для выведения ошибки на экран
Есть дополнительная проверка на ОДЗ
*/
double cotangent(double a, int *check_DEG_RAG, std::string &output_result) {
   //Если задана в градусах
   if (*check_DEG_RAG != true) {
      for (int i = 0; i < 10; i++) {
         if (a == 0 + 180 * i || a == 180 + 180 * i) {
            out_error(output_result, "Неверный ввод. Котангенс не существует");
            return -1; //Возвращаем ошибку
         }
         else {
            //Для быстрого выведения из цикла
            if (a < 0 + 180 * i || a < 180 + 180 * i) break;
            //т.е. число больше проверки, нужно добрать и проверить
            continue;
         }
      }
      //Из градусов к радианам и получаем число
      return cos((a) * (PI / 180.0)) / sin((a) * (PI / 180.0));
   }
   else {
      for (int i = 0; i < 10; i++) {
         if (a == PI * i || a == PI + PI * i) {
            out_error(output_result, "Неверный ввод. Котангенс не существует");
            return -1; //Возвращаем ошибку
         }
         else {
            //Для быстрого выведения из цикла
            if (a < 0 + 180 * i || a < 180 + 180 * i) break;
            //т.е. число больше проверки, нужно добрать и проверить
            continue;
         }
      }
      //Из радианов к градусам и получаем число
      return cos(a) / sin(a);
   }
}

/*
Функция обратного синуса
На вход поступает аргумент a типа double и flag типа int, который означает, что пользователь ввел аргумент в радианах
Также в параметрах есть output_result - нужна для выведения ошибки на экран
Есть дополнительная проверка на ОДЗ
*/
double arcsinus(double a, std::string &output_result) {
   if (-1.0 <= a && a <= 1.0) {
      return asin(a);
   }
   out_error(output_result, "Неверный ввод. Диапазон должен быть от -1 до 1");
   return -1;
}
/*
Функция обратного косинуа
На вход поступает аргумент a типа double и flag типа int, который означает, что пользователь ввел аргумент в радианах
Также в параметрах есть output_result - нужна для выведения ошибки на экран
Есть дополнительная проверка на ОДЗ
*/
double arccosinus(double a, std::string &output_result) {
   if (-1.0 <= a && a <= 1.0) {
      return acos(a);
   }
   out_error(output_result, "Неверный ввод. Диапазон должен быть от -1 до 1");
   return -1;
}

/*
Функция обратного тангенса
На вход поступает аргумент a типа double и flag типа int, который означает, что пользователь ввел аргумент в радианах
*/
double arctangent(double a,int *check_DEG_RAG) {
   double num = 0;
   //Если передано в градусах, то переделаем в радианах
   if (*check_DEG_RAG != true) num = a * (PI / 180.0);
   else  num = a; //Передано в радианах

   return atan(num);
}

/*
Функция обратного котангенса
На вход поступает аргумент a типа double и flag типа int, который означает, что пользователь ввел аргумент в радианах
Например, в arccotangent(p/2)
*/
double arccotangent(double a, int *check_DEG_RAG) {
   double num = 0;
   //Если передано в градусах, то переделаем в радианах
   if (*check_DEG_RAG != true) num = a * (PI / 180.0);
   else  num = a; //Передано в радианах

   return atan(1.0 / num);
}
//Функция логарифма с основанием 2 | На вход поступает аргумент а типа double, являющимся числом | В функции есть дополнительная проверка на ОДЗ
double log_2(double a, std::string &output_result) {
   if (a <= 0) {
      out_error(output_result, "Неверный ввод. Диапазон начинатся от 0");
      return false;
   }
   return log2(a);
}
/*
Функция десятичного логарифма
На вход поступает аргумент а типа double
Также в параметрах есть output_result - нужна для выведения ошибки на экран
В функции есть дополнительная проверка на ОДЗ
*/
double lg(double a, std::string &output_result) {
   if (a <= 0) {
      out_error(output_result, "Неверный ввод. Диапазон начинатся от 0");
      return false;
   }
   return log10(a);
}

/*
Функция натурального логарифма
На вход поступает аргумент а типа double
Также в параметрах есть output_result - нужна для выведения ошибки на экран
В функции есть дополнительная проверка на ОДЗ
*/
double ln(double a, std::string &output_result) {
   if (a <= 0) {
      out_error(output_result, "Неверный ввод. Диапазон начинатся от 0");
      return false;
   }
   return log(a);
}

/*
Функиця вычисления логарифма с основанием b и числом a
На вход поступают два аргумента a и b, оба типа double
Переменная b является основанием логарифма
Переменная а является числом
Также в параметрах есть output_result - нужна для выведения ошибки на экран
Есть дополнительная проверка на ОДЗ
*/
double logn(double a, double b, std::string &output_result) {
   if (a < 0 || b <= 0 || b == 1.0) {
      out_error(output_result, "Неверный ввод. Проверьте диапазон аргументов.");
      return false;
   }
   return log(b) / log(a);
}
//Функция вычисления числа а степени 2.0 |На вход поступает аргумент а типа double
double pow2(double a) {
   return pow(a, 2.0);
}

/*
Функция вычисления числа a  от степени n
На вход поступают два аргумента a и b, оба типа double
*/
double pown(double a, double b) {
   return pow(a, b);
}

/*
Функция вычисления числа 10 со степенью n, т.е. 10 ^ n
На вход поступает аргумент а типа double в качестве степени числа 10
*/
double pow10n(double a) {
   return pow(10, a);
}

/*
Функция кважратного корня
На вход поступает аргумент а типа double
output_result - нужна для выведения ошибки на экран
Есть дополнительная проверка на ОДЗ
*/
double sqrt2(double a, std::string &output_result) {
   if (a < 0) {
      out_error(output_result, "Неверный ввод. Диапазон начинатся от 0");
      return false;
   }
   return sqrt(a);
}

/*
Функция sqrtn - функция корня, в котором есть дополнительная проверка
На вход поступает два аргуемнта a и b, оба типа double
Переменная a является числом, из которого нужно вычислить корень
Переменная b является числом для степени корня
Также в параметрах есть output_result - нужна для выведения ошибки на экран
*/

double sqrtn(double a, double b, std::string &output_result) {
   //Если остаток равен 0, то значит степень четная
   if (std::fmod(b, 2.0) == 0.0 && a < 0) {
      out_error(output_result, "Неверный ввод. Диапазон начинается от 0");
      return false;
   }
   // Возвращаем результат вычисления корня
   return std::pow(b, 1.0 / a);
}


//Функция для вычисления остатка от двух чисел
double MOD(double a, double b) {
   return fmod(a, b);
}

//Функция для вычисления абсолютного значения числа
double modul(double a) {
   return fabs(a);
}

//Функция для вычисления выражения 1/x, где на вход поступает аргумент а типа double
double delete_1(double a, std::string &output_result) {
   if (a == 0.0) { // По идеи, что вещественное число b должно быть равно 0.0
      out_error(output_result, "Деление на 0 запрещено!");
      return false;
   }
   else {
      return 1.0 / a;
   }

}

//Функция для вычисления экспоненты | На вход поступает аргумент а типа double
double exponenta(double a) {
   return exp(a);
}

//---------------------------Математические функции---------------------------