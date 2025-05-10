package MyFactoryEmulator;

public class Car{
    private static int counter = 0; //Счетчик - количество созданных объектов от класса Car
    private final int id; //Уникальный индетификатор для каждого объекта класса Car
    private final Body body; //Объект класса Body
    private final Motor motor; //Объект класса Motor
    private final Accessory accessory; //Объект класса Accessory

    public Car(Body body, Motor motor, Accessory accessory){
        this.id = counter++;
        this.body = body;
        this.motor = motor;
        this.accessory = accessory;
    }

    //Метод - получение индетификатора объекта классса Car
    public int getId() { return id; }
    @Override
    public String toString() { return String.format("Car#%d (Body: %s, Motor: %s, Accessory: %s)", id, body, motor, accessory); }
}
