/*
Лабораторная работа 2. Простейшие классы. Обработка исключений.

Каждый разрабатываемый класс должен, как правило, содержать следующие элементы:
скрытые поля, конструкторы с параметрами и без параметров, методы, свойства.
Методы и свойства должны обеспечивать непротиворечивый, полный, минимальный и удобный интерфейс класса.
При возникновении ошибок должны выбрасываться исключения.
Написать программу, демонстрирующую все разработанные элементы класса.
В программе должна выполняться проверка всех разработанных элементов класса.

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

public class Main {
    public static void main(String[] args) {
        try {
            //Создаем экземпляры классов
            Processor obj1 = new Processor();
            Processor obj2 = new Processor("Intel", 5, 1500, 20000);
            MotherBoard obj3 = new MotherBoard(obj1, 36);
            MotherBoard obj4 = new MotherBoard(obj2, 36);

            //Использование свойств для объектов
            System.out.println("Установим значения для объекта obj1");
            obj1.setStamp("AMD");
            obj1.setCachesize(1200);
            obj1.setFrequency(4.3f);
            obj1.setPrice(15000);

            System.out.println("Получим значение полей из объектов obj1 и obj2");
            System.out.println("Название у объекта obj2 " + obj2.getStamp());

            System.out.println("Название у объекта obj1 " + obj1.getStamp());
            System.out.println("Размер кэша у объекта obj1 " + obj1.getCachesize());
            System.out.println("Тактовая частота у объекта obj1 " + obj1.getFrequency());
            System.out.println("Цена у объекта obj1 " + obj1.getPrice());

            System.out.println("Проверяем работоспособность функции getProcessor");
            System.out.println(obj3.getProcessor());
            System.out.println(obj4.getProcessor());

            //Изменение поля у объекта
            System.out.println("Изменение значения полей у объекта obj2");
            obj2.setStamp("Elbrus");
            System.out.println(obj2.getStamp());
            obj2.setFrequency(10f);
            System.out.println(obj2.getFrequency());
            obj2.setCachesize(500);
            System.out.println(obj2.getCachesize());
            obj2.setPrice(3000000);
            System.out.println(obj2.getPrice());

            //Пробуем вызвать ошибку
            computers.Processor obj5 = new computers.Processor("Intel", -4, -5, -2);
            MotherBoard obj6 = new MotherBoard(obj1, -1);
        } catch (ProcessorException ex) {
            System.out.println(ex.getMessage());
        } catch (MotherBoardException ex) {
            System.out.println(ex.getMessage());
        } catch(Exception ex){
            System.out.println(ex.getMessage());
        }

    }
}