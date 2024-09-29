using System;
using System.Diagnostics.Tracing;

//Лабораторная работа 3 | Романов Никита ЕТ-212
//Файл Program.cs является основным файлом, в котором будут выводиться тестовые значения, вывод результатов, вызов методов из класса ArrayUtils

namespace practice3 
{ 
    class Program 
    {
        static void Main(string[] args) 
        {
            //Тесты на проверку каждых методов из класса ArrayUtils
            int[] mas1 = { 5, 7, 8 };
            int[] mas2 = { 10, 15, 16, 19 };

            //случаи с 5 задачей
            int[] mas3 = { 5, 6, 8, 24, 28};
            int[] mas4 = { 10, 15, 16, 19 };

            int[] mas5 = { 5, 6, 8, 90, 80, 50 };
            int[] mas6 = { 10,15, 16 };

            //Задача 1
            Console.WriteLine("1 задача");
            foreach (var elem in ArrayUtils.MergeMassive(mas1, mas2))
            {
                Console.WriteLine($"Элемент: {elem}");
            }

            Console.WriteLine();

            //Задача 2
            //1 случай
            foreach (var elem in ArrayUtils.NewMassive(mas1, 10, 1))
            {
                Console.WriteLine($"Элемент: {elem}");
            }
            //2 случай
            foreach (var elem in ArrayUtils.NewMassive(mas1, 0, 3))
            {
                Console.WriteLine($"Элемент: {elem}");
            }
            //3 случай
            foreach (var elem in ArrayUtils.NewMassive(mas1, 1, 0))
            {
                Console.WriteLine($"Элемент: {elem}");
            }

            Console.WriteLine();

            //Задача 3
            Console.WriteLine("1 Случай 3 задачи");
            foreach (var elem in ArrayUtils.DeleteElemMass(mas1, 0))
            {
                Console.WriteLine($"Элемент: {elem}");
            }
            Console.WriteLine("2 Случай 3 задачи");
            foreach (var elem in ArrayUtils.DeleteElemMass(mas1, 1))
            {
                Console.WriteLine($"Элемент: {elem}");
            }
            Console.WriteLine("3 Случай 3 задачи");
            foreach (var elem in ArrayUtils.DeleteElemMass(mas1, 2))
            {
                Console.WriteLine($"Элемент: {elem}");
            }

            Console.WriteLine();

            //Задача 4
            Console.WriteLine("1 Случай 4 задачи");
            foreach (var elem in ArrayUtils.InsertMassive(mas1, 0, mas2))
            {
                Console.WriteLine($"Элемент: {elem}");
            }
            Console.WriteLine("2 Случай 4 задачи");
            foreach (var elem in ArrayUtils.InsertMassive(mas1, 1, mas2))
            {
                Console.WriteLine($"Элемент: {elem}");
            }
            Console.WriteLine("3 Случай 4 задачи");
            foreach (var elem in ArrayUtils.InsertMassive(mas1, 3, mas2))
            {
                Console.WriteLine($"Элемент: {elem}");
            }

            Console.WriteLine();

            Console.WriteLine("5 задача, неправильный случай");
            foreach (var elem in ArrayUtils.CopyReplaceMassive(mas1, mas2, 0, 1, 4)) // Когда mas1.Length < mas2.Length
            {
                Console.WriteLine($"Элемент: {elem}");
            }
            Console.WriteLine("5 задача, правильный случай");
            foreach (var elem in ArrayUtils.CopyReplaceMassive(mas1, mas2, 0, 1, 3))
            {
                Console.WriteLine($"Элемент: {elem}");
            }

            Console.WriteLine("5 задача, правильный случай");
            foreach (var elem in ArrayUtils.CopyReplaceMassive(mas3, mas4, 2, 1, 3)) // Когда mas3.Length == mas4.length
            {
                Console.WriteLine($"Элемент: {elem}");
            }
            Console.WriteLine("5 задача, правильный случай");
            foreach (var elem in ArrayUtils.CopyReplaceMassive(mas5, mas6, 3, 0, 3)) // Когда mas5.length > mas6.Length
            {
                Console.WriteLine($"Элемент: {elem}");
            }


            Console.ReadKey();
        }
    }

}