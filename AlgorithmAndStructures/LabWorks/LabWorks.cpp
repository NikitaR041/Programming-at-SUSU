#include <iostream>

/*
Лабораторная работа - Вариант 19
*/

/*
Задание 1
Реализуйте АТД Стек на односвязном списке (forward_list).

Решение:
1)Нужно реализовать узел
2)Реализовать методы 

*/

class Stack {
private:
    struct Node {
        int value; //Значение узла
        std::unique_ptr<Node> next; //Указатель на следующий элемент
        Node(int value) : value(value), next(nullptr) {}
    };

    std::unique_ptr<Node> top; //Указатель на верхний элемент
public:
    Stack() : top(nullptr) {}
    
    //Реализовать методы:
    void pushElem(int value) {
        std::unique_ptr<Node> obj = std::make_unique<Node>(value);
        obj->next = std::move(top);
        top = std::move(obj);
    }

    //Исправить
    void popElen() {
        if (top != nullptr) top;
    }
};


int main()
{
    std::cout << "Hello World!\n";
}
