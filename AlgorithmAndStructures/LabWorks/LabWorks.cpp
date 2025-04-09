#include <iostream>
#include <queue>
#include <unordered_set>
#include <forward_list>

/*
Лабораторная работа - Вариант 19
*/

//Задание 1
/*
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
class Stack {
private:
    std::forward_list<int> MyStack;
public:
    // Добавление элемента на вершину стека (в начало списка)
    void pushElem(int value) {
        MyStack.push_front(value);
    }

    // Удаление верхнего элемента стека
    void popElem() {
        if (!MyStack.empty()) MyStack.pop_front();
    }

    // Получение верхнего элемента
    int topElem() const {
        if (!MyStack.empty()) return MyStack.front();
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return MyStack.empty();
    }
};
*/
//Задание 2 - (2736)
/*
Используя класс queue из STL решите следующую задачу.

Вывести простые числа среди чисел от 2 до N, используя следующий алгоритм:

I. Первоначально очередь имеет все числа от 2 до N.
    1)Взять первый элемент X из входной очереди и напечатать.
    2)В выходную очередь поместить числа из очереди, которые не кратны X.
    3)Поменять входную и выходную очередь (swap).
    4)Пока очередь не пуста, то повторять дествия с шага 2.
II. Ввод содержит одно целое число N (2 ≤ N ≤ 100000).

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
        //std::cout << "Элемент X из выходной очереди: " << X << '\n';
        std::cout << X << ' ';
        while (!my_queue.empty()) {
            int value = my_queue.front();
            my_queue.pop();
            if (value % X != 0) temp_queue.push(value); // (2)
        }
        swap(my_queue, temp_queue);
    }
    return 0;
}
*/

//Задание 3
/*
Абстрактный тип данных (АТД) — это математическая модель для типов данных, где тип данных определяется поведением (семантикой) с точки зрения пользователя данных, 
а именно в терминах возможных значений, возможных операций над данными этого типа и поведения этих операций.
Конкретные реализации АТД называются структурами данных. 
В С++ структуры данных реализуются как классы. В задаче 3 необходимо определить АТД, не нужно писать реализацию класса С++!

Определите АТД для хранения информации об неориентированном графе: количество вершин N, количество ребер, список всех ребер (пара из номеров вершин от 0 до N−1),
списки номеров соседних вершин для каждой вершины. 
Перечислите методы АТД, обеспечивающие последовательный доступ к информации и её изменение, аргументы и возвращаемые значения каждого метода с комментариями.

Последовательный доступ к данным выполняется через for и может быть реализован через итераторы 
(собственные типы - АТД, не STL) или доступ по номеру (если порядок хранения данных является важным как в АТД Массив)


//Неориентированный граф
class Graph {
public:
    class EdgeIterator {
    public:
        //Требование:E>0
        //Действие: Возвращает true, если остались не просмотренные рёбра, иначе false.
        bool hasNext() const;
        //Требование: нет.
        //Действие: Сбрасывает итератор в начальное положение.
        void reset();
        //Требование: нет.
        //Действие: Возвращает текующее ребро, затем переход к следующему.
        Edge next();
    };

    class NeighborIterator {
    public:
        //Требование:V>0
        //Действие: Возвращает true, если остались не просмотренные вершины, иначе false.
        bool hasNext() const;
        //Требование: нет.
        //Действие: Сбрасывает итератор в начальное положение.
        void reset();
        //Требование: нет.
        //Действие: Возвращает текующего соседа вершины, затем переход к следующему.
        int next();
    };

    //Требование: нет.
    //Действие: Увеличивает количество вершин на 1. Возвращает номер добавленный вершины.
    void addVertex(int V);    
    //Требование: V >= 0.
    //Действие: Удаляет вершину V из графа, а также рёбра, инцидентные ей.
    void removeVertex(int V);
    //Требование: E >= 0,  E != V, т.е. количество рёбер на 1 меньше, чем количество вершин.
    //Действие: Добавление ребра между E и V.
    void addEdge(int V, int E);
    //Требование: E>=0, существование ребра.
    //Действие: Удаление между E и V.
    void removeEdge(int V, int E);

    //Требование: нет.
    //Действие: Возвращает true, если существует ребро(E,V), иначе false.
    bool isEdge(int V, int E);
    
    //Требование: нет.
    //Действие: Возвращает количество вершин.
    int getVertexCount() const;
    //Требование: нет.
    //Действие: Возвращает количество рёбер.
    int getEdgeCount() const;
    //Требование: V>=0, E>=0.
    //Действие: Возвращает итератор по всем рёбрам графа.
    EdgeIterator getEdgeIterator() const;
    //Требование: V >=0, E>=0.
    //Действие: Возвращает итератор по всем вершинам, смежным вершине V.
    NeighborIterator getNeighborIterator(int v) const;
};
*/

