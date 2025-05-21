package MyFactoryEmulator;
import java.util.logging.Logger;
import java.util.concurrent.Semaphore;
/*
Класс Dealer - класс, который представляет объект дилера, продающего автомобили
*/

public class Dealer implements Runnable {
    private final Semaphore carReady;

    private final Storage<Car> carStorage; //Хранилище объектов для класса Car
    private final int delayMs; //Задержка в миллисекундах
    private final Logger logger; //Логирование

    public Dealer(Storage<Car> carStorage, int delayMs, Logger logger, Semaphore carReady) {
        this.carStorage = carStorage;
        this.delayMs = delayMs;
        this.logger = logger;
        this.carReady = carReady;
    }

    @Override
    public void run(){
        try {
            while (!Thread.currentThread().isInterrupted()) {
                carReady.acquire(); // ждём, пока появится собранная машина
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
