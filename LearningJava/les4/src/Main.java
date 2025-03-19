
//Лабораторная работа 4 - Регулярные выражения. Лямбды.

/*
Регулярные выражения:
https://metanit.com/java/tutorial/7.4.php
https://javarush.ru/groups/posts/regulyarnye-vyrazheniya-v-java
Лямбда-выражения:
https://metanit.com/java/tutorial/9.1.php

Задание - Регулярные выражения.
1.	Написать регулярное выражение, которые проверят e-mail простого вида (например, test@test.test).
2.	Написать программу, которые при помощи регулярных выражений заменяет слово «функция» в тексте на «<mark>функция</mark>».
3.	Написать функцию, которая при помощи регулярных выражений разбивает текст на отдельные слова и находит частоту встречаемости отдельных слов.

Задание - Лямбда-выражение.
4.	Написать функциональный интерфейс с методом, который принимает число и возвращает булево значение.
Написать реализацию такого интерфейса в виде лямбда-выражения, которое возвращает true если переданное число делится без остатка на 13.
5.  Написать функциональный интерфейс с методом, который принимает две строки и возвращает тоже строку.
Написать реализацию такого интерфейса в виде лямбды, которая возвращает ту строку, которая длиннее.
6.	Написать функциональный интерфейс с методом, который принимает три дробных числа: a, b, c и возвращает тоже дробное число.
Написать реализацию такого интерфейса в виде лямбда-выражения, которое возвращает дискриминант. Кто забыл, D = b^2 — 4ac.
7.	Используя функциональный интерфейс из задачи 6 написать лямбда-выражение, которое возвращает результат операции a * b^c.

*/
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.util.*;

//Задание - Регулярные выражения.
//#1
/*
public class Main {
    public static void main(String[] args) {
        String example = "VseMoguchi@yandex.ru Tamagochi2004@mail.ru niki228@gmail.com test@test.test Oshibka1test.test Oshibka2@.";
        Pattern pattern = Pattern.compile("\\b[\\w]+@[\\w]+\\.[a-zA-Z]{2,6}\\b"); // Для простых видов e-mail
        //Pattern pattern = Pattern.compile("\\b[\\w._%+-]+@[\\w.-]+\\.[a-zA-Z]{2,6}\\b"); //Для более сложных видов e-mail
        Matcher matcher = pattern.matcher(example);
        while (matcher.find()) {
            System.out.println("Найден email: " + matcher.group());
        }
    }
}
*/
//#2
/*
public class Main {
    public static void main(String[] args) {
        String example = "функция функция   функция    функция функция";
        Pattern pattern = Pattern.compile("функция(\\s*)");
        Matcher matcher = pattern.matcher(example);
        String new_example = matcher.replaceAll("<mark>функция</mark>");
        System.out.println(new_example);
    }
}
*/
//#3
/*
public class Main{
    public static void findFrequencyWords(String obj){
        Map<String, Integer> states = new HashMap<String, Integer>();
        Pattern pattern = Pattern.compile("\\s+");
        String[] words = pattern.split(obj);
        for (String word : words) {
            states.put(word, states.getOrDefault(word, 0) + 1);
        }
        for(Map.Entry<String, Integer> item : states.entrySet()){
            System.out.printf("Ключ: %s  Значение: %d \n", item.getKey(), item.getValue());
        }
    }
    public static void main(String[] args){
        String example1 = "Шла Саша по шоссе и сосала сушку";
        String example2 = "Абракадабра Абракадабра Абракадабра Саша саша Мама Мама";
        findFrequencyWords(example1);
        System.out.println("----------------------");
        findFrequencyWords(example2);
    }
}*/

//Задание - Лямбда-выражение.
//#4
/*
interface Operation{
    boolean isDivion(int number);
}

public class Main {
    public static void main(String[] args) {
        Operation operation = number -> number % 13 == 0;
        System.out.println(operation.isDivion(15));
        System.out.println(operation.isDivion(26));
        System.out.println(operation.isDivion(39));
        System.out.println(operation.isDivion(13));
    }
}
*/

//#5
/*
interface Operation{
    String obj(String a, String b);
}

public class Main{
    public static void main(String[] args){
        Operation obj = (a,b) -> a.length() >= b.length() ? a : b;
        System.out.println(obj.obj("Hello", "World!")); // World!
        System.out.println(obj.obj("Java", "Programming")); // Programming
        System.out.println(obj.obj("Car", "Fly")); // Functions
    }
}
*/

//#6
/*
interface Discriminant{
    double D(double a, double b, double c);
}
public class Main{
    public static void main(String[] args){
        Discriminant obj = (a,b,c) -> (b*b) - 4*a*c;
        System.out.println(obj.D(1,-8,12));
        System.out.println(obj.D(5,3,7));
        System.out.println(obj.D(1,-6,9));
    }
}
*/

//#7
interface Discriminant{
    double D(double a, double b, double c);
}
public class Main{
    public static void main(String[] args){
        Discriminant obj = (a,b,c) -> a * Math.pow(b,c);
        System.out.println(obj.D(1,-8,2));
        System.out.println(obj.D(5,3,3));
        System.out.println(obj.D(2,4,0.5));
    }
}