package MyFactoryEmulator;
import java.util.logging.Logger;

/*
Класс Dealer - класс, который представляет объект дилера, продающего автомобили
*/

public class Dealer implements Runnable {
    private final Storage<Car> carStorage; //Хранилище объектов для класса Car
    private final int delayMs; //Задержка в миллисекундах
    private final Logger logger; //Логирование

    public Dealer(Storage<Car> carStorage, int delayMs, Logger logger) {
        this.carStorage = carStorage;
        this.delayMs = delayMs;
        this.logger = logger;
    }

    @Override
    public void run(){
        try {
            while (!Thread.currentThread().isInterrupted()) {
                synchronized (carStorage) {
                    carStorage.notifyAll();
                }
                Car car = carStorage.takeItem(); // берём машину со склада
                System.out.println("Продана машина: " + car);
                logger.info("Дилер продал: " + car);
                Thread.sleep(delayMs); // задержка между продажами
            }
        } catch (InterruptedException e) {
            System.out.println("Дилер остановлен.");
            Thread.currentThread().interrupt();
        }
    }
}
