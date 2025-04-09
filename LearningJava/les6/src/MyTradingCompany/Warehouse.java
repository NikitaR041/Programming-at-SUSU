package MyTradingCompany;

import java.util.ArrayList;
import java.util.List;

//Класс Склад
public class Warehouse<T extends Product> {
    private List<T> MyWarehouse = new ArrayList<>(); //Список объектов класса Product

    //Геттеры и сеттеры
    public void setMyWarehouse(T item) { MyWarehouse.add(item); }
    public void getMyWarehouse(){
        for(T item : MyWarehouse){
            System.out.println("Вот ваши продукты: " + item.getNameProduct());
        }
    }
}