/*
Вариант 19
Описать класс ≪процессор≫, содержащий сведения о марке, тактовой частоте, объеме кэша и стоимости.
Предусмотреть инициализацию с проверкой допустимости значений полей.
В случае недопустимых значений полей выбрасываются исключения.
Описать свойства для получения состояния объекта.
Описать класс «материнская плата», включающий класс «процессор» (как ссылку) и объем установленной оперативной памяти.
Предусмотреть инициализацию с проверкой допустимости значений поля объема памяти.
В случае недопустимых значений поля выбрасывается исключение.
Описать свойства для получения состояния объекта.

Исключения придумать свои
*/
package computers;
public class Processor{
    private String stamp; //Марка процессора
    private float frequency; //Тактовая частота
    private int cachesize; //Объем кэша
    private int price; //Стоимость

    //Конструктор без параметров (Конструктор по умолчанию)
    public Processor(){}

    //Конструктор с параметрами
    public Processor(String stamp, float frequency, int cachesize, int price) throws ProcessorException {
        isError(stamp, frequency, cachesize, price);
        this.stamp = stamp;
        this.frequency = frequency;
        this.cachesize = cachesize;
        this.price = price;
    }

    //Приватный метод для проверки допустимости значений
    private void isError(String stamp, float frequency, int cachesize, int price ) throws ProcessorException {
        if (stamp.isEmpty() || stamp == null) throw new ProcessorException("Должно быть название процессора!");
        if (frequency < 0 ) throw new ProcessorException("Тактовая частота не должна быть меньше 0!");
        if (cachesize < 0 ) throw new ProcessorException("Объем кэша не должна быть меньше 0!");
        if (price < 0 ) throw new ProcessorException("Цена на процессор не должна быть меньше 0!");

    }

    //Переопределение класса String для того, чтобы работал getProcessor в классе computers.MotherBoard
    @Override
    public String toString(){ return "Процессор " + stamp;}

    //Свойства (Геттеры, сеттеры)
    public String getStamp() {return stamp;}
    public void setStamp(String stamp) throws ProcessorException {
        isError(stamp, this.frequency, this.cachesize, this.price);
        this.stamp = stamp;
    }

    public int getCachesize() { return cachesize; }
    public void setCachesize(int cachesize) throws ProcessorException {
        isError(this.stamp, frequency, this.cachesize, this.price);
        this.cachesize = cachesize;
    }

    public float getFrequency(){ return frequency; }
    public void setFrequency(float frequency) throws ProcessorException {
        isError(this.stamp, this.frequency, cachesize, this.price);
        this.frequency = frequency;
    }

    public int getPrice() { return price; }
    public void setPrice(int price) throws ProcessorException {
        isError(this.stamp, this.frequency, this.cachesize, price);
        this.price = price;
    }
}

