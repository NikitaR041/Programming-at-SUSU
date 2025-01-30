#include <iostream>
#include <locale.h>
#include "Math_for_calc.h"
#include "graphics.h"


//Функция отображает результат вычисления после нажатия пользователем конпки '='
void out_result(std::string& result_str, my_stack& m) {
    //Проверка на то, что если пользователь ввёл ((())) -> результат 0
    if (stack_isempty(&m) == true) {
        result_str.clear();
        result_str += std::to_string(0);
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
        outtextxy(10, 35, result_str.c_str());
    }
    else {
        result_str.clear();
        result_str += std::to_string(stack_top(&m));
        settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
        outtextxy(10, 35, result_str.c_str());
    }
}

//Функция отображает каждый символ, который пользователь может нажать на кнопку
void out_expression(std::string& output_result, char type) {
    output_result += (type);
    //Если указатель спустился ниже своего уровня, а уровень должен начинаться с 0
    settextstyle(SIMPLEX_FONT, HORIZ_DIR,3);
    outtextxy(10, 10, output_result.c_str());
}

//Это функция отвечает за отображение целых строк на диалоговом окне,к примеру, для различных математических функций sin, log и тд
void out_expression_str(std::string& output_result, const std::string type) {
    output_result += type;
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(10, 10, output_result.c_str());
}

//Это функция отвевчает за отображение ошибки на экран
void out_error(std::string& output_result, std::string error) {
    //cleardevice();
    output_result.clear();
    output_result += error;
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(10, 36, output_result.c_str());
}
//Это функция выводит промежуточное вычилениe на экран
void out_bottom_result_str(std::string& result_str, char symb) {
    result_str += symb; 
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
    outtextxy(10, 35, result_str.c_str());
}

//Удаление части выражения для исправления вида | применяется для унаных математических функциях
void delete_expression(std::string& num_str, my_stack& m) {
    //Здесь должны показать промежуточное вычисление
    //Делаем черный прямоугольник для удаление числа
    setfillstyle(SOLID_FILL, BLACK);
    bar(10, 35, 810, 70);
    out_result(num_str, m); //Здесь мы заного добавили число в num_str, который ранее очищали
    num_str.clear();

}

//Функция, которая определяет какую бинарную функцию пользователь нажал
void switch_binary_func(char type, double a, double b,int* is_check_error,std::string& output_result, my_stack& m) {
    if (type == 'B') {
        if (sqrtn(a, b, output_result) == false) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, sqrtn(a, b, output_result));
        }
    }
    else if (type == 'D') {
        stack_push(&m, pown(a, b));
    }
    else if (type == 'G') {
        if (logn(a, b, output_result) == false) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, logn(a, b, output_result));
        }
    }
    else if (type == 'V') {
        stack_push(&m, MOD(a, b));
    }
}

//Функция, которая определяет какую унарную функцию пользователь нажал на кнопку
void switch_unary_func(char type, double a,int* is_check_error,int* check_DEG_RAG, std::string& output_result, my_stack& m) {
    if (type == 'A') {
        if (sqrt2(a, output_result) == false) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, sqrt2(a, output_result));
        }
    }
    else if (type == 'C') {
        stack_push(&m, pow2(a));
    }
    else if (type == 'E') {
        if (fact(a, output_result) == false) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, fact(a, output_result));
        }
    }
    else if (type == 'F') {
        if (log_2(a, output_result) == false) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, log_2(a, output_result));
        }
    }
    else if (type == 'H') {
        if (ln(a, output_result) == false) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, ln(a, output_result));
        }
    }
    else if (type == 'I') {
        if (lg(a, output_result) == false) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, lg(a, output_result));
        }
    }
    else if (type == 'K') {
        stack_push(&m, pow10n(a));
    }
    else if (type == 'L') {
        stack_push(&m, sinus(a, check_DEG_RAG));
    }
    else if (type == 'M') {
        stack_push(&m, cosinus(a, check_DEG_RAG));
    }
    else if (type == 'N') {
        if (tangent(a, check_DEG_RAG, output_result) == -1) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, tangent(a, check_DEG_RAG, output_result));
        }
    }
    else if (type == 'O') {
        if (cotangent(a, check_DEG_RAG, output_result) == -1) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, cotangent(a, check_DEG_RAG, output_result));
        }
    }
    else if (type == 'P') { 
        if (arcsinus(a, output_result) == -1) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, arcsinus(a, output_result));
        }
    }
    else if (type == 'Q') {
        if (arccosinus(a, output_result) == -1) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, arccosinus(a, output_result));
        }
    }
    else if (type == 'R') {
        stack_push(&m, arctangent(a, check_DEG_RAG));
    }
    else if (type == 'S') {
        stack_push(&m, arccotangent(a, check_DEG_RAG));
    }
    else if (type == 'T') {
        stack_push(&m, modul(a));
    }
    else if (type == 'W') {
        stack_push(&m, exponenta(a));
    }
    else if (type == 'X') {
        if (delete_1(a, output_result) == false) {
            *is_check_error = true;
        }
        else {
            stack_push(&m, delete_1(a, output_result));
        }

    }
}

//Функция определяет приоритет вычисления знака в выражении
void arith_switch(char type, int* priority, stack_char& b) {
    if (type == '+') {
        *priority = 1;
    }
    else if (type == '-') {
        *priority = 1;
    }
    else if (type == '*') {
        *priority = 2;
    }
    else if (type == '/') {
        *priority = 2;
    }
    else if (type == '(' || type == ')') {
        *priority = 0;
    }
    else if (stack_isempty(&b) == true) {
        *priority = 0; 
    }
}

//Это функция заносит арифметический знак в соответвстующмй типу стека (т.е. стеку типа char)
void switch_arith_push(char type, stack_char& b) {
    if (type == '+') {
        stack_push(&b, type);
    }
    else if (type == '-') {
        stack_push(&b, type);
    }
    else if (type == '*') {
        stack_push(&b, type);
    }
    else if (type == '/') {
        stack_push(&b, type);
    }
    else if (type == '(' || type == ')') {
        stack_push(&b, type);
    }
}

/*
Это функция обрабатывает два случая:
1)Если в численном стеке было введено одно число
2)Если в численном стеке были два числа

Функция почти повторяет себя, как operation_result, но функция merging_two_numbers необходим для длинных выражений
Т.е. в текущем моменте он вычисляет математическую операцию, а затем проверяет нет ли в глубине стека ещё какой-либо арифметический знак
*/
void merging_two_numbers(int* priority, my_stack& m, stack_char& b, std::string& output_result) {
    double n1 = 0.0, n2 = 0.0;
    char symb;
    n1 = stack_top(&m);
    stack_pop(&m);
    if (stack_isempty(&m) == true) {
        n2 = 0.0;
    }
    else {
        n2 = stack_top(&m);
        stack_pop(&m);
    }
    if (stack_top(&b) == '+') {
        stack_push(&m, sum_digits(n2, n1));
        stack_pop(&b);
        //Далее смотрим в арифметическом стеке символ, если он есть, то берем и смотрим на приоритет, если нет, то приоритет 0
        symb = stack_top(&b);
        arith_switch(symb, priority, b);
    }
    else if (stack_top(&b) == '-') {
        stack_push(&m, sub_digits(n2, n1));
        stack_pop(&b);
        symb = stack_top(&b);
        arith_switch(symb, priority, b);
    }
    else if (stack_top(&b) == '*') {
        stack_push(&m, mul_digits(n2, n1));
        stack_pop(&b);
        symb = stack_top(&b);
        arith_switch(symb, priority, b);
    }
    else if (stack_top(&b) == '/') {
        stack_push(&m, div_digits(n2, n1, output_result));
        stack_pop(&b);
        symb = stack_top(&b);
        arith_switch(symb, priority, b);
    }
    //Ниже может быть нужно исправить случаи
    else if (stack_isempty(&b) == true) {
        *priority = 0;
    }//В этом случаи нужно смотреть, что если пользователь введет ((4+4))->((8)) -> должно быть (4)

}

//Это функция выполняет математические операции (+,-,*,/) с двумя аргументами типа double
//Если второй агрумент является пустым, то за место него будет число 0
void operation_result(char type_symbol,std::string& output_result, int* is_check_del, my_stack& m, stack_char& b) {
    double n1 = 0.0, n2 = 0.0;
    n1 = stack_top(&m);
    stack_pop(&m);
    if (stack_isempty(&m)) {
        n2 = 0.0;
    }
    else {
        n2 = stack_top(&m);
        stack_pop(&m);
    }
    if (type_symbol == '+') {
        stack_push(&m, sum_digits(n2, n1));
        stack_pop(&b);
    }
    else if (type_symbol == '-') {
        stack_push(&m, sub_digits(n2, n1));
        stack_pop(&b);
    }
    else if (type_symbol == '*') {
        stack_push(&m, mul_digits(n2, n1));
        stack_pop(&b);
    }
    else if (type_symbol == '/') {
        if (div_digits(n2, n1, output_result) != false) { // Если деление на ноль
            stack_push(&m, div_digits(n2, n1, output_result));
        }
        else {
            n2 = 0.0;
            n1 = 0.0;
            out_error(output_result, "Деление на 0 запрещено!");
            *is_check_del = true;
        }
        stack_pop(&b);
    }
}

//Функция отвечает за явный перевод чисел из типа string в тип double для дальнейшего вычисления 
void savestr(std::string& num_str,my_stack& m) {
    if (num_str != "") {
        //Переводим явным образом из типа str в тип double
        stack_push(&m, std::stod(num_str));
        //Очистка строки
        num_str.clear();
    }
}

//Это функция примняется только тогда, когда пользователь пользуется скобками (выражения со скобками)
//Работает по приниципу, когда пользователь нажал на закрывающуюся скобку, то процесс вычисления сразу начинается и завершается тем, что удаляет открывающуюся скобку
void is_singular(my_stack& m, stack_char& b,int* priority, int* priority_skb_o, std::string& output_result) {
    int its_true = false;
    char syb;
    while (its_true == false) {
        if (stack_top(&b) != '(') {
            merging_two_numbers(priority, m, b, output_result);
        }
        else if (stack_top(&b) == '(') {
            its_true = true;
            stack_pop(&b); // Удаляем '('
            //Дальше должны посмотреть, а вдруг в глубине стека, есть знак ?, если скобка, то ничего страшного
            syb = stack_top(&b);
            arith_switch(syb, priority, b); //Сначала рассмотрим какая приоритетность у знака
            *priority_skb_o -= 1;
        }
    }
}

//Это функция выполняет замену знака '-', на '+' | используется для функции abs
void delete_sub_unary(int* priority, stack_char& b) {
    //Процесс
    char plus = '+';
    stack_pop(&b); //Должно быть удаление '-'
    arith_switch(plus, priority, b);
    switch_arith_push(plus, b);
}

//Это функция выполняет замену знака '-', на '+'
void delete_sub(int* priority, my_stack& m, stack_char& b) {
    //Как работает функция: 5-3 -> 5+(-3), где (-3) - это уже double, а не отдельные два вида '-' - char и '3' - int
    double n = 0.0;
    char plus = '+';
    //Процесс
    stack_pop(&b); //Должно быть удаление '-'

    arith_switch(plus, priority, b);
    switch_arith_push(plus, b);
    
    n = n - stack_top(&m); //Достаем число, которое должно быть отрицательным и отрицаем его
    stack_pop(&m); //Удаляем число, которое должно быть отрицательным
    stack_push(&m, n); //Заносим то же число, но уже с отрицанием
}

