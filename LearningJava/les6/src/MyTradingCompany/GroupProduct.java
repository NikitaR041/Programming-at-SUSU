package MyTradingCompany;
import java.util.ArrayList;
import java.util.List;

//Класс Категория продуктов (молочка, овощи, фрукты)
public class GroupProduct {
    private List<String> myGroupProduct = new ArrayList<>();


    //Геттеры и сеттеры
    public void setMyGroupproduct(String[] items) {
        for(String i : items){
            myGroupProduct.add(i);
        }
    }
    public void getMyGroupproduct(){
        for(String item : myGroupProduct){
            System.out.println("Ваши категории в компании:" + item);
        }
    }
}
