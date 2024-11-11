#include <iostream>
#include <memory>

/*
Извини, я случайно отправил тебе сообщение.
Смотри на 2 этапе разработки курсовой работы, преподаватель хочет, чтобы я расписал базовые интерфейсы классов (которые могут быть изменены впоследствии).
Помоги, пожалуйста, как должен выглядеть базовый интерфейс класса BinaryTree и Node, а также ConsoleIntarface ?


*/

//Разработаем предварительный класс ConsoleInterface
class ConsoleInterface {
    unsigned short int count_arith_expres; //Количество арифметических выражений
    unsigned short int count_operations; //Количество арифметических операций + - * / -(-)
    short int range_num_min; //Диапазон чисел, минимум
    short int range_num_max; //Диапазон чисел, максимум
    std::unique_ptr<char[]> symbols; //Выбор арифметических операций

    public:
        ConsoleInterface(unsigned short int count_arith_expres = 0, unsigned short int count_operations = 0, short int range_num_min = 0, short int range_num_max = 0) :
            count_arith_expres(count_arith_expres), count_operations(count_operations), range_num_min(range_num_min), range_num_max(range_num_max), symbols{std::make_unique<char[]>(5)} {}
        ~ConsoleInterface() {}

    //Здесь может быть реализованы какие-то методы, но их ещё не нужно реализовывать
    //Property - т.е. Аксессоры для получения get и установление set каждыйх переменных, кроме symbols
    //ShowInterface - показать на консоли интерфейс
    
};

//Разработаем предварительный класс GeneratorArithmetic
class Node {
    short int value; //Значение в узле типа short int
    char sym; //Оператор (например, '+', '-', '*', '/', '-(-)')
    std::unique_ptr<Node> left; //Левый узел(лист)
    std::unique_ptr<Node> right; //Правый узел(лист)

    //...
};

//Нужно ещё реализовать класс ...
//...
int main()
{
    std::cout << "Hello World!\n";
}