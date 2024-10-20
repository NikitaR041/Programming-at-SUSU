using System;
using System.Collections.Generic;
using System.Diagnostics.Metrics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AIS
{
    internal class Basket
    {
        //Динамическая память, в котором хранятся объекты танков - корзина
        private static List<TypeTank> elem = new List<TypeTank>();
        private static bool IsEmpty = false; //Проверка, что д.п. пуста

        //Дальше реализация управления с паматью
        private static void PrintTank(int x, int y,  List<TypeTank> m_tank, byte active_ind) {
            if (m_tank.Count == 0)
            {
                Console.SetCursorPosition(x, y);
                Console.WriteLine("Корзина пуста.");
                return;
            }
            Console.BackgroundColor = ConsoleColor.Magenta;
            Console.ForegroundColor = ConsoleColor.Green;

            for (int i = 0; i < m_tank.Count; i++)
            {
                Console.SetCursorPosition(x, y + i);
                Console.Write($"Танк {m_tank[i].Name} - цена {m_tank[i].Price}");
            }

            if (active_ind < m_tank.Count)
            {
                Console.BackgroundColor = ConsoleColor.Black;
                Console.ForegroundColor = ConsoleColor.Green;
                Console.SetCursorPosition(x, y + active_ind);
                Console.Write($"Танк {m_tank[active_ind].Name} - цена {m_tank[active_ind].Price}");
            }
        }
        private static TypeTank? SelectTankItem(int x, int y, List<TypeTank> m_tank) {
            //DrawLine();
            Console.CursorVisible = false;
            bool isWorking = true;
            byte activ_ind = 0;
            while (isWorking)
            {
                PrintTank(x, y, m_tank, activ_ind);
                ConsoleKeyInfo info = Console.ReadKey();
                switch (info.Key)
                {
                    //Удаление определенного элемента из корзины
                    case ConsoleKey.Backspace:
                        return m_tank[activ_ind];
                        //return m_tank[activ_ind];
                    case ConsoleKey.UpArrow:
                        // защита от выхода
                        if (activ_ind > 0) activ_ind--;
                        break;
                    case ConsoleKey.DownArrow:
                        // защита от выхода
                        if (activ_ind < m_tank.Count - 1) activ_ind++;
                        break;
                    case ConsoleKey.Spacebar:
                        isWorking = false;
                        break;
                    default:
                        return null;
                }
            }
            Console.CursorVisible = true;
            return null;
        }

        //Добавление в танка в корзину
        public static void AddInBasket(TypeTank tank) {
            elem.Add(tank);
            IsEmpty = true;
            Console.SetCursorPosition(35, 25);
            Console.WriteLine($"Ваш танк {tank.Name} добавлен в корзину!");
        }

        //Удаление танка из корзины
        public void DeleteInBasket(TypeTank tank) {
            if (elem.Count > 0) 
            {
                elem.Remove(tank);
                Console.WriteLine($"Ваш танк {tank.Name} удален из корзины!");
            }
            else {
                Console.WriteLine($"Нет такого танка {tank.Name} из корзины!");
                IsEmpty = false;
            }
        }

        //Получение цены от танка
        public void GetElemPrice()
        {
            int total = 0;
            foreach (var item in elem)
            {
                total += item.Price;
            }
            Console.SetCursorPosition(40, 8);
            Console.WriteLine($"Ваша конечная цена: {total}");
        }

        public void ShowElemInBasket() {
            Console.Clear();
            Menu.DrawLine();
            
            ConsoleKeyInfo info;
            TypeTank obj = null;
            bool active_while = true;
            bool flag = false;
            bool flag_text = false;
            
            //Первое событие - пустая корзина
            while (active_while == true && IsEmpty == false) {
                Console.SetCursorPosition(35, 9);
                Console.WriteLine("Ваша Корзина пуста! Нажмите на Escape для выхода!");
                info = Console.ReadKey();
                if (info.Key == ConsoleKey.Escape) {
                    active_while = false;
                    return;
                }
            }

            //Второе собитие - подтверждеине заказа
            while (active_while == true && IsEmpty == true && flag == false) {
                if (flag_text == false) {
                    Console.SetCursorPosition(40, 7);
                    Console.WriteLine("Вы сейчас находитесь в событии подтверждения заказа...");
                    Console.SetCursorPosition(40, 8);
                    Console.WriteLine("Для подтверждения заказа нажмите Tab, иначе Escape!");
                    PrintTank(50, 10, elem, 0);
                    flag_text = true;
                }
                info = Console.ReadKey();
                if (info.Key == ConsoleKey.Escape)
                {
                    active_while = false;
                    flag_text = false;
                    flag = true;
                }
                else if (info.Key == ConsoleKey.Tab) {
                    Console.Clear();
                    Menu.DrawLine();
                    Console.SetCursorPosition(50, 1);
                    Console.WriteLine("Для выхода нажмите Escape");
                    Console.SetCursorPosition(40, 7);
                    Console.WriteLine("Спасибо за Вашу покупку! Вот Ваш чек!");
                    GetElemPrice();
                    PrintTank(50, 10, elem, 0);
                    info = Console.ReadKey(); 
                    active_while = false;
                    return;
                }
            }

            //Третье событие - редактирование
            while (active_while == false && IsEmpty == true && flag == true) {
                if (flag_text == false) {
                    Console.Clear();
                    Menu.DrawLine();
                    Console.SetCursorPosition(40, 7);
                    Console.WriteLine("Вы сейчас находитесь в событии редактирование заказа...");
                    Console.SetCursorPosition(40, 8);
                    Console.WriteLine("Для удаление товара нажмите на Backspace!");
                    Console.SetCursorPosition(40, 9);
                    Console.WriteLine("Для выхода из редактирования нажмите на кнопку Escape");
                    flag_text = true;
                }

                if (elem.Count != 0) { PrintTank(50, 10, elem, 0); }

                info = Console.ReadKey(); //Предположение, что пользователь будет двигать список
                if (elem.Count == 0)
                {
                    Console.Clear();
                    Menu.DrawLine();
                    Console.SetCursorPosition(35, 7);
                    Console.WriteLine("Извините, но вам нечего удалять!");
                    Console.SetCursorPosition(35, 8);
                    Console.WriteLine("Для выхода нажмите на любую кнопку!");
                    info = Console.ReadKey(); 
                    active_while = false;
                    return;
                }
                else if (elem.Count > 0 && info.Key != ConsoleKey.Escape)
                {
                    obj = SelectTankItem(50, 10, elem);
                    DeleteInBasket(obj);
                    flag_text = false;
                    Console.WriteLine("Удалил элемент!");
                }
                else if (info.Key == ConsoleKey.Escape) {
                    active_while = true;
                    flag_text = false;
                    flag = false;
                    return;
                }
            }
        }
    }
}