//Задание 4
/*
Предложите структуры данных для представления АТД из задания 3. 
Перечислите поля, их типы и комментарии к каждому полю. 
Укажите оценку эффективности (амортизированную или среднюю) для каждого метода с учетом использованных структур данных. 
Хранимая в структуре информация не должна дублироваться.

Это отдельная задача. Не объединяете с задачей 3! Не пишите реализацию методов, нужно указать только оценку эффективности.


//Для хранение неориентированного графа подойдет список смежностей.

class Graph {
private:
    int V; //Количество вершин
    int E; //Количество рёбер
public:
    //Требование: нет.
    //Действие: Увеличивает количество вершин на 1. Возвращает номер добавленный вершины.
    //Асимптотическая сложность: O(1)
    void addVertex(int V);
    //Требование: V >= 0.
    //Действие: Удаляет вершину V из графа, а также рёбра, инцидентные ей.
    //Асимптотическая сложность: O(1)
    void removeVertex(int V);
    //Требование: E >= 0,  E != V, т.е. количество рёбер на 1 меньше, чем количество вершин.
    //Действие: Добавление ребра между E и V.
    //Асимптотическая сложность: O(E+V)
    void addEdge(int V, int E);
    //Требование: E>=0, существование ребра.
    //Действие: Удаление между E и V.
    //Асимптотическая сложность: O(1)
    void removeEdge(int V, int E);

    //Требование: нет.
    //Действие: Возвращает true, если существует ребро(E,V), иначе false.
    //Асимптотическая сложность: O(1)
    bool isEdge(int V, int E);

    //Требование: нет.
    //Действие: Возвращает количество вершин.
    //Асимптотическая сложность: O(1)
    int getVertexCount() const;
    //Требование: нет.
    //Действие: Возвращает количество рёбер.
    //Асимптотическая сложность: O(1)
    int getEdgeCount() const;
    //Требование: V>=0, E>=0.
    //Действие: Возвращает итератор по всем рёбрам графа.
    //Асимптотическая сложность:O(N+M), где M - число ребер, N - число вершин.
    EdgeIterator getEdgeIterator() const;
    //Требование: V >=0, E>=0.
    //Действие: Возвращает итератор по всем вершинам, смежным вершине V.
    //Асимптотическая сложность:O(k), где k - число соседей у вершины V.
    NeighborIterator getNeighborIterator(int v) const;
};
*/

//Задание 5
/*
Напишите функцию обхода бинарного дерева по возрастанию глубины (с помощью очереди), заданного следующей структурой:
struct node { int value; node *left, *right; };
К каждому значению, хранящемуся в дереве, функция применяет функцию, указанную в качестве аргумента:
void BFSorder(node *n, void (*f)(int));

#include <iostream>
#include <queue>

struct node {
    int value;
    node* left, * right;
};

// Функция, применяемая к узлу (просто выводит значение)
void printValue(int val) {
    std::cout << val << " ";
}

// Функция обхода бинарного дерева в ширину (BFS)
void BFSorder(node* n, void (*f)(int)) {
    if (!n) return;  // Если дерево пустое, сразу выходим

    std::queue<node*> q;  // Очередь для BFS
    q.push(n);  // Добавляем корень в очередь

    while (!q.empty()) {
        node* current = q.front();  // Берём первый элемент
        q.pop();  // Удаляем его из очереди

        f(current->value);  // Применяем функцию f

        // Добавляем потомков в очередь
        if (current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
}

// Тестовый запуск
int main() {
    // Создадим дерево:
    node* root = new node{ 1, nullptr, nullptr };
    root->left = new node{ 2, nullptr, nullptr };
    root->right = new node{ 3, nullptr, nullptr };
    root->left->left = new node{ 4, nullptr, nullptr };
    root->left->right = new node{ 5, nullptr, nullptr };
    root->right->left = new node{ 6, nullptr, nullptr };
    root->right->right = new node{ 7, nullptr, nullptr };

    std::cout << "Обход в ширину (BFS): ";
    BFSorder(root, printValue);  // Выведет: 1 2 3 4 5 6 7

    return 0;
}
*/


