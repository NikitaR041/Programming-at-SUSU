package MyPages;

public class Material {
    private String nameMaterial; //Название материала
    private String dateMaterial; //Дата производства
    private int weightMaterial; //Вес материала

    //Конструктор по умолчанию
    public Material(){}
    //Конструктор с параметрами
    public Material(String nameMaterial, String dateMaterial, int weightMaterial){
        this.nameMaterial = nameMaterial;
        this.dateMaterial = dateMaterial;
        this.weightMaterial = weightMaterial;
    }

    //Собственный вывод материала на экран
    // В класс Material
    @Override
    public String toString() {
        return nameMaterial + " (Дата: " + dateMaterial + ", Вес: " + weightMaterial + "г)";
    }
}
