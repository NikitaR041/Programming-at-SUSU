using System;
using System.ComponentModel.Design;
using System.Runtime.InteropServices;

/*
Лабораторная работа 4.
Разработка АИС "Онлайн-заказ" с использованием ООП.

Моя предметная область этой л/р 4 - продажа различных запчастей танков, а также самих танков.

Здесь будет находится основной цикл по обработке 

Если что активных состояний может быть много
active = -1 - Меню 
active = -2 - Корзина
active = -3 - Выход
*/

namespace AIS
{
    internal class Program : Menu
    {
        static void Main(string[] args) 
        {
            string[] m = { "Пойти за покупками!", "Смотреть корзину!", "История танков!" };

            bool isWorking = true; //Означает, что цикл будет работать до тех пор, когда мы не выйдем
            int active = -1; // Означает, что мы будем смотреть на главное меню
            int is_clear_window = 0;

            DrawLine();
            while (isWorking) {
                if (is_clear_window == 1) {
                    Console.Clear();
                    DrawLine();
                    is_clear_window = 0;
                    Console.WriteLine("Hellp1313231");
                }
                active = SelectMenuItem(50,10,m);
                switch (active) {
                    case 0:
                        KatalogTypeTanks();
                        is_clear_window = 1;

                        break;
                    case 1:
                        //Console.Clear();
                        break;
                    case 2:
                        //Console.Clear()
                        break;
                    default:
                        break;
                }

            }
            Console.ReadLine();
        }
    }
}