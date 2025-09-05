#include <menu.hpp>
#include <filesystem>
#include <graphics.h>

using namespace std;
using namespace filesystem;

int wx = 500, wy = 600; //Размеры окна
int dx=200, dy=108; //Размеры арта
string filename=""; //Имя файла
fstream file;

int main(void){
   initwindow(wx, wy, "ASCII-arts");
   draw_menu();
   //Папка для файлов
   if(!exists("Arts")) create_directory("Arts");
   cycle();
   file.close();
   closegraph();
   return 0;
}