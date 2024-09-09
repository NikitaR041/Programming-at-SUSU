using System;

//Лабораторная работа 1. Ветвление. Сравнение трёх чисел.
/*
Юзер вводит три числа. 
Используя только операцию сравнения вывести на экран эти три числа сначала по возрастанию, затем по убыванию.
При сравнении за раз сравниваем только два числа и не используем "обмен значениями".
Не используем массив и прочие коллекции!
*/

namespace MyApp 
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Привет! Введи 3 числа на каждой строке!");
            string num1 = Console.ReadLine();
            string num2 = Console.ReadLine(); 
            string num3 = Console.ReadLine();
            int x = int.Parse(num1);
            int y = int.Parse(num2);
            int z = int.Parse(num3);

            int flag1, flag2, flag3;

            //Если первое число больше второго
            if (x > y)
            {
                //Если первое число больше третьего
                if (x > z)
                {
                    //Если первое число больше второго и больше третьего, то
                    flag3 = x;
                    if (y > z)
                    {
                        //Если второе число больше третье
                        flag2 = y;
                        flag1 = z;
                    }
                    else
                    {
                        //Иначе третье число больше второго
                        flag2 = z;
                        flag1 = y;
                    }
                }
                //Иначе третье число больше второе
                else
                {
                    //Значит, что второе число не может быть больше третьего, то
                    flag1 = y;
                    flag2 = x; //А первое число будет нечто средним 
                    flag3 = z; //Последнее число самое большое
                }
            }
            //Иначе второе число больше первого числа
            else
            {
                //Если второе число больше третьего числа
                if (y > z)
                {
                    //Если первое число больше третьего
                    if (x > z)
                    {
                        flag1 = z;
                        flag2 = x;
                        flag3 = y;
                    }
                    else
                    {
                        flag1 = x;
                        flag2 = z;
                        flag3 = y;
                    }
                }
                //Иначе третье число больше второго
                else {
                    flag1 = x;
                    flag2 = y;
                    flag3 = z;
                }  
            }
            Console.WriteLine(flag1 + " " + flag2 + " " + flag3);
            Console.WriteLine(flag3 + " " + flag2 + " " + flag1);
            Console.ReadLine();
        }
    }
}