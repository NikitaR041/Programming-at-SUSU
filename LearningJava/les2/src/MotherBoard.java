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

public class MotherBoard {
    private Processor processor; // Ссылка класса "процессор"
    private int sizeMemory; //Объем оперативной памяти

    //Конструктор без параметров (Конструктор по умолчанию)
    public MotherBoard(){};
    //Конструктор с параметрами
    public MotherBoard(Processor processor, int sizeMemory) throws MotherBoardException{
        if (sizeMemory < 0) throw new MotherBoardException("Объём памяти не должен быть меньше нуля!");
        this.processor = processor;
        this.sizeMemory = sizeMemory;
    }

    //Свойства (геттеры, сеттеры)
    public Processor getProcessor() {return processor;}

    public int getSizeMemory() { return sizeMemory; }
    public void setSizeMemory(int sizeMemory) { this.sizeMemory = sizeMemory; }
}
