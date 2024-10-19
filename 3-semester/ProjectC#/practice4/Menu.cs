//using practice4;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;

namespace AIS
{
    internal class Menu
    {
        //метод отвечает за вывод меню на экран
        public static void PrintMenu(int x, int y, string[] menu, int active_ind)
        {
            Console.BackgroundColor = ConsoleColor.Magenta;
            Console.ForegroundColor = ConsoleColor.Green;

            for (int i = 0; i < menu.Length; i++)
            {
                Console.SetCursorPosition(x, y + i);
                Console.Write(menu[i]);
            }

            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.Green;
            Console.SetCursorPosition(x, y + active_ind);
            Console.Write(menu[active_ind]);
        }

        //Метод обрабатывает выбор элемента меню пользователем
        public static byte SelectMenuItem(int x, int y, string[] menu)
        {
            //DrawLine();
            Console.CursorVisible = false;
            bool isWorking = true;
            byte activ_ind = 0;
            while (isWorking)
            {
                PrintMenu(x, y, menu, activ_ind);
                ConsoleKeyInfo info = Console.ReadKey();
                switch (info.Key)
                {
                    case ConsoleKey.Enter:
                        isWorking = false;
                        //Console.Clear();
                        return activ_ind; 
                        break;
                    case ConsoleKey.UpArrow:
                        // защита от выхода
                        if (activ_ind > 0) activ_ind--;
                        break;
                    case ConsoleKey.DownArrow:
                        // защита от выхода
                        if (activ_ind < menu.Length - 1) activ_ind++;
                        break;
                    case ConsoleKey.Escape:
                        return 255; // 255 означает выход из выбора
                    case ConsoleKey.Tab:
                        return 254; // 254 означает выход к каталогу типов танков
                    default:
                        break;
                }
            }
            Console.CursorVisible = true;
            return 253; //Но не факт
        }


        public static void KatalogTypeTanks() {
            //В любом случае нужно выводить текст для выхода из конкретного окна
            string[] types_tanks = { "Легкие танки", "Средние танки", "Тяжелые танки", "ПТ-САУ", "САУ" };
            byte type_id;
            
            bool active_while = true;
            while (active_while == true) {
                type_id = SelectMenuItem(50, 5, types_tanks);
                Console.Clear();
                DrawLine();
                switch (type_id)
                {
                    case 0:
                        LightTank();
                        break;
                    case 1:
                        //Средние танки
                        MediumTank();
                        break;
                    case 2:
                        //Тяжелые танки
                        HeavyTank();
                        break;
                    case 3:
                        //ПТ-САУ
                        TankDestroyer();
                        break;
                    case 4:
                        //САУ
                        SAVt();
                        break;
                    default: //По идеи сюда может попасть 255 и различные значение кроме [0;4]
                        active_while = false;
                        return;
                }
            }
        }

        static void LightTank() {
            //В любом случае нужно выводить текст для выхода из конкретного окна
            string[] m1_lighttanks = { "T-50-2", "AMX 13 75", "Type 62" };

            LightTank[] m2_lighttanks = new LightTank[3];

            m2_lighttanks[0] = new LightTank("T-50-2", "57 mm ZiS-4", "СССР", 60, 1000000, "Green");
            m2_lighttanks[1] = new LightTank("AMX 13 75", "75 mm SA 50", "США", 60, 5000000, "DarkBlue");
            m2_lighttanks[2] = new LightTank("Type 62", "100 mm Type 62", "Япония", 55, 1500000, "DarkGreen");

            ConsoleKeyInfo info;
            bool active_while = true;
            bool flag = false;
            while (active_while) {
                if (flag == false) { // flag == false нужна проверка на то, чтобы не запускать 100 одно и тоже сообщение
                    byte name_tank_id = SelectMenuItem(50, 2, m1_lighttanks);
                    Console.Clear();
                    DrawLine();
                    switch (name_tank_id)
                    {
                        case 0:
                            m2_lighttanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        case 1:
                            m2_lighttanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        case 2:
                            m2_lighttanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        default:
                            //Случай если из name_tank_id пользователь нажмёт на escape или tab
                            active_while = false;
                            flag = false;
                            return;
                    }
                }

                //По идеи здесь сообщение об выходе, чтобы выбрать другой танк
                info = Console.ReadKey(); // Читаем нажатую клавишу
                if (info.Key == ConsoleKey.Tab) // Проверяем на Escape
                {
                    flag = false;
                    Console.Clear();
                    DrawLine();
                }
                else if (info.Key == ConsoleKey.Escape) {
                    Console.WriteLine("Ты нажал на ESC");
                    active_while = false;
                    flag = false;
                    Console.Clear();
                    DrawLine();
                    return;
                }
            }
        }

