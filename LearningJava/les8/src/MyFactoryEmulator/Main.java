package MyFactoryEmulator;

import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.logging.Logger;
import java.util.concurrent.Semaphore;

public class Main {
    public static void main(String[] args) {
        try {
            Semaphore carReady = new Semaphore(0, true);
            // Загрузка конфигурации
            MyConfig config = new MyConfig("MyFactoryEmulator/config.properties");

            int motorDelay = config.getInt("motorDelay");
            int bodyDelay = config.getInt("bodyDelay");
            int accessoryDelay = config.getInt("accessoryDelay");
            int carStorageSize = config.getInt("carStorageSize");

            // Создание логгера
            Logger logger = MyLogger.createLogger("FactoryLogger");

            // Создание складов
            Storage<Body> bodyStorage = new Storage<>(10);
            Storage<Motor> motorStorage = new Storage<>(10);
            Storage<Accessory> accessoryStorage = new Storage<>(10);
            Storage<Car> carStorage = new Storage<>(carStorageSize);

            //---
            Thread assembler1 = new Thread(new CarAssembly(bodyStorage, motorStorage, accessoryStorage, carStorage, carReady));
            Thread assembler2 = new Thread(new CarAssembly(bodyStorage, motorStorage, accessoryStorage, carStorage, carReady));
            assembler1.start();
            assembler2.start();


            // Создание и запуск поставщиков
            Thread bodySupplier = new Thread(new Supplier<>(bodyStorage, Body::new, bodyDelay));
            Thread motorSupplier = new Thread(new Supplier<>(motorStorage, Motor::new, motorDelay));
            Thread accessorySupplier = new Thread(new Supplier<>(accessoryStorage, Accessory::new, accessoryDelay));

            bodySupplier.start();
            motorSupplier.start();
            accessorySupplier.start();

            // Сборка автомобилей (через пул потоков)
            ExecutorService carAssemblyPool = Executors.newFixedThreadPool(2);
            for (int i = 0; i < 2; i++) {
                carAssemblyPool.submit(new CarAssembly(bodyStorage, motorStorage, accessoryStorage, carStorage, carReady));
            }

            // Запуск дилера
            Thread dealer = new Thread(new Dealer(carStorage, 1000, logger, carReady));
            dealer.start();

            // Контроллер склада готовых изделий (пока в заготовке)
            Thread controller = new Thread(new ControllerWarehouse(carStorage));
            controller.start();

        } catch (IOException e) {
            System.err.println("Ошибка конфигурации: " + e.getMessage());
        }
    }
}
