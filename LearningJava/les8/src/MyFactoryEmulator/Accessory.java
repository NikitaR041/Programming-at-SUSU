package MyFactoryEmulator;

public class Accessory {
    private static int counter = 0; //Счетчик - количество созданных объектов от класса Body
    private static final int id = counter++; //Уникальный индетификатор для каждого объекта класса Body
    //Поле id - обновляется после каждого созданного объекта класса Body

    //Метод - получение индетификатора объекта классса Body
    public int getId(){ return id;}
    //Метод - получение общего количества произведенных объектов класса Body
    public static int getTotalCount(){ return counter;}
}
