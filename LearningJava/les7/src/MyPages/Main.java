package MyPages;/*
Лабораторная работа 7. Коллекции.
Реализовать поиск, добавление и удаление информации о строительных материалах; каталог материалов организован по категориям.
Используем стандартный map
*/

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        MyCollectionMap<String, Material> myMap = new MyCollectionMap<>();

        myMap.addToMyMap("Продукты", new Material("Банка сгущенки", "25.02.2025", 150));
        myMap.addToMyMap("Продукты", new Material("Пакет сахара", "12.05.2011", 300));
        myMap.addToMyMap("Строительные материалы", new Material("Металлические брусья", "01.01.1900", 450));
        myMap.addToMyMap("Строительные материалы", new Material("Пластиковые трубы", "11.11.2000", 1000));
        myMap.addToMyMap("Инструменты", new Material("Молоток", "11.11.2000", 1000));

        myMap.printAll();

        System.out.println(" ---- ");
        myMap.erasePairMyMap("Продукты");
        myMap.printAll();

        System.out.println(" ---- ");
        System.out.println("Функция isSearchInMyMap вернула пару:");
        myMap.isSearchInMyMap("Строительные материалы");

        System.out.println("Что осталось в словаре:");
        myMap.printAll();
    }
}