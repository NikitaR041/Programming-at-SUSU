#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>
#include <fstream>
#include<graphics.h>

using namespace std;

extern int wx, wy; //������� ����
extern string filename; //��� �����
extern int dx, dy; //������� ����
void cycle(); //�������� ���� ��� �������� �������
void generate(); //������� �����������
void clear_all(); //�������� ��������
void prov_pole(int x, int y); //�������� ������
void use_but(int i); //������������� ������
void draw_menu(); //��������� ����
string input_word(const int startX, const int startY, const int endX, const int endY, int i); //��������� ����� ����� ��� ��������� � �� ����������
void about_programm(); //� ���������
#endif  /* MENU */