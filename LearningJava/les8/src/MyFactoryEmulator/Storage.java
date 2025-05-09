package MyFactoryEmulator;

import java.util.LinkedList;
import java.util.Queue;


/*
Класс Storage - это обобщенный класс, от которого объявлены объекты "Склад двигателей", "Склад кузовов",
    "Склад аксессуаров", "Склад готовых изделий".
*/


public class Storage<T> {
    private final Queue<T> warehouse = new LinkedList<T>(); //Само хранилище в виде структуры данных очередь
    private final int maxsizeWarehouse; //Максимальный размер хранилища

    //Конструктор с параметром
    public Storage(int maxsizeWarehouse) { this.maxsizeWarehouse = maxsizeWarehouse; }

    //Метод добавления элемента в склад
    public synchronized void addItem(T item){
        while (warehouse.size() >= maxsizeWarehouse) {
            try{
                wait(); //Работает текущий поток, а другие ждут
            }catch(InterruptedException e){
            }
        }
        warehouse.add(item);
        notifyAll(); //Теперь работают другие потоки
    }

    //Метод получение элемента из склада
    public synchronized T takeItem(){
        while (warehouse.isEmpty()) {
            try{
                wait(); //Работает текущий поток, а другие ждут
            }catch(InterruptedException e){
            }
        }
        T item = warehouse.poll();
        notifyAll(); //Теперь работают другие потоки
        return item;
    }

    //Метод получение количества элементов в складе
    public synchronized int getItemCount(){ return warehouse.size(); }
    //Метод получение максимального размера склада
    public int getMaxsizeWarehouse(){ return this.maxsizeWarehouse; }
}
