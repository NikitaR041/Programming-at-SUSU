/*
Вариант 19
Описать класс ≪процессор≫, содержащий сведения о марке, тактовой частоте, объеме кэша и стоимости.
Предусмотреть инициализацию с проверкой допустимости значений полей.
В случае недопустимых значений полей выбрасываются исключения.
Описать свойства для получения состояния объекта.
Описать класс «материнская плата», включающий класс «процессор» (как ссылку) и объем установленной оперативной памяти.
Предусмотреть инициализацию с проверкой допустимости значений поля объема памяти.
В случае недопустимых значений поля выбрасывается исключение.
Описать свойства дляполучения состояния объекта.

Исключения придумать свои
 */

public class Processor{
    private String stamp; //Марка процессора
    private int frequency; //Тактовая частота
    private int cachesize; //Объем кэша
    private int price; //Стоимость

    //Конструктор без параметров (Конструктор по умолчанию)
    public Processor(){}

    //Конструктор с параметрами
    public Processor(String stamp, int frequency, int cachesize, int price) throws ProcessorException {
        if (frequency < 0 || cachesize < 0 || price < 0){
            throw new ProcessorException("Недопустимые значения полей!");
        }
        this.stamp = stamp;
        this.frequency = frequency;
        this.cachesize = cachesize;
        this.price = price;
    }

    //Свойства (Геттеры, сеттеры)
    public int getCachesize() { return cachesize; }
    public void setCachesize(int cachesize) { this.cachesize = cachesize; }

    public int getFrequency(){ return frequency; }
    public void setFrequency(int frequency){ this.frequency = frequency; }

    public int getPrice() { return price; }
    public void setPrice(int price){ this.price = price; }
}

