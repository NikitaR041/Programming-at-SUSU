#pragma once
#ifndef _CONSOLEINTERFACE_HPP_
#define _CONSOLEINTERFACE_HPP_
#include <vector>
#include <string>

//Класс, принимающий настройки от пользователя
class ConsoleInterface {
    short int count_arith_expres; //Количество арифметических выражений
    short int count_operations; //Количество арифметических операций + - * / -(-)
    int range_num_min; //Диапазон чисел, минимум
    int range_num_max; //Диапазон чисел, максимум
    std::string symbols; //Выбор арифметических операций - массив

public:
    //Конструктор 
    ConsoleInterface(short int count_arith_expres = 0, short int count_operations = 0, int range_num_min = 0, int range_num_max = 0, std::string symbols = "") :
        count_arith_expres(count_arith_expres), count_operations(count_operations), range_num_min(range_num_min), range_num_max(range_num_max), symbols(symbols) {}

    short int getCountArithExpres() const { return this->count_arith_expres; } //Метод для получения значения из поля count_arith_expres – количество арифметических выражений
    short int getCountOperation() const { return this->count_operations; } //Метод для получения значения из поля count_operations – количество арифметических операций
    int getRangeNumMin() const { return this->range_num_min; } //Метод для получения минимального значения из поля range_num_min
    int getRangeNumMax() const { return this->range_num_max; } //Метод для получения максимального значения из поля range_num_max
    
    std::string getSymbols() { return this->symbols; } // Метод для получения символов
    
    void setSymbols(); //Метод для задания операций 
    void setConfigureInterface(); //Метод ввода значений с консоли
};

#endif // !_CONSOLEINTERFACE_HPP_
