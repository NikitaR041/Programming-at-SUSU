#include <iostream>
#include <cmath>
#include <locale.h>
#include "Button.h"
#include "Math_for_calc.h"
#include "Button_processing.h"
#include "graphics.h"

using namespace std;

int main() {
    //-----Массив_с_координатами_клика_мышью-----
    //Каждый клин мышью имеет координаты по оси Ох и оси Oy
    //Эти два ниже объекта используются в заголовочном и .cpp файлах, названная как Button
    int mass[2] = { 0 }; //Хранение координат одного клика в массиве
    int count_mass = 0; //Даст ответ количество уже знаесенных в массив
    //-----Массив_с_координатами_клика_мышью-----

    //----Объявление двух стеков и строкового массива - нужно для функции about_but()----
    my_stack m;
    stack_char b;
    stack_init(&m);
    stack_init(&b);

    //Промежуточный массив перед output_result{} 
    string result_str{}; //Нужна после нажатия пользователем на кнопку '=' 
    //Массив для вывода результата и выражения на диалоговое окно
    string output_result; 
    
    setlocale(LC_ALL, "rus"); //Необходимо для того, чтобы получился вывод русских символов на диалоговое окно
    initwindow(810, 530, "calculat"); //Создание диалогового окна
   
    draw_buts();
    
    //функция по замене типа DEG на RAG и наоборот
    replace_deg_rag(&is_check_deg_rag);

    //В цикле происходит работа калькулятора, в заголовочном файле Button.h расписаны комментарии к этим функциям
    while (true) { 
        //Получаем координаты из нажатия ЛКМ:
        int x = 0, y = 0;
        getmouseclick(WM_LBUTTONDOWN, x, y); // Получаем координаты мыши
        if (x > 0 && y > 0) {
            // Заносим координаты в массив
            mass[count_mass] = x; // Записываем x
            mass[count_mass + 1] = y; // Записываем y
            // Увеличиваем счетчик на 2, так как мы записали два элемента (x и y)
            count_mass += 2;
            about_but(mass, &count_mass, output_result, result_str, m, b);
        }
    }
}