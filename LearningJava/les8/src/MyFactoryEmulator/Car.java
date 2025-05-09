package MyFactoryEmulator;

public class Car{
    private static int counter = 0; //Счетчик - количество созданных объектов от класса Body
    private static final int id = counter++; //Уникальный индетификатор для каждого объекта класса Body
    private final Body body; //Объект класса Body
    private final Motor motor; //Объект класса Motor
    private final Accessory accessory; //Объект класса Accessory

    public Car(Body body, Motor motor, Accessory accessory){
        this.body = body;
        this.motor = motor;
        this.accessory = accessory;
    }

    //Метод - получение индетификатора объекта классса Car
    public int getId() { return id; }
}