        static void MediumTank() {
            //В любом случае нужно выводить текст для выхода из конкретного окна
            string[] m1_medtanks = { "T-34", "Centurion Mk. 7/1" };

            MediumTank[] m2_medtanks = new MediumTank[2];


            m2_medtanks[0] = new MediumTank("T-34", "76.2 mm F-34", "СССР", 40, 1500000, 60);
            m2_medtanks[1] = new MediumTank("Centurion Mk. 7/1", "105 mm L7", "Великобритания", 48, 1250000, 80);
            
            ConsoleKeyInfo info;
            bool active_while = true;
            bool flag = false;
            while (active_while)
            {
                if (flag == false)
                { // flag == false нужна проверка на то, чтобы не запускать 100 одно и тоже сообщение
                    byte name_tank_id = SelectMenuItem(50, 2, m1_medtanks);
                    Console.Clear();
                    DrawLine();
                    switch (name_tank_id)
                    {
                        case 0:
                            m2_medtanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        case 1:
                            m2_medtanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        default:
                            //Случай если из name_tank_id пользователь нажмёт на escape или tab
                            active_while = false;
                            flag = false;
                            return;
                    }
                }

                //По идеи здесь сообщение об выходе, чтобы выбрать другой танк
                info = Console.ReadKey(); // Читаем нажатую клавишу
                if (info.Key == ConsoleKey.Tab) // Проверяем на Escape
                {
                    flag = false;
                    Console.Clear();
                    DrawLine();
                }
                else if (info.Key == ConsoleKey.Escape)
                {
                    Console.WriteLine("Ты нажал на ESC");
                    active_while = false;
                    flag = false;
                    Console.Clear();
                    DrawLine();
                    return;
                }
            }
        }

        static void HeavyTank() {
            //В любом случае нужно выводить текст для выхода из конкретного окна
            string[] m1_hevtanks = { "ИС-2", "M103", "Maus" };

            HeavyTank[] m2_hevtanks = new HeavyTank[3];


            m2_hevtanks[0] = new HeavyTank("ИС-2", "122 mm D-25T", "СССР", 37, 5500000, 20);
            m2_hevtanks[1] = new HeavyTank("M103", "105 mm M68", "США", 35, 5250000, 20);
            m2_hevtanks[2] = new HeavyTank("Maus", "128 mm KwK 44", "Германия", 20, 8000000, 15);

            ConsoleKeyInfo info;
            bool active_while = true;
            bool flag = false;
            while (active_while)
            {
                if (flag == false)
                { // flag == false нужна проверка на то, чтобы не запускать 100 одно и тоже сообщение
                    byte name_tank_id = SelectMenuItem(50, 2, m1_hevtanks);
                    Console.Clear();
                    DrawLine();
                    switch (name_tank_id)
                    {
                        case 0:
                            m2_hevtanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        case 1:
                            m2_hevtanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        case 2:
                            m2_hevtanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        default:
                            //Случай если из name_tank_id пользователь нажмёт на escape или tab
                            active_while = false;
                            flag = false;
                            return;
                    }
                }

                //По идеи здесь сообщение об выходе, чтобы выбрать другой танк
                info = Console.ReadKey(); // Читаем нажатую клавишу
                if (info.Key == ConsoleKey.Tab) // Проверяем на Escape
                {
                    flag = false;
                    Console.Clear();
                    DrawLine();
                }
                else if (info.Key == ConsoleKey.Escape)
                {
                    Console.WriteLine("Ты нажал на ESC");
                    active_while = false;
                    flag = false;
                    Console.Clear();
                    DrawLine();
                    return;
                }
            }
        }

        static void TankDestroyer() {
            //В любом случае нужно выводить текст для выхода из конкретного окна
            string[] m1_destanks = { "Jagdpanther", "СУ-152", "Charioteer" };

            TankDestroyer[] m2_destanks = new TankDestroyer[3];

            m2_destanks[0] = new TankDestroyer("Jagdpanther", "88 mm Pak 43", "Германия", 46, 2890000, 5, 15);
            m2_destanks[1] = new TankDestroyer("СУ-152", "152 mm ML-20", "CCCР", 43, 2340000, 8, 10);
            m2_destanks[2] = new TankDestroyer("Charioteer", "105 mm L7", "Великобритания", 50, 3000000, 8, 16);

            ConsoleKeyInfo info;
            bool active_while = true;
            bool flag = false;
            while (active_while)
            {
                if (flag == false)
                { // flag == false нужна проверка на то, чтобы не запускать 100 одно и тоже сообщение
                    byte name_tank_id = SelectMenuItem(50, 2, m1_destanks);
                    Console.Clear();
                    DrawLine();
                    switch (name_tank_id)
                    {
                        case 0:
                            m2_destanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        case 1:
                            m2_destanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        case 2:
                            m2_destanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        default:
                            //Случай если из name_tank_id пользователь нажмёт на escape или tab
                            active_while = false;
                            flag = false;
                            return;
                    }
                }

                //По идеи здесь сообщение об выходе, чтобы выбрать другой танк
                info = Console.ReadKey(); // Читаем нажатую клавишу
                if (info.Key == ConsoleKey.Tab) // Проверяем на Escape
                {
                    flag = false;
                    Console.Clear();
                    DrawLine();
                }
                else if (info.Key == ConsoleKey.Escape)
                {
                    Console.WriteLine("Ты нажал на ESC");
                    active_while = false;
                    flag = false;
                    Console.Clear();
                    DrawLine();
                    return;
                }
            }
        }

        static void SAVt() {
            //В любом случае нужно выводить текст для выхода из конкретного окна
            string[] m1_SAVtanks = { "Caesar", "2С1 Гвоздика", "M109" };

            SAV[] m2_SAVtanks = new SAV[3];

            m2_SAVtanks[0] = new SAV("Caesar", "155 mm howitzer", "Франция", 100, 4890000, 60, 11);
            m2_SAVtanks[1] = new SAV("2С1 Гвоздика", "122 mm howitzer", "CCCР", 60, 5340000, 55, 14);
            m2_SAVtanks[2] = new SAV("M109", "155 mm howitzer", "США", 56, 4500000, 56, 16);

            ConsoleKeyInfo info;
            bool active_while = true;
            bool flag = false;
            while (active_while)
            {
                if (flag == false)
                { // flag == false нужна проверка на то, чтобы не запускать 100 одно и тоже сообщение
                    byte name_tank_id = SelectMenuItem(50, 2, m1_SAVtanks);
                    Console.Clear();
                    DrawLine();
                    switch (name_tank_id)
                    {
                        case 0:
                            m2_SAVtanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        case 1:
                            m2_SAVtanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        case 2:
                            m2_SAVtanks[name_tank_id].AboutTank();
                            flag = true;
                            break;
                        default:
                            //Случай если из name_tank_id пользователь нажмёт на escape или tab
                            active_while = false;
                            flag = false;
                            return;
                    }
                }

                //По идеи здесь сообщение об выходе, чтобы выбрать другой танк
                info = Console.ReadKey(); // Читаем нажатую клавишу
                if (info.Key == ConsoleKey.Tab) // Проверяем на Escape
                {
                    flag = false;
                    Console.Clear();
                    DrawLine();
                }
                else if (info.Key == ConsoleKey.Escape)
                {
                    Console.WriteLine("Ты нажал на ESC");
                    active_while = false;
                    flag = false;
                    Console.Clear();
                    DrawLine();
                    return;
                }
            }
        }

        //метод выводит вертикальную линию на экран
        public static void DrawLine()
        {
            //Console.SetCursorPosition((Console.WindowWidth/4) + 10, Console.WindowHeight/3);
            //Console.Write("Добро пожаловать в наш магазин запчастей танков!");
            Console.ForegroundColor = ConsoleColor.White;
            //Сначала рисуем края
            Console.SetCursorPosition(0, 0);
            Console.Write("┌");
            Console.SetCursorPosition(0, Console.WindowHeight - 1);
            Console.Write("└");
            Console.SetCursorPosition(Console.WindowWidth - 1, 0);
            Console.Write("┐");
            Console.SetCursorPosition(Console.WindowWidth - 1, Console.WindowHeight - 1);
            Console.Write("┘");

            //Затем рисуем бока
            for (int i = 1; i < Console.WindowHeight; i++) {
                if (i == Console.WindowHeight - 1) break;
                Console.SetCursorPosition(0, 0 + i);
                Console.Write("│");
                Console.SetCursorPosition(Console.WindowWidth - 1, 0 + i);
                Console.Write("│");
            }

            for (int i = 1; i < Console.BufferWidth; i++){
                if (i == Console.WindowWidth - 1) break;
                Console.SetCursorPosition(0 + i, 0);
                Console.Write("─");
                Console.SetCursorPosition(i + 0, Console.WindowHeight - 1);
                Console.Write("─");

            }
        }
    }
}
