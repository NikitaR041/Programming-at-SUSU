package MyFactoryEmulator;

public class ControllerWarehouse implements Runnable{
    private final Storage<Car> carStorage;

    public ControllerWarehouse(Storage<Car> carStorage) {
        this.carStorage = carStorage;
    }

    @Override
    public void run(){
        while (carStorage.getItemCount() >= carStorage.getMaxsizeWarehouse()) {
            try{
                wait(); //Работает текущий поток, а другие ждут

            }catch(InterruptedException e){
            }
        }
        notifyAll(); //Теперь работают другие потоки
    }
}
