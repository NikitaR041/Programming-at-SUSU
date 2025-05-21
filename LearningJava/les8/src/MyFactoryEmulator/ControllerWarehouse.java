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
                Thread.sleep(100);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}