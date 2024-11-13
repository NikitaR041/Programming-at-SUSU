using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace AIS
{
    internal class ConsoleInterface
    {
        private static List<string> name_title_chapter = new List<string>(); //Название заголовка <title> и название главы <h1>
        private static List<string> chapters = new List<string>(); //Характеристики-свойства
        private static List<string> temporary_list = new List<string>(); //Аудиоколоника с характеристиками
        private static string[] manual = new string[] { "ESC - выход/очистить экран", "Enter - перейти", "Tab - открыть таблицу"};

        private static short index = 0;

        // Метод, который считывает информацию с файла
        public void ReadFile(StreamReader sr, List<AudioSpeaker> speakerList)
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
                        //this.name_title = stroka.Substring(stroka.IndexOf("<title>") + 7, stroka.LastIndexOf("</title>") - stroka.IndexOf("<title>") - 7).Trim();
                        stroka = stroka.Substring(stroka.IndexOf("<title>") + 7, stroka.LastIndexOf("</title>") - stroka.IndexOf("<title>") - 7).Trim();
                        name_title_chapter.Add(stroka);
                    }
                    else if (stroka.IndexOf("<h1>") != -1) //Глава
                    {
                        //this.name_chapter = stroka.Substring(stroka.IndexOf("<h1>") + 4, stroka.LastIndexOf("</h1>") - stroka.IndexOf("<h1>") - 4).Trim();
                        stroka = stroka.Substring(stroka.IndexOf("<h1>") + 4, stroka.LastIndexOf("</h1>") - stroka.IndexOf("<h1>") - 4).Trim();
                        name_title_chapter.Add(stroka);
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
                            temporary_list.Add(stroka);
                            index++;
                        }
                        else
                        { 
                            speakerList.Add(new AudioSpeaker(temporary_list[0], temporary_list[1], temporary_list[2], temporary_list[3], temporary_list[4], temporary_list[5]));
                            temporary_list.Clear();  // Очищаем список для следующего объекта
                            index = 1;  // Сбрасываем индекс для следующей записи
                            temporary_list.Add(stroka);
                        }
                    }
                }
            }
        }

        //Метод, который отображает интерфес в консоли
        //метод отвечает за вывод меню на экран
        public static void PrintMenu(int x, int y, List<AudioSpeaker> speakerList, byte active_ind)
        {
            Console.BackgroundColor = ConsoleColor.Magenta;
            Console.ForegroundColor = ConsoleColor.Green;

            for (int i = 0; i < speakerList.Count; i++)
            {
                Console.SetCursorPosition(x, y + i);
                Console.Write(speakerList[i].Name);
            }

            Console.BackgroundColor = ConsoleColor.Black;
            Console.ForegroundColor = ConsoleColor.Green;
            Console.SetCursorPosition(x, y + active_ind);
            Console.Write(speakerList[active_ind].Name);
        }

        //Метод обрабатывает выбор элемента меню пользователем
        public static byte SelectMenuItem(int x, int y, List<AudioSpeaker> speakerList)
        {
            DrawLine();
            Console.CursorVisible = false;
            bool isWorking = true;
            bool flag = false;
            byte activ_ind = 0;
            while (isWorking)
            {
                if (flag == false) { PrintMenu(x, y, speakerList, activ_ind); }

                ConsoleKeyInfo info = Console.ReadKey();
                switch (info.Key)
                {
                    case ConsoleKey.Enter:
                        isWorking = false;
                        return activ_ind;
                    case ConsoleKey.UpArrow:
                        if (activ_ind > 0) activ_ind--; //Защита от выхода
                        break;
                    case ConsoleKey.DownArrow:
                        if (activ_ind < speakerList.Count - 1) activ_ind++; //Защита от выхода
                        break;
                    case ConsoleKey.Escape: //Для очистки таблицы
                        Console.Clear();
                        flag = false;
                        DrawLine();
                        break;
                    case ConsoleKey.Tab: //Для отображения таблицы
                        Console.Clear();
                        //DrawLine();
                        flag = true;
                        for (byte i = 0; i < speakerList.Count; i++)
                        {
                            Console.WriteLine(speakerList[i].ToString());
                        }
                        break;
                    default:
                        break;
                }
            }
            Console.CursorVisible = true;
            return 255; //Возвращение значения, что ничего не произошло
        }

        //Метод switch, который определяет кого показывать, а кого нет
        public static void SearchValue(byte index, List<AudioSpeaker> speakerList) {
            Console.Clear();
            DrawLine();
            bool isWorking = true;
            AudioSpeaker obj = speakerList[index];

            //Сначала нужно вывести характеристики-свойства
            for (byte i = 0; i < chapters.Count; i++) {
                Console.SetCursorPosition(30, 10 + i); //По идеи слева|середина
                Console.WriteLine(chapters[i]);
            }

            //Затем выведем объект с его свойствами! - может быть здесь переопределит ToString()?
            Console.SetCursorPosition(57, 10); 
            Console.WriteLine(obj.Name);
            Console.SetCursorPosition(57, 11); 
            Console.WriteLine(obj.Power);
            Console.SetCursorPosition(57, 12); 
            Console.WriteLine(obj.Size);
            Console.SetCursorPosition(57, 13); 
            Console.WriteLine(obj.ConType);
            Console.SetCursorPosition(57, 14); 
            Console.WriteLine(obj.ButteryLife);
            Console.SetCursorPosition(57, 15); 
            Console.WriteLine(obj.Price);

            //Выход из этого цикла, нужно нажать на Escape
            ConsoleKeyInfo info = Console.ReadKey();
            while (isWorking) {
                if (info.Key == ConsoleKey.Escape)
                {
                    Console.Clear();
                    isWorking = false;
                    break;
                }
                info = Console.ReadKey();
            }
        }
        //Метод, который рисует таблицу
        public static void DrawLine()
        {

            for (byte i = 0; i < name_title_chapter.Count; i++) {
                Console.ForegroundColor = ConsoleColor.Green;
                Console.SetCursorPosition(50 + (i * (-8)), 6 + i);
                Console.WriteLine(name_title_chapter[i]);
            }
            for (byte i = 0; i < manual.Length; i++)
            {
                Console.SetCursorPosition(2, 10 + i);
                Console.WriteLine(manual[i]);
            }
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
            for (int i = 1; i < Console.WindowHeight; i++)
            {
                if (i == Console.WindowHeight - 1) break;
                Console.SetCursorPosition(0, 0 + i);
                Console.Write("│");
                Console.SetCursorPosition(Console.WindowWidth - 1, 0 + i);
                Console.Write("│");
            }

            for (int i = 1; i < Console.BufferWidth; i++)
            {
                if (i == Console.WindowWidth - 1) break;
                Console.SetCursorPosition(0 + i, 0);
                Console.Write("─");
                Console.SetCursorPosition(i + 0, Console.WindowHeight - 1);
                Console.Write("─");

            }
        }
    }
}
