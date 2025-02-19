import java.util.Scanner;

public class Main {
    public static void main(String[] arg){
        //Объявление с клавиатуры
        Scanner scanner = new Scanner(System.in);
        System.out.println("Введите размер массива (n>=10) ");
        int n = scanner.nextInt();

        if(n < 10) System.out.println("Вы неверно ввели размер массива!");

        System.out.println("Введите диапазоны");
        System.out.println("Введите минимальный диапазон");
        int minDiap = scanner.nextInt();
        System.out.println("Введите максимальный диапазон");
        int maxDiap = scanner.nextInt();

        //Объявить массив целых чисел и заполнить его случайными числами.
        int[] intArray = new int[n];
        for(short i = 0; i < n; i++) {
            int value = (int) ((Math.random() * (maxDiap-minDiap)) + minDiap);
            intArray[i] = value;
        }

        // Вывод массива
        System.out.println("Сгенерированный массив:");
        for (int value : intArray) {
            System.out.print(value + " ");
        }
        System.out.println();

        /*
         * Найти непрерывный участок из 10 элементов, сумма которых максимальна.
         * Вывести индекс начала участка.
         */
        int maxSum = -100000; //Замечание: Пусть минимальный порог - это -100.000
        int index = -1;

        for (int i = 0; i <= n - 10; i++) {
            int sum = 0;
            for (int j = i; j < i + 10; j++) {
                sum += intArray[j];
            }
            if (sum > maxSum) {
                maxSum = sum;
                index = i;
            }
        }
        System.out.println("Максимальная сумма: " + maxSum);
        System.out.println("Индекс начала участка с максимальной суммой: " + index);
    }
}
