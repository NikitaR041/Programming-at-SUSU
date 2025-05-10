package MyFactoryEmulator;

public class Body {
    private static int counter = 0; //Счетчик - количество созданных объектов от класса Body
    private final int id; //Уникальный индетификатор для каждого объекта класса Body
                                            //Поле id - обновляется после каждого созданного объекта класса Body
    public Body(){ this.id = counter++; }
    //Метод - получение индетификатора объекта классса Body
    public int getId(){ return id;}
    //Метод - получение общего количества произведенных объектов класса Body
    public static int getTotalCount(){ return counter;}
    @Override
    public String toString(){ return "Body#" + id; }
}
