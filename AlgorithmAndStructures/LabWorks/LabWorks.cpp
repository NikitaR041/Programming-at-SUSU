#include <iostream>
#include <queue>

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

/*
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

    void popElem() {
        if (top != nullptr) {
            top = std::move(top->next);
        }
    }

    int topElem() const {
        if (top != nullptr) {
            return top->value;
        }
    }

    bool isEmpty() {
        return top == nullptr;
    }
};


int main()
{

    Stack obj;
    obj.pushElem(10);
    obj.pushElem(20);
    obj.pushElem(30);
    
    std::cout << obj.topElem() << '\n';
    
    obj.popElem();
    std::cout << obj.topElem() << '\n';

    obj.popElem();
    std::cout << obj.topElem() << '\n';

    obj.popElem();
    std::cout << obj.topElem() << '\n';

    if (obj.isEmpty()) {
        std::cout << "Стек пуст!" << '\n';
    }
    return 0;
}*/

/*
Задание 2 - (2736)
Используя класс queue из STL решите следующую задачу.

Вывести простые числа среди чисел от 2 до N, используя следующий алгоритм:

I. Первоначально очередь имеет все числа от 2 до N.
    1)Взять первый элемент X из входной очереди и напечатать.
    2)В выходную очередь поместить числа из очереди, которые не кратны X.
    3)Поменять входную и выходную очередь (swap).
    4)Пока очередь не пуста, то повторять дествия с шага 2.
II. Ввод содержит одно целое число N (2 ≤ N ≤ 100000).

Задача:
1)Нужно реализовать именно АТД - т.е. абастрактный класс
*/

int main() {
    int N = 0;
    std::queue<int> my_queue;
    std::queue<int> temp_queue;
    
    std::cin >> N;
    if (!(2 <= N && N <= 100000)) return 0;
    for (short i = 2; i <= N; i++) {
        my_queue.push(i);
    }

    //Алгоритм
    while (!my_queue.empty()) {
        int X = my_queue.front(); // (1)
        my_queue.pop();
        std::cout << "Элемент X из выходной очереди: " << X << '\n';
        while (!my_queue.empty()) {
            int value = my_queue.front();
            my_queue.pop();
            if (value % X != 0) temp_queue.push(value); // (2)
        }
        swap(my_queue, temp_queue);
    }
    for (short i = 0; i < my_queue.size(); i++) {
        std::cout << my_queue.front() << '\n';
    }
    return 0;
}