package MyFactoryEmulator;
import java.util.concurrent.Semaphore;

/*
Класс CarAssembly - класс, который представляет сборку автомобилей из частей объектов классов Body, Motor, Accessory
*/

public class CarAssembly implements Runnable{

    private final Semaphore carReady; //Семафор - для синхронизации
    //Поля - хранилища элементов
    private final Storage<Body> bodyStorage;
    private final Storage<Motor> motorStorage;
    private final Storage<Accessory> accessoryStorage;
    private final Storage<Car> carStorage;

    public CarAssembly(Storage<Body> bodyStorage, Storage<Motor> motorStorage,
                       Storage<Accessory> accessoryStorage, Storage<Car> carStorage, Semaphore carReady) {
        this.bodyStorage = bodyStorage;
        this.motorStorage = motorStorage;
        this.accessoryStorage = accessoryStorage;
        this.carStorage = carStorage;
        this.carReady = carReady;
    }


    @Override
    public void run(){
        try {
            while (!Thread.currentThread().isInterrupted()) {
                Body body = bodyStorage.takeItem();
                Motor motor = motorStorage.takeItem();
                Accessory accessory = accessoryStorage.takeItem();
                Car car = new Car(body, motor, accessory);
                carStorage.addItem(car);
                System.out.println("Собрана машина: " + car);
                carReady.release(); // разрешаем дилеру продать
                Thread.sleep(500); // необязательная задержка
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
