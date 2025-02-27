/*
Лабораторная работа 1. Основы языка Java

Вариант 19

Объявить массив целых чисел и заполнить его случайными числами.
Размер массива (n>=10) и диапазон значений его элементов вводятся с клавиатуры.
Найти непрерывный участок из 10 элементов, сумма которых максимальна.
Вывести индекс начала участка.
*/

import java.util.Scanner;

public class Main {
    public static void main(String[] arg){
        int maxDiap = 0, minDiap = 0; //Диапазоны чисел, задаваемые пользователем
        int[] intArray; // Целочисленный массив

        //Объявление с клавиатуры
        Scanner scanner = new Scanner(System.in);
        System.out.println("Введите размер массива (n>=10) ");
        int n = scanner.nextInt();
        intArray = new int[n];

        if (n < 10){
            System.out.println("Вы неверно ввели размер массива!");
            return;
        }

        System.out.println("Введите диапазоны. Минимальный диапазон:");
        minDiap = scanner.nextInt();
        System.out.println("Введите максимальный диапазон: ");
        maxDiap = scanner.nextInt();

        //Заполнить массив случайными числами.
        for(short i = 0; i < n; i++) {
            int value = (int) ((Math.random() * (maxDiap - (minDiap + 1)) + minDiap));
            intArray[i] = value;
        }

        //Найти непрерывный участок из 10 элементов, сумма которых максимальна.
        //Вывести индекс начала участка.
        int maxSum = Integer.MIN_VALUE, sum = 0;
        int index = 0;
        for(int i = 0; i < n - 10; i++){
            sum = 0;
            for(int j = i; j < i + 10; j++){
                sum += intArray[j];
            }
            if (maxSum < sum) {
                maxSum = sum; //Максимальная сумма
                index = i; //Начала индекса
            }
        }
        System.out.printf("Максимальная сумма: %d \nИндекс начала участка с максимальной суммой: %d", maxSum, index);
    }
}
