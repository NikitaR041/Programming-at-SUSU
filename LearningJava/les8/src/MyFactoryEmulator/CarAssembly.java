package MyFactoryEmulator;

/*
Класс CarAssembly - класс, который представляет сборку автомобилей из частей объектов классов Body, Motor, Accessory
*/

public class CarAssembly implements Runnable{
    //Поля - хранилища элементов
    private final Storage<Body> bodyStorage;
    private final Storage<Motor> motorStorage;
    private final Storage<Accessory> accessoryStorage;
    private final Storage<Car> carStorage;

    public CarAssembly(Storage<Body> bodyStorage, Storage<Motor> motorStorage,
                        Storage<Accessory> accessoryStorage,Storage<Car> carStorage) {
        this.bodyStorage = bodyStorage;
        this.motorStorage = motorStorage;
        this.accessoryStorage = accessoryStorage;
        this.carStorage = carStorage;
    }

    @Override
    public void run(){
        Body body = bodyStorage.takeItem();
        Motor motor = motorStorage.takeItem();
        Accessory accessory = accessoryStorage.takeItem();
        Car car = new Car(body, motor, accessory);
        carStorage.addItem(car);
        System.out.println("Собрана машина: " + car);
    }
}
