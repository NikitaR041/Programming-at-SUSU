using System;

/*
Лабораторная работа #2
Романов Никита ЕТ-212 

Задание:
Задача на знаки Зодиака и Китайский календарь.
Юзер вводит три числа: любой год, месяц и день.
Определить (Животное: Дракон, Бык,...) Год по Китайскому календарю и цвет животного и Знак Зодиака (западная астрологии)
1) Не использовать стандартный класс ChineseLunisolarCalendar
2) Не использовать DateTime и системные фукнции работы с датой 
*/

namespace MyApp // Note: actual namespace depends on the project name.
{
    internal class Program
    {
        // Взято данные из сайта: https://horoscopes.rambler.ru/znaki-zodiaka/?ysclid=m19gbgruc259517481&updated&page=2
        static string Zodiak(int day, int month) {
            if ((day >= 21 && month == 3) || (day <= 20 && month == 4))
            {
                return "Овен";
            }
            else if ((day >= 21 && month == 4) || (day <= 20 && month == 5))
            {
                return "Телец";
            }
            else if ((day >= 21 && month == 5) || (day <= 21 && month == 6))
            {
                return "Близнецы";
            }
            else if ((day >= 22 && month == 6) || (day <= 22 && month == 7))
            {
                return "Рак";
            }
            else if ((day >= 23 && month == 7) || (day <= 22 && month == 8))
            {
                return "Лев";
            }
            else if ((day >= 23 && month == 8) || (day <= 23 && month == 9))
            {
                return "Дева";
            }
            else if ((day >= 24 && month == 9) || (day <= 23 && month == 10))
            {
                return "Весы";
            }
            else if ((day >= 24 && month == 10) || (day <= 22 && month == 11))
            {
                return "Скорпион";
            }
            else if ((day >= 23 && month == 11) || (day <= 21 && month == 12))
            {
                return "Стрелец";
            }
            else if ((day >= 22 && month == 12) || (day <= 20 && month == 1))
            {
                return "Козерог";
            }
            else if ((day >= 21 && month == 1) || (day <= 18 && month == 2))
            {
                return "Водолей";
            }
            else if ((day >= 19 && month == 2) || (day <= 20 && month == 3))
            {
                return "Рыбы";
            }
            else {
                return "Нет такой даты";
            }
        }

        static string ChinaCalendar(int year)
        {
            string[] calendar = new string[2];
            int num1 = year % 12;
            int num2 = year % 10;

            // Проверим по году
            switch (num1)
            {
                case 0: calendar[0] = "Крыса"; break;
                case 1: calendar[0] = "Бык"; break;
                case 2: calendar[0] = "Тигр"; break;
                case 3: calendar[0] = "Кролик"; break;
                case 4: calendar[0] = "Дракон"; break;
                case 5: calendar[0] = "Змея"; break;
                case 6: calendar[0] = "Лошадь"; break;
                case 7: calendar[0] = "Коза"; break;
                case 8: calendar[0] = "Обезьяна"; break;
                case 9: calendar[0] = "Петух"; break;
                case 10: calendar[0] = "Собака"; break;
                case 11: calendar[0] = "Свинья"; break;
                default: calendar[0] = "Неизвестно"; break;
            }

            // Проверим цвет
            switch (num2)
            {
                case 0: calendar[1] = "Неизвестно"; break;
                case 1: calendar[1] = "Белый (Металл)"; break;
                case 2: calendar[1] = "Неизвестно"; break;
                case 3: calendar[1] = "Черный (Вода)"; break;
                case 4: calendar[1] = "Неизвестно"; break;
                case 5: calendar[1] = "Зеленый (Дерево)"; break;
                case 6: calendar[1] = "Неизвестно"; break;
                case 7: calendar[1] = "Красный (Огонь)"; break;
                case 8: calendar[1] = "Неизвестно"; break;
                case 9: calendar[1] = "Желтый (Земля)"; break;
                default: calendar[1] = "Неизвестно"; break;
            }

            return calendar[0] + ' ' + calendar[1];
        }



        //Будем вызывать методы по знаку зодиака и по китайскому календарю
        static void Main(string[] args)
        {
            Console.WriteLine("Введите день:");
            int day = int.Parse(Console.ReadLine());

            Console.WriteLine("Введите месяц:");
            int month = int.Parse(Console.ReadLine());

            Console.WriteLine("Введите год:");
            int year = int.Parse(Console.ReadLine());

            //Узнаем знак зодиака
            string zodiak = Zodiak(day, month);
            string calend = ChinaCalendar(year);
            Console.WriteLine($"Знак зодиака: {zodiak}");
            Console.WriteLine($"Год животного и его цвет в Китайском календаре: {calend}");
        }
    }
}

/*
 Базовые приницы (3 кита) 5 китов:
1) Всякая сущность - обхект
2) Классифмкация (Класс) и Абстрагирование
3) Инкапсуляция (1 КИТ)
4) Наследование (2 КИТ)
5) Полиморфизмы (3 КИТ)
*/

/*
 ООП - эволюция
1) Неструктурное (двоичный код) с 40 до 60-ых
2) Структурное (процедурное) - типы данных, управляющие конструкции (следование, ветвления и циклы), подпрограммы (процедуры и функции)
   Были созданы самые сложные программы -> ОС | первая UNIX созданная на языке С.
   С 60-ых годов началось структурное программирование
3) В 80-ых Объектно-ориентированное программирование (ООП)
*/

/*
 Преимущества ООП:
 1) Повышение модульности и удобства повторного использования - ускорение разработки ПО.
 2) Программный код пишется в ТЕРМИНАХ предметной области и упрощает чтение кода.
*/