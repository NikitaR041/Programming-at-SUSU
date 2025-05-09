package MyFactoryEmulator;

/*
Класс Supplier - шаблонный класс, который обозначается, как "Поставщики аксессуаров", "Поставщики кузовов",
    "Поставщики двигателей"
*/

public class Supplier<T> implements Runnable {
    private final Storage<T> storage; //Хранилище объектов для класса Accessory
    private final SupplierFactory<T> factory; //Поле - вспомогательный интерфейс - это способ создания объектов типа Т (например, new Motor())
    private final int delayMs; //Задержка в миллисекундах

    //Конструктор с параметрами
    public Supplier(Storage<T> storage, SupplierFactory<T> factory, int delayMs) {
        this.storage = storage;
        this.factory = factory;
        this.delayMs = delayMs;
    }

    @Override
    public void run(){
        try {
            //Проверка завершения работы потока - isInterrupted, currentThread - получаем текущий поток
            while (!Thread.currentThread().isInterrupted()) {
                T item = factory.create();      // создать новый объект
                storage.addItem(item);          // положить на склад
                System.out.println("Поставлен: " + item);
                Thread.sleep(delayMs);          // пауза
            }
        } catch (InterruptedException e) {
            System.out.println("Поставщик остановлен: " + Thread.currentThread().getName());
            Thread.currentThread().interrupt();
        }
    }
}
