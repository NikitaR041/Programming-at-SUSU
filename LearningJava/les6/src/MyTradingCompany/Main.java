package MyTradingCompany;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        ShopCompany obj1 = new ShopCompany("Пятерочка", "20.20.2020", 1232141);
        GroupProduct obj2 = new GroupProduct();
        Warehouse obj3 = new Warehouse();

        //Создаем экземпляры класса Product
        Product obj4 = new Product();
        Product obj5 = new Product("Простоквашино", "09.04.2025", 11111);
        Product obj6 = new Product("Провансаль", "31.03.2025", 222222);

        obj4.setNameProduct("Александр Б.Ю");
        obj4.setDate("20.20.2015");
        obj4.setBarCode(12314);

        String[] categories = {"Молочные продукты", "Хлебобулочные изделия", "Палеты"};
        obj2.setMyGroupproduct(categories);

        obj3.setMyWarehouse(obj4);
        obj3.setMyWarehouse(obj5);
        obj3.setMyWarehouse(obj6);

        //Ошибка: Так как класс Warehouse принимает объекты класса Product
        //obj3.setMyWarehouse(obj1);

        obj1.getInfoCopmany();
        obj2.getMyGroupproduct();
        obj3.getMyWarehouse();
    }
}