package MyFactoryEmulator;

public class Accessory {
    private static int counter = 0; //Счетчик - количество созданных объектов от класса Accessory
    private final int id; //Уникальный индетификатор для каждого объекта класса Accessory
    //Поле id - обновляется после каждого созданного объекта класса Accessory

    public Accessory() { this.id = counter++; }
    //Метод - получение индетификатора объекта классса Accessory
    public int getId(){ return id;}
    //Метод - получение общего количества произведенных объектов класса Accessory
    public static int getTotalCount(){ return counter;}
    @Override
    public String toString(){ return "Accessory#" + id; }
}