//Задание 6 - (2379)
/*
Используя декартово дерево из лекций решите следующую задачу.
Будем называть i-й элемент последовательности a1, a2, ..., aN медианным, если количество элементов, меньших или равных ai среди элементов a1, a2, ..., ai−1, 
больше или равно количеству элементов, больших или равных ai среди элементов ai+1, ai+2, ..., aN. 
В последовательности может быть несколько медианных элементов.
Напишите программу, которая находит минимальный индекс медианного элемента.

В приложении MinIDE работает


#include <iostream>
#include <functional>
#include <stdexcept>
#include <utility>
#include <cstdlib>

using namespace std;

template <typename T>
class ITreap {
    struct node {
        T v; // значение элемента
        size_t k; // неявный ключ - количество элементов в поддереве
        int y; // случайная высота
        node* left = nullptr;
        node* right = nullptr;

        node(T v) : v(v), k(1), y(rand()) {}
    };

    node* root;

    size_t size(node* n) const {
        return n ? n->k : 0;
    }

    void update(node* t) {
        if (!t) return;
        t->k = 1 + size(t->left) + size(t->right);
    }

    pair<node*, node*> spliti(node* t, size_t k) { // разрезание по количеству
        if (!t || k >= t->k) return { t, nullptr };
        if (k == 0) return { nullptr, t };
        size_t l = size(t->left);
        if (l < k) {
            auto [t1, t2] = spliti(t->right, k - l - 1);
            t->right = t1;
            update(t);
            return { t, t2 };
        }
        else {
            auto [t1, t2] = spliti(t->left, k);
            t->left = t2;
            update(t);
            return { t1, t };
        }
    }

    node* merge(node* t1, node* t2) { // слияние
        if (!t2) return t1;
        if (!t1) return t2;
        if (t1->y > t2->y) {
            t1->right = merge(t1->right, t2);
            update(t1);
            return t1;
        }
        else {
            t2->left = merge(t1, t2->left);
            update(t2);
            return t2;
        }
    }

    node* find(size_t k) const { // поиск узла по номеру
        node* p = root;
        while (p) {
            size_t l = size(p->left);
            if (l == k) break;
            else if (k < l) p = p->left;
            else {
                k -= l + 1;
                p = p->right;
            }
        }
        return p;
    }

    void foreach(const function<void(T&)>& f, node* p) const { // обход дерева
        if (!p) return;
        foreach(f, p->left);
        f(p->v);
        foreach(f, p->right);
    }

    void free(node* p) { // освобождение памяти
        if (!p) return;
        free(p->left);
        free(p->right);
        delete p;
    }

public:
    ITreap() : root(nullptr) {}
    ITreap(const ITreap&) = delete; // запрет копирования
    ITreap& operator=(const ITreap&) = delete; // запрет присваивания
    ~ITreap() { free(root); }

    size_t size() const {
        return size(root);
    }

    T& operator[](size_t k) { // доступ к элементу по индексу
        if (k >= size()) throw runtime_error("Wrong index");
        node* p = find(k);
        return p->v;
    }

    T operator[](size_t k) const {
        if (k >= size()) throw runtime_error("Wrong index");
        node* p = find(k);
        return p->v;
    }

    void inserti(size_t k, T v) { // вставка
        if (k > size()) throw runtime_error("Wrong index");
        node* m = new node(v);
        auto [t1, t2] = spliti(root, k);
        root = merge(merge(t1, m), t2);
    }

    void erasei(size_t k) { // удаление
        if (k >= size()) throw runtime_error("Wrong index");
        auto [t1, t] = spliti(root, k);
        auto [m, t2] = spliti(t, 1);
        root = merge(t1, t2);
        delete m;
    }

    void foreach(const function<void(T&)>& f) const {
        foreach(f, root);
    }
};

int main() {
    ITreap<int> t;

    // Пример использования
    t.inserti(0, 10); // {10}
    t.inserti(1, 20); // {10, 20}
    t.inserti(1, 15); // {10, 15, 20}

    t.foreach([](int& v) { cout << v << "\n"; });

    t[2] = 25; // {10, 15, 25}
    t.erasei(1); // {10, 25}

    cout << t[0] << "\n";
    cout << t[1] << "\n";

    return 0;
}
*/

//Задание 7 - 
/*

*/