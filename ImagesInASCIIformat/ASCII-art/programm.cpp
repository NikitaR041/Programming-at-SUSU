#include <menu.hpp>
#include <filesystem>
#include <graphics.h>

using namespace std;
using namespace filesystem;

int wx = 500, wy = 600; //������� ����
int dx=200, dy=108; //������� ����
string filename=""; //��� �����
fstream file;

int main(void){
   initwindow(wx, wy, "ASCII-arts");
   draw_menu();
   //����� ��� ������
   if(!exists("Arts")) create_directory("Arts");
   cycle();
   file.close();
   closegraph();
   return 0;
}