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
        //private string name_chapter; //Название главы <h1>
        

        private static short index = 0;
        private static short size = 0;

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
                        { // Создаем новый объект

                            speakerList.Add(new AudioSpeaker(temporary_list[0], temporary_list[1], temporary_list[2], temporary_list[3], temporary_list[4], temporary_list[5]));
                            //foreach (var elem in temporary_list)
                            //{
                            //    Console.WriteLine(elem);
                            //}
                            //Console.WriteLine(temporary_list[0]);
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
            //DrawLine();
            Console.CursorVisible = false;
            bool isWorking = true;
            byte activ_ind = 0;
            while (isWorking)
            {
                PrintMenu(x, y, speakerList, activ_ind);
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
                        if (activ_ind < speakerList.Count - 1) activ_ind++;
                        break;
                    default:
                        //isWorking = false;
                        break;
                }
            }
            Console.CursorVisible = true;
            return 255; //Возвращение значения, что ничего не произошло
        }

        //Метод switch, который определяет кого показывать, а кого нет
        public static void search_value(byte index, List<AudioSpeaker> speakerList) {
            Console.Clear();
            bool isWorking = true;
            AudioSpeaker obj = speakerList[index];

            //Сначала нужно вывести характеристики-свойства
            for (byte i = 0; i < chapters.Count; i++) {
                Console.SetCursorPosition(30, 10 + i); //По идеи слева|середина
                Console.WriteLine(chapters[i]);
            }

            //Затем выведем объект с его свойствами!
            Console.SetCursorPosition(57, 10); //По идеи слева|середина
            Console.WriteLine(obj.Name);
            Console.SetCursorPosition(57, 11); //По идеи слева|середина
            Console.WriteLine(obj.Power);
            Console.SetCursorPosition(57, 12); //По идеи слева|середина
            Console.WriteLine(obj.Size);
            Console.SetCursorPosition(57, 13); //По идеи слева|середина
            Console.WriteLine(obj.ConType);
            Console.SetCursorPosition(57, 14); //По идеи слева|середина
            Console.WriteLine(obj.ButteryLife);
            Console.SetCursorPosition(57, 15); //По идеи слева|середина
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
    }
}
