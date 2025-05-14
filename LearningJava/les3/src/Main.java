/*
   Лабораторная работа 3 | Вариант 19
   Задание:
    Разработать консольную программу на языке Java, в которой необходимо определить базовый класс и на его основе производные классы.
    Кроме закрытых полей с данными в классах должны быть методы доступа, конструкторы с параметрами, также методы в соответствии с
    индивидуальным вариантом задачи.
    С использованием массива ссылок на базовый класс создать массив объектов производных классов и организовать работу с ним.
    В программе необходимо продемонстрировать механизм динамического полиморфизма.

   Задание с варианта 2:
    Определить класс «Шахматная фигура» и унаследовать от него классы, соответствующие шахматным фигурам «Ферзь», «Пешка», «Конь».
    Задать позицию и определить список фигур, которые может убить некоторая выбранная фигура.
 */

public class Main {
    public static void main(String[] args) {
        ChessFigure[] figures = new ChessFigure[6];

        //Расстановка фигур на доске
        figures[0] = new Queen('d', 4);
        figures[1] = new Pawn('e', 5);
        figures[2] = new Knight('c', 6);
        figures[3] = new Pawn('c', 5);
        figures[4] = new Knight('e', 2);
        figures[5] = new Queen('a', 4);

        //Выбираем Ферзя и смотрим
        ChessFigure attacker = figures[0];

        System.out.println("Фигуры, которых может побить " + attacker.getClass().getSimpleName() +
                " на позиции " + attacker.getX() + attacker.getY() + ":");

        for (int i = 1; i < figures.length; i++) {
            if (attacker.canKill(figures[i])) {
                System.out.println("  " + figures[i].getClass().getSimpleName() +
                        " на позиции " + figures[i].getX() + figures[i].getY());
            }
        }

        System.out.println();

        //Выбираем коня и смотрим
        ChessFigure knight = figures[4];
        System.out.println("Фигуры, которых может побить " + knight.getClass().getSimpleName() +
                " на позиции " + knight.getX() + knight.getY() + ":");

        for (int i = 0; i < figures.length; i++) {
            if (i != 4 && knight.canKill(figures[i])) {
                System.out.println("  " + figures[i].getClass().getSimpleName() +
                        " на позиции " +figures[i].getX() + figures[i].getY());
            }
        }
    }
}