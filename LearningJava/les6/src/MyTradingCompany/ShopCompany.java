package MyTradingCompany;

//Класс Торговая компания
public class ShopCompany {
    //Поля
    private String NameCompany;
    private String DateCompany;
    private int INN;

    public ShopCompany(String nameCompany, String dateCompany, int inn){
        this.NameCompany = nameCompany;
        this.DateCompany = dateCompany;
        this.INN = inn;
    }

    //Геттеры
    public void getInfoCopmany() {
        System.out.println("Компания: " + this.NameCompany + " Год создания: " + this.DateCompany + " Код подразделения: " + this.INN);
    }
}
