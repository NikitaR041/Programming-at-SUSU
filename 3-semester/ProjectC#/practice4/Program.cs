using System;
using System.ComponentModel.Design;
using System.Runtime.InteropServices;

/*
Лабораторная работа 4.
Разработка АИС "Онлайн-заказ" с использованием ООП.

Моя предметная область этой л/р 4 - продажа различных запчастей танков, а также самих танков.
*/

namespace AIS
{
    internal class Program : Menu
    {
        static void Main(string[] args) 
        {
            string[] m = { "Пойти за покупками!", "Смотреть корзину!", "История танков!" };

            Menu.PrintManual(1);
            Basket basket = new Basket();

            bool isWorking = true; //Означает, что цикл будет работать до тех пор, когда мы не выйдем
            byte active = 255; // Означает, что мы будем смотреть на главное меню
            byte is_clear_window = 0;

            DrawLine();
            Menu.PrintManual(3);
            while (isWorking) {
                if (is_clear_window == 1) {
                    Console.Clear();
                    DrawLine();
                    Menu.PrintManual(1);
                    Menu.PrintManual(3);
                    is_clear_window = 0;
                }
                active = SelectMenuItem(50,10,m);
                switch (active) {
                    case 0:
                        KatalogTypeTanks();
                        is_clear_window = 1;
                        break;
                    case 1:
                        basket.ShowElemInBasket();
                        is_clear_window = 1;
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