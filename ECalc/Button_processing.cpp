#include <iostream>
#include <locale.h>
#include "Math_for_calc.h"
#include "graphics.h"


//������� ���������� ��������� ���������� ����� ������� ������������� ������ '='
void out_result(std::string& result_str, my_stack& m) {
    //�������� �� ��, ��� ���� ������������ ��� ((())) -> ��������� 0
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

//������� ���������� ������ ������, ������� ������������ ����� ������ �� ������
void out_expression(std::string& output_result, char type) {
    output_result += (type);
    //���� ��������� ��������� ���� ������ ������, � ������� ������ ���������� � 0
    settextstyle(SIMPLEX_FONT, HORIZ_DIR,3);
    outtextxy(10, 10, output_result.c_str());
}

//��� ������� �������� �� ����������� ����� ����� �� ���������� ����,� �������, ��� ��������� �������������� ������� sin, log � ��
void out_expression_str(std::string& output_result, const std::string type) {
    output_result += type;
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(10, 10, output_result.c_str());
}

//��� ������� ��������� �� ����������� ������ �� �����
void out_error(std::string& output_result, std::string error) {
    //cleardevice();
    output_result.clear();
    output_result += error;
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 3);
    outtextxy(10, 36, output_result.c_str());
}
//��� ������� ������� ������������� ��������e �� �����
void out_bottom_result_str(std::string& result_str, char symb) {
    result_str += symb; 
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
    outtextxy(10, 35, result_str.c_str());
}

//�������� ����� ��������� ��� ����������� ���� | ����������� ��� ������ �������������� ��������
void delete_expression(std::string& num_str, my_stack& m) {
    //����� ������ �������� ������������� ����������
    //������ ������ ������������� ��� �������� �����
    setfillstyle(SOLID_FILL, BLACK);
    bar(10, 35, 810, 70);
    out_result(num_str, m); //����� �� ������ �������� ����� � num_str, ������� ����� �������
    num_str.clear();

}

//�������, ������� ���������� ����� �������� ������� ������������ �����
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

//�������, ������� ���������� ����� ������� ������� ������������ ����� �� ������
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

//������� ���������� ��������� ���������� ����� � ���������
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

//��� ������� ������� �������������� ���� � ��������������� ���� ����� (�.�. ����� ���� char)
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
��� ������� ������������ ��� ������:
1)���� � ��������� ����� ���� ������� ���� �����
2)���� � ��������� ����� ���� ��� �����

������� ����� ��������� ����, ��� operation_result, �� ������� merging_two_numbers ��������� ��� ������� ���������
�.�. � ������� ������� �� ��������� �������������� ��������, � ����� ��������� ��� �� � ������� ����� ��� �����-���� �������������� ����
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
        //����� ������� � �������������� ����� ������, ���� �� ����, �� ����� � ������� �� ���������, ���� ���, �� ��������� 0
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
    //���� ����� ���� ����� ��������� ������
    else if (stack_isempty(&b) == true) {
        *priority = 0;
    }//� ���� ������ ����� ��������, ��� ���� ������������ ������ ((4+4))->((8)) -> ������ ���� (4)

}

//��� ������� ��������� �������������� �������� (+,-,*,/) � ����� ����������� ���� double
//���� ������ �������� �������� ������, �� �� ����� ���� ����� ����� 0
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
        if (div_digits(n2, n1, output_result) != false) { // ���� ������� �� ����
            stack_push(&m, div_digits(n2, n1, output_result));
        }
        else {
            n2 = 0.0;
            n1 = 0.0;
            out_error(output_result, "������� �� 0 ���������!");
            *is_check_del = true;
        }
        stack_pop(&b);
    }
}

//������� �������� �� ����� ������� ����� �� ���� string � ��� double ��� ����������� ���������� 
void savestr(std::string& num_str,my_stack& m) {
    if (num_str != "") {
        //��������� ����� ������� �� ���� str � ��� double
        stack_push(&m, std::stod(num_str));
        //������� ������
        num_str.clear();
    }
}

//��� ������� ���������� ������ �����, ����� ������������ ���������� �������� (��������� �� ��������)
//�������� �� ���������, ����� ������������ ����� �� ������������� ������, �� ������� ���������� ����� ���������� � ����������� ���, ��� ������� ������������� ������
void is_singular(my_stack& m, stack_char& b,int* priority, int* priority_skb_o, std::string& output_result) {
    int its_true = false;
    char syb;
    while (its_true == false) {
        if (stack_top(&b) != '(') {
            merging_two_numbers(priority, m, b, output_result);
        }
        else if (stack_top(&b) == '(') {
            its_true = true;
            stack_pop(&b); // ������� '('
            //������ ������ ����������, � ����� � ������� �����, ���� ���� ?, ���� ������, �� ������ ���������
            syb = stack_top(&b);
            arith_switch(syb, priority, b); //������� ���������� ����� �������������� � �����
            *priority_skb_o -= 1;
        }
    }
}

//��� ������� ��������� ������ ����� '-', �� '+' | ������������ ��� ������� abs
void delete_sub_unary(int* priority, stack_char& b) {
    //�������
    char plus = '+';
    stack_pop(&b); //������ ���� �������� '-'
    arith_switch(plus, priority, b);
    switch_arith_push(plus, b);
}

//��� ������� ��������� ������ ����� '-', �� '+'
void delete_sub(int* priority, my_stack& m, stack_char& b) {
    //��� �������� �������: 5-3 -> 5+(-3), ��� (-3) - ��� ��� double, � �� ��������� ��� ���� '-' - char � '3' - int
    double n = 0.0;
    char plus = '+';
    //�������
    stack_pop(&b); //������ ���� �������� '-'

    arith_switch(plus, priority, b);
    switch_arith_push(plus, b);
    
    n = n - stack_top(&m); //������� �����, ������� ������ ���� ������������� � �������� ���
    stack_pop(&m); //������� �����, ������� ������ ���� �������������
    stack_push(&m, n); //������� �� �� �����, �� ��� � ����������
}

