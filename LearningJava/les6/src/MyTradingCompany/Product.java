package MyTradingCompany;

//Класс продукты (яблоки, помидоры, ананасы)
public class Product {
    private String NameProduct; //Название товара
    private String Date; //Дата изготовления
    private int BarCode; //Штрих-кода

    public Product(){}
    public Product(String nameProduct, String date, int barCode){
        this.NameProduct = nameProduct;
        this.Date = date;
        this.BarCode = barCode;
    }
    //Геттеры и сеттеры
    public int getBarCode() { return BarCode; }
    public String getDate() { return Date; }
    public String getNameProduct() { return NameProduct; }

    public void setNameProduct(String item){ this.NameProduct = item; }
    public void setDate(String item) { this.Date = item; }
    public void setBarCode(int item) { this.BarCode = item; }
}
