package MyFactoryEmulator;

public class ControllerWarehouse implements Runnable{
    private final Storage<Car> carStorage;
    public ControllerWarehouse(Storage<Car> carStorage){
        this.carStorage = carStorage;
    }
    @Override
    public void run(){
        try {
            while (!Thread.currentThread().isInterrupted()) {
                synchronized (carStorage) {
                    int count = carStorage.getItemCount();
                    int capacity = carStorage.getMaxsizeWarehouse();

                    if (count >= capacity) {
                        System.out.println("Склад машин полон (" + count + "/" + capacity + "). Ожидаем продажи...");
                        carStorage.wait();
                    } else {
                        carStorage.notifyAll();
                    }
                }

                Thread.sleep(500);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}