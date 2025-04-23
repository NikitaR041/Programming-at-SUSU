package MyPages;/*
Лабораторная работа 7. Коллекции.
Реализовать поиск, добавление и удаление информации о строительных материалах; каталог материалов организован по категориям.

Используем стандартный map
*/

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        //MyCollectionMap<String, Material> MyMap;
        List<Material> myExample = new ArrayList<>();
        myExample.add(new Material("Банка сгущенки", "25.02.2025", 150));
        myExample.add(new Material("Пакет сахара", "12.05.2011", 300));
        myExample.add(new Material("Металлические брусья", "01.01.1900", 450));
        myExample.add(new Material("Пластиковые трубы", "11.11.2000", 1000));
        myExample.add(new Material("Подшипники", "11.11.2000", 1000));

    }
}