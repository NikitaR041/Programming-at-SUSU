package MyFactoryEmulator;

public class Motor {
    private static int counter = 0; //Счетчик - количество созданных объектов от класса Motor
    private final int id; //Уникальный индетификатор для каждого объекта класса Motor
    //Поле id - обновляется после каждого созданного объекта класса Motor
    public Motor() { this.id = counter++; }
    //Метод - получение индетификатора объекта классса Motor
    public int getId(){ return id;}
    //Метод - получение общего количества произведенных объектов класса Motor
    public static int getTotalCount(){ return counter;}
    @Override
    public String toString(){ return "Motor#" + id; }
}
