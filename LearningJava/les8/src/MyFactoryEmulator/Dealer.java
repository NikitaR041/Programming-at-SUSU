package MyFactoryEmulator;

public class Dealer implements Runnable {
    private final Storage<Car> carStorage; //Хранилище объектов для класса Car
    private final int delayMs; //Задержка в миллисекундах

    public Dealer(Storage<Car> carStorage, int delayMs) {
        this.carStorage = carStorage;
        this.delayMs = delayMs;
    }

    @Override
    public void run(){
        try {
            while (!Thread.currentThread().isInterrupted()) {
                Car car = carStorage.takeItem(); // берём машину со склада
                System.out.println("Продана машина: " + car);
                Thread.sleep(delayMs); // задержка между продажами
            }
        } catch (InterruptedException e) {
            System.out.println("Дилер остановлен.");
            Thread.currentThread().interrupt();
        }
    }
}
