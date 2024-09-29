using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

//Файл ArrayUtils - класс объекта массива с различными методами

namespace practice3
{
    class ArrayUtils
    {
        //Рассмотрим реализованные методы по пунктам
        /*
        Задача 1)
        Слияние массивов (Склеивание). Написать функцию кот принимает на вход два массива. 
        На выход выдаёт третий массив в кот будут эл-ты сначала из 1го потом из 2го. 
        [5,7,8] + [10, 15,16,19] => [5,7,8,10,15,16,19]
        */
        public static int[] MergeMassive(int[] firstMassive, int[] secondMassive) {
            //mergemas - массив, в котором сливаем два массива
            int[] mergemas = new int[firstMassive.Length + secondMassive.Length];
            
            //Сливаем из первого массива
            for (int i = 0; i < firstMassive.Length; i++) { 
                mergemas[i] = firstMassive[i];
            }

            //Сливаем из второго массива
            for(int i = 0; i < secondMassive.Length; i++) {
                mergemas[firstMassive.Length + i] = secondMassive[i];
            }

            return mergemas;
        }

        /*
        Задача 2) 
        Вставка нового эл-та в массив. 
        Написать функцию кот принимает на вход массив, число, индекс. 
        На выход – новый массив (на единицу больше) в котором новое число по нужному индексу. 
        
        Здесь мы должны рассмотреть 3 случая расстановки числа по нужному индексу 
        */
        public static int[] NewMassive(int[] massive, int digit, int index) {
            //Новый массив, в который будет перекидыватся старые значения из massive и новый элемент по индексу
            int[] newmass = new int[massive.Length + 1]; //На единицу больше массив

            //1 случай, когда нужный элемент на каком-либо промежутке стоит,то
            if (0 < index && index < massive.Length)
            {
                Console.WriteLine("1 случай 2 задачи");
                for (int i = 0; i < index; i++)
                {
                    newmass[i] = massive[i];
                }
                newmass[index] = digit;
                int j = index + 1;
                for (; j < newmass.Length; j++)
                {
                    newmass[j] = massive[j - 1];
                }
            }
            //2 случай, когда нужный элемент стоит в начале, то
            else if (0 == index)
            {
                Console.WriteLine("2 случай 2 задачи");
                newmass[index] = digit;
                for (int i = 1; i < newmass.Length; i++)
                {
                    newmass[i] = massive[i - 1];
                }
                
            }
            //3 случай, когда нужный элемент стоит в конце, то
            else if (massive.Length == index) {
                Console.WriteLine("3 случай 2 задачи");
                for (int i = 0; i < massive.Length; i++)
                {
                    newmass[i] = massive[i];
                }
                newmass[index] = digit;
            }

            return newmass;
        }

        /*
        Задача 3) 
        Удаление эл-та из массива. 
        Написать функцию кот принимает на вход массив и индекс. 
        На выход – новый массив (на единицу меньше) в котором число по индексу отсутствует. 
        */
        public static int[] DeleteElemMass(int[] massive, int index) {
            int[] newmassive = new int[massive.Length - 1];

            for (int i = 0; i < index; i++) {
                newmassive[i] = massive[i];
            }
            for (int i = index; i < newmassive.Length; i++) {
                newmassive[i] = massive[i + 1];
            }
            return newmassive;
        }

        /*
        Задача 4)
        Вставка массива в массив. 
        Написать функцию кот принимает на вход массив, индекс, второй массив. 
        На выход – новый массив  в вставлен второй.
        
        Рассмотрим случаи:
        Пример работы 1: m1 = [1 2 3 4], m2 = [8 9] -> начиная с индекса 2 вставляем второй массив в первый массив [1 2  8 9  3 4] 
        Пример работы 1: m1 = [1 2 3 4], m2 = [8 9] -> начиная с индекса 0 вставляем второй массив в первый массив [8 9  1 2 3 4] 
        Пример работы 1: m1 = [1 2 3 4], m2 = [8 9] -> начиная с индекса 3 вставляем второй массив в первый массив [1 2 3 4  8 9] 
        
        */
        public static int[] InsertMassive(int[] firstMassive, int index, int[] secondMassive) {
            int[] newmassive = new int[firstMassive.Length + secondMassive.Length];
            //Разработаем три цикла, которые будут расмотрены для наших трех случаев
            for (int i = 0; i < index; i++) {
                newmassive[i] = firstMassive[i];
            }
            for (int i = 0; i < secondMassive.Length; i++) {
                newmassive[i + index] = secondMassive[i];
            }
            for (int i = index; i < firstMassive.Length; i++) {
                newmassive[i + secondMassive.Length] = firstMassive[i];
            }

            return newmassive;
        }

        /*
        Задача 5)
        Копирование (с заменой). На вход два массива. Два индекса. И количество эл-в. 
        Из первого массива, начиная с 1 индекса во второй массив с заменой копируются данные во второй массив начиная со второго индекса. 
        Обеспечить Проверки выхода за границы массивы.

                       m1 = [1 2 3 4 5 6 7 8] m2 = [10 11 12 13]     m1.Length > m2.Length - случай обработан
                       m1 = [1 2 3 4 5 6] m2 = [10 11 12 13 14 15]   m1.Length == m2.Length - случай обработан
        Пример работы: m1 = [1 2 3 4 5 6], m2 = [10 11 12 13 14 15 16]   m1.Length < m2.Length - случай обработан
                       index1 = 3           index2 = 2    count = 2
        Результат работы: m2 = [10 11 4 5 14 15 16]
        Случаи, которые мы должны обработать:
        1)количество копируемых элементов из m1 = количеству элементов замене во втором массиве
            1)Копируем из m1, 2 элемента начиная с 5 индеска и заменяем во втором массиве начиная 5 индекса, то результат m2 [10 11 12 13 14 5 6]
            2)Копируем из m1, 3 элемента начиная с 2 индекса и заменяем во втором массиве начиная 3 индеска, то результат m2 [10 11 12 3 4 5 16]
                т.е. должны смотреть, что количество копирование элементов из m1 должно НЕ превышать m2.Length - index2, где m2.Length - index2 подскажет сколько элементов можно заменить начиная с index2 
        */
        public static int[] CopyReplaceMassive(int[] firstMassive, int[] secondMassive, int index1, int index2, int count_copy) {
            int flag1 = count_copy;
            int flag2 = index2;
            //Обработаем случай, который я привел выше
            if (count_copy <= (secondMassive.Length - index2))
            {
                for (int i = index1; i < firstMassive.Length; i++)
                {
                    if (flag1 != 0)
                    {
                        secondMassive[flag2++] = firstMassive[i];
                        flag1--;
                    }
                    else {
                        break;
                    }
                }
            }
            else {
                Console.WriteLine($"Превышение копирование элементов из 1 массива: {count_copy}");
            }
            return secondMassive;
        }
    }   
}
