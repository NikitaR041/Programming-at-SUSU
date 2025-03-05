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

Пример рисунка
1) Создание двух 3-ёх объектов: 1 объект: значение 10, 2 объект: значение 20, 3 объект: значение 30
I. Создаем первый объект
top -> [10|nullptr]
II. Создаем второй объект
top -> [20|next] -> [10|nullptr]
III. Создаем третий объект
top -> [30|next] -> [20|next] -> [10|nullptr]

2) Удаление объектов уже имеющимися объектами в стеке
I. Удаляем верхний элемет
top -/-> [30|next] -> [20|next] -> [10|nullptr]
И получили следующее: top -> [20|next] -> [10|nullptr]
II. Удаляем вернхий объект:
top -/-> [20|next] -> [10|nullptr]
И получили следующий элемент: top -> [10|nullptr]
III. Удаляем верхний объект:
top -/-> [10|nullptr]
И получили следующий элемент: ПОЛУЧИЛИ ПУСТОЙ STACK
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
    
    void pushElem(int value) {
        std::unique_ptr<Node> obj = std::make_unique<Node>(value);
        obj->next = std::move(top);
        top = std::move(obj);
    }

    void popElen() {
        if (top != nullptr) {
            top = std::move(top->next);
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};


int main()
{
    std::cout << "Hello World!\n";
}
