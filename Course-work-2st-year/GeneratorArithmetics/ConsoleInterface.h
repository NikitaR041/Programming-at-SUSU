#pragma once
#include <memory>
#include <vector>

//Класс, принимающий настройки от пользователя
class ConsoleInterface {
    unsigned short int count_arith_expres; //Количество арифметических выражений
    unsigned short int count_operations; //Количество арифметических операций + - * / -(-)
    short int range_num_min; //Диапазон чисел, минимум
    short int range_num_max; //Диапазон чисел, максимум
    //std::unique_ptr<char[]> symbols; //Выбор арифметических операций - массив

public:
    ConsoleInterface(unsigned short int count_arith_expres = 0, unsigned short int count_operations = 0, short int range_num_min = 0, short int range_num_max = 0) :
        count_arith_expres(count_arith_expres), count_operations(count_operations), range_num_min(range_num_min), range_num_max(range_num_max) {}

    unsigned short int getCountArithExpres() const { return this->count_arith_expres; } //Метод для получения значения из поля count_arith_expres – количество арифметических выражений
    unsigned short int getCountOperation() const { return this->count_operations; } //Метод для получения значения из поля count_operations – количество арифметических операций
    short int getRangeNumMin() const { return this->range_num_min; } //Метод для получения минимального значения из поля range_num_min
    short int getRangeNumMax() const { return this->range_num_max; } //Метод для получения максимального значения из поля range_num_max
    //const char* getSymbols() const { return this->symbols.get(); } //Метод для получения значений – арифметических знаков

    void setSymbols(std::unique_ptr<char[]>& symbols); //Метод для задания операций 
    
    void setConfigureInterface(); //Метод ввода значений с консоли
};

