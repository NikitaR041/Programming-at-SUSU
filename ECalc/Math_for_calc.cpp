#include <iostream>
#include <cmath>
#include "Math_for_calc.h"
#include "Button_processing.h"


//--------stack_digit--------

//������������� ���������� �����
void stack_init(my_stack *a) {
   a->top = -1;
}

//���������� �������� � ��������� ����
void stack_push(my_stack *a, double v) {
   if (a->top == 1000) {
      return;
   }
   a->top += 1;
   a->mass[a->top] = v;
}

//�������� �������� �������� �� ���������� �����
void stack_pop(my_stack *a) {
   a->mass[a->top] = 0;
   a->top -= 1;
}

//��������� �������� �������� �� ���������� �����
double stack_top(my_stack *a) {
   return a->mass[a->top];
}

//�������� �� ������� ���������� �����
double stack_isempty(my_stack *a) { // ���������, ��� ���� ����
   if (a->top == -1) {
      return true;
   }
   else {
      return false;
   }
}
//----------------stack_digit----------------



//----------------stack_char----------------

// ������������� ��������������� �����
void stack_init(stack_char *b) {
   b->top = -1;
}

//���������� �������� � �������������� ����
void stack_push(stack_char *b, char v) {
   if (b->top == 1000) {
      return;
   }
   b->top += 1;
   b->mass_char[b->top] = v;
}

//�������� �������� �������� �� ��������������� �����
void stack_pop(stack_char *b) {
   b->mass_char[b->top] = 0;
   b->top -= 1;
}

//��������� �������� �������� �� ��������������� �����
int stack_top(stack_char *b) {
   return b->mass_char[b->top];
}

//�������� �� ������� ��������������� �����
int stack_isempty(stack_char *b) {
   if (b->top == -1) {
      return true;
   }
   else {
      return false;
   }
}
//----------------stack_char----------------

//---------------------------�������������� ��������---------------------------
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
   if (b == 0.0) { // �� ����, ��� ������������ ����� b ������ ���� ����� 0.0
      out_error(output_result, "������� �� 0 ���������!");
      return -1;
   }
   else {
      return a / b;
   }
}
//---------------------------�������������� ��������---------------------------

//---------------------------�������������� �������---------------------------
/*
������� ���������� ���������� �� ����� a
�� ���� ��������� �������� a ���� double
����� � ���������� ���� output_result - ����� ��� ��������� ������ �� �����
���� �������������� �������� �� ���
*/
double fact(double a, std::string &output_result) {
   double result = 1;
   if (a < 0) {
      out_error(output_result, "�������� ����. �������� ���������� � ����.");
      return false;
   }
   for (int i = 1; i <= a; ++i) {
      result *= i;
   }
   return result;
}

//������� ������ | �� ���� ��������� �������� a ���� double � flag ���� int, ������� ��������, ��� ������������ ���� �������� � ��������
double sinus(double a, int *check_DEG_RAG) {
   if (*check_DEG_RAG == true) {
      return sin(a); //�� �������� � ������� �������� ��������
   }
   else {
      return sin((a) * (PI / 180.0)); //�� �������� � ������� �������� ��������
   }
}

//������� �������� | �� ���� ��������� �������� a ���� double � flag ���� int, ������� ��������, ��� ������������ ���� �������� � ��������
double cosinus(double a, int *check_DEG_RAG) {
   if (*check_DEG_RAG == true) {
      return cos(a);//�� �������� � ������� �������� ��������
   }
   else {
      return cos((a) * (PI / 180.0)); //�� �������� � ������� �������� ��������
   }
}

/*
������� ��������
�� ���� ��������� �������� a ���� double � flag ���� int, ������� ��������, ��� ������������ ���� �������� � ��������
����� � ���������� ���� output_result - ����� ��� ��������� ������ �� �����
���� �������������� �������� �� ���
*/
double tangent(double a, int *check_DEG_RAG, std::string &output_result) {
   double num = 0;
   //���� ���� � ��������
   if (*check_DEG_RAG != true) {
      for (int i = 1; i <= 10; i++) {
         if (a == 90 * i || a == 270 * i) {
            out_error(output_result, "�������� ����. ������� �� ����������");
            return -1; //���������� ������
         }
         else {
            //��� �������� ��������� �� �����
            if (a < 90 * i && (a) < 270 * i) break;
            //�.�. ����� ������ ��������, ����� ������� � ���������
            continue;
         }
      }
      return  tan((a) * (PI / 180.0)); //�� �������� � �������� � �������� �����
   }
   else {
      num = (PI / 2);
      for (int i = 0; i < 10; i++) {
         if (a == num + PI * i || a == 3 * num + PI * i) {
            out_error(output_result, "�������� ����. ������� �� ����������");
            return -1; //���������� ������
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
�������� ����������
�� ���� ��������� �������� a ���� double � flag ���� int, ������� ��������, ��� ������������ ���� �������� � ��������
����� � ���������� ���� output_result - ����� ��� ��������� ������ �� �����
���� �������������� �������� �� ���
*/
double cotangent(double a, int *check_DEG_RAG, std::string &output_result) {
   //���� ������ � ��������
   if (*check_DEG_RAG != true) {
      for (int i = 0; i < 10; i++) {
         if (a == 0 + 180 * i || a == 180 + 180 * i) {
            out_error(output_result, "�������� ����. ��������� �� ����������");
            return -1; //���������� ������
         }
         else {
            //��� �������� ��������� �� �����
            if (a < 0 + 180 * i || a < 180 + 180 * i) break;
            //�.�. ����� ������ ��������, ����� ������� � ���������
            continue;
         }
      }
      //�� �������� � �������� � �������� �����
      return cos((a) * (PI / 180.0)) / sin((a) * (PI / 180.0));
   }
   else {
      for (int i = 0; i < 10; i++) {
         if (a == PI * i || a == PI + PI * i) {
            out_error(output_result, "�������� ����. ��������� �� ����������");
            return -1; //���������� ������
         }
         else {
            //��� �������� ��������� �� �����
            if (a < 0 + 180 * i || a < 180 + 180 * i) break;
            //�.�. ����� ������ ��������, ����� ������� � ���������
            continue;
         }
      }
      //�� �������� � �������� � �������� �����
      return cos(a) / sin(a);
   }
}

/*
������� ��������� ������
�� ���� ��������� �������� a ���� double � flag ���� int, ������� ��������, ��� ������������ ���� �������� � ��������
����� � ���������� ���� output_result - ����� ��� ��������� ������ �� �����
���� �������������� �������� �� ���
*/
double arcsinus(double a, std::string &output_result) {
   if (-1.0 <= a && a <= 1.0) {
      return asin(a);
   }
   out_error(output_result, "�������� ����. �������� ������ ���� �� -1 �� 1");
   return -1;
}
/*
������� ��������� �������
�� ���� ��������� �������� a ���� double � flag ���� int, ������� ��������, ��� ������������ ���� �������� � ��������
����� � ���������� ���� output_result - ����� ��� ��������� ������ �� �����
���� �������������� �������� �� ���
*/
double arccosinus(double a, std::string &output_result) {
   if (-1.0 <= a && a <= 1.0) {
      return acos(a);
   }
   out_error(output_result, "�������� ����. �������� ������ ���� �� -1 �� 1");
   return -1;
}

/*
������� ��������� ��������
�� ���� ��������� �������� a ���� double � flag ���� int, ������� ��������, ��� ������������ ���� �������� � ��������
*/
double arctangent(double a,int *check_DEG_RAG) {
   double num = 0;
   //���� �������� � ��������, �� ���������� � ��������
   if (*check_DEG_RAG != true) num = a * (PI / 180.0);
   else  num = a; //�������� � ��������

   return atan(num);
}

/*
������� ��������� ����������
�� ���� ��������� �������� a ���� double � flag ���� int, ������� ��������, ��� ������������ ���� �������� � ��������
��������, � arccotangent(p/2)
*/
double arccotangent(double a, int *check_DEG_RAG) {
   double num = 0;
   //���� �������� � ��������, �� ���������� � ��������
   if (*check_DEG_RAG != true) num = a * (PI / 180.0);
   else  num = a; //�������� � ��������

   return atan(1.0 / num);
}
//������� ��������� � ���������� 2 | �� ���� ��������� �������� � ���� double, ���������� ������ | � ������� ���� �������������� �������� �� ���
double log_2(double a, std::string &output_result) {
   if (a <= 0) {
      out_error(output_result, "�������� ����. �������� ��������� �� 0");
      return false;
   }
   return log2(a);
}
/*
������� ����������� ���������
�� ���� ��������� �������� � ���� double
����� � ���������� ���� output_result - ����� ��� ��������� ������ �� �����
� ������� ���� �������������� �������� �� ���
*/
double lg(double a, std::string &output_result) {
   if (a <= 0) {
      out_error(output_result, "�������� ����. �������� ��������� �� 0");
      return false;
   }
   return log10(a);
}

/*
������� ������������ ���������
�� ���� ��������� �������� � ���� double
����� � ���������� ���� output_result - ����� ��� ��������� ������ �� �����
� ������� ���� �������������� �������� �� ���
*/
double ln(double a, std::string &output_result) {
   if (a <= 0) {
      out_error(output_result, "�������� ����. �������� ��������� �� 0");
      return false;
   }
   return log(a);
}

/*
������� ���������� ��������� � ���������� b � ������ a
�� ���� ��������� ��� ��������� a � b, ��� ���� double
���������� b �������� ���������� ���������
���������� � �������� ������
����� � ���������� ���� output_result - ����� ��� ��������� ������ �� �����
���� �������������� �������� �� ���
*/
double logn(double a, double b, std::string &output_result) {
   if (a < 0 || b <= 0 || b == 1.0) {
      out_error(output_result, "�������� ����. ��������� �������� ����������.");
      return false;
   }
   return log(b) / log(a);
}
//������� ���������� ����� � ������� 2.0 |�� ���� ��������� �������� � ���� double
double pow2(double a) {
   return pow(a, 2.0);
}

/*
������� ���������� ����� a  �� ������� n
�� ���� ��������� ��� ��������� a � b, ��� ���� double
*/
double pown(double a, double b) {
   return pow(a, b);
}

/*
������� ���������� ����� 10 �� �������� n, �.�. 10 ^ n
�� ���� ��������� �������� � ���� double � �������� ������� ����� 10
*/
double pow10n(double a) {
   return pow(10, a);
}

/*
������� ����������� �����
�� ���� ��������� �������� � ���� double
output_result - ����� ��� ��������� ������ �� �����
���� �������������� �������� �� ���
*/
double sqrt2(double a, std::string &output_result) {
   if (a < 0) {
      out_error(output_result, "�������� ����. �������� ��������� �� 0");
      return false;
   }
   return sqrt(a);
}

/*
������� sqrtn - ������� �����, � ������� ���� �������������� ��������
�� ���� ��������� ��� ��������� a � b, ��� ���� double
���������� a �������� ������, �� �������� ����� ��������� ������
���������� b �������� ������ ��� ������� �����
����� � ���������� ���� output_result - ����� ��� ��������� ������ �� �����
*/

double sqrtn(double a, double b, std::string &output_result) {
   //���� ������� ����� 0, �� ������ ������� ������
   if (std::fmod(b, 2.0) == 0.0 && a < 0) {
      out_error(output_result, "�������� ����. �������� ���������� �� 0");
      return false;
   }
   // ���������� ��������� ���������� �����
   return std::pow(b, 1.0 / a);
}


//������� ��� ���������� ������� �� ���� �����
double MOD(double a, double b) {
   return fmod(a, b);
}

//������� ��� ���������� ����������� �������� �����
double modul(double a) {
   return fabs(a);
}

//������� ��� ���������� ��������� 1/x, ��� �� ���� ��������� �������� � ���� double
double delete_1(double a, std::string &output_result) {
   if (a == 0.0) { // �� ����, ��� ������������ ����� b ������ ���� ����� 0.0
      out_error(output_result, "������� �� 0 ���������!");
      return false;
   }
   else {
      return 1.0 / a;
   }

}

//������� ��� ���������� ���������� | �� ���� ��������� �������� � ���� double
double exponenta(double a) {
   return exp(a);
}

//---------------------------�������������� �������---------------------------