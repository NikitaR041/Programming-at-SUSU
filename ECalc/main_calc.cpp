#include <iostream>
#include <cmath>
#include <locale.h>
#include "Button.h"
#include "Math_for_calc.h"
#include "Button_processing.h"
#include "graphics.h"

using namespace std;

int main() {
    //-----������_�_������������_�����_�����-----
    //������ ���� ����� ����� ���������� �� ��� �� � ��� Oy
    //��� ��� ���� ������� ������������ � ������������ � .cpp ������, ��������� ��� Button
    int mass[2] = { 0 }; //�������� ��������� ������ ����� � �������
    int count_mass = 0; //���� ����� ���������� ��� ���������� � ������
    //-----������_�_������������_�����_�����-----

    //----���������� ���� ������ � ���������� ������� - ����� ��� ������� about_but()----
    my_stack m;
    stack_char b;
    stack_init(&m);
    stack_init(&b);

    //������������� ������ ����� output_result{} 
    string result_str{}; //����� ����� ������� ������������� �� ������ '=' 
    //������ ��� ������ ���������� � ��������� �� ���������� ����
    string output_result; 
    
    setlocale(LC_ALL, "rus"); //���������� ��� ����, ����� ��������� ����� ������� �������� �� ���������� ����
    initwindow(810, 530, "calculat"); //�������� ����������� ����
   
    draw_buts();
    
    //������� �� ������ ���� DEG �� RAG � ��������
    replace_deg_rag(&is_check_deg_rag);

    //� ����� ���������� ������ ������������, � ������������ ����� Button.h ��������� ����������� � ���� ��������
    while (true) { 
        //�������� ���������� �� ������� ���:
        int x = 0, y = 0;
        getmouseclick(WM_LBUTTONDOWN, x, y); // �������� ���������� ����
        if (x > 0 && y > 0) {
            // ������� ���������� � ������
            mass[count_mass] = x; // ���������� x
            mass[count_mass + 1] = y; // ���������� y
            // ����������� ������� �� 2, ��� ��� �� �������� ��� �������� (x � y)
            count_mass += 2;
            about_but(mass, &count_mass, output_result, result_str, m, b);
        }
    }
}