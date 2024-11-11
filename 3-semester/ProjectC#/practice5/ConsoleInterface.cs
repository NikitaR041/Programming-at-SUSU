using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AIS
{
    internal class ConsoleInterface
    {
        private string name_title; //Название заголовка
        private string name_chapter; //Название главы <h1>
        private List<string> chapters; //Характеристики
        private List<string> value;
        private short index = 0;

        // Метод, который считывает информацию с файла
        public void read_files(StreamReader sr, List<AudioSpeaker> speakerList) // Изменим на List<AudioSpeaker>
        {
            string stroka = sr.ReadLine();
            while (!sr.EndOfStream)
            {
                stroka = sr.ReadLine();  // Важно считать строку перед проверкой условий!

                // Проверяем наличие хотя бы одного из тегов
                if (stroka.IndexOf("<h1>") != -1 || stroka.IndexOf("<title>") != -1 || stroka.IndexOf("<th>") != -1 || stroka.IndexOf("<td>") != -1)
                {
                    // Делаем проверки для разных тегов
                    if (stroka.IndexOf("<title>") != -1) //Заголовок 
                    {
                        this.name_title = stroka.Substring(stroka.IndexOf("<title>") + 7, stroka.LastIndexOf("</title>") - stroka.IndexOf("<title>") - 7).Trim();
                    }
                    else if (stroka.IndexOf("<h1>") != -1) //Глава
                    {
                        this.name_chapter = stroka.Substring(stroka.IndexOf("<h1>") + 4, stroka.LastIndexOf("</h1>") - stroka.IndexOf("<h1>") - 4).Trim();
                    }
                    else if (stroka.IndexOf("<th>") != -1) //Характеристка - столбец
                    {
                        stroka = stroka.Substring(stroka.IndexOf("<th>") + 4, stroka.LastIndexOf("</th>") - stroka.IndexOf("<th>") - 4).Trim();
                        chapters.Add(stroka);
                    }
                    else if (stroka.IndexOf("<td>") != -1) //Описание характеристики - строка
                    {
                        stroka = stroka.Substring(stroka.IndexOf("<td>") + 4, stroka.LastIndexOf("</td>") - stroka.IndexOf("<td>") - 4).Trim();
                        //Сначала накапливаем в массив value
                        if (index != 6)
                        {
                            value.Add(stroka);
                            index++;
                        }
                        else
                        { // Создаем новый объект  
                            speakerList.Add(new AudioSpeaker(value[0], value[1], value[2], value[3], value[4], value[5]));
                            value.Clear();  // Очищаем список для следующего объекта
                            index = 0;  // Сбрасываем индекс для следующей записи
                        }
                    }
                }
            }
        }

        //Метод, который отображает интерфес в консоли
        //метод отвечает за вывод меню на экран
        public static void PrintMenu(int x, int y, string[] menu, byte active_ind)
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
                    //case ConsoleKey.Tab:
                    //    return 254; // 254 означает выход к каталогу типов танков
                    default:
                        isWorking = false;
                        break;
                }
            }
            Console.CursorVisible = true;
            return 253; //Возвращение значения, что ничего не произошло
        }
    }
}
