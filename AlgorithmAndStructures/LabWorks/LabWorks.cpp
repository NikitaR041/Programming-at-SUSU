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
    std::forward_list<int> MyStack;
public:
    // Добавление элемента на вершину стека (в начало списка)
    void pushElem(int value) {
        MyStack.push_front(value);
    }

    // Удаление верхнего элемента стека
    void popElem() {
        if (!MyStack.empty()) throw std::underflow_error("Стек пустой");
        MyStack.pop_front();
    }

    // Получение верхнего элемента
    int topElem() const {
        if (MyStack.empty()) throw std::underflow_error("Стек пустой");
        return MyStack.front();
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

*/
//Неориентированный граф
/*
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
        //Действие: Переход к следующему ребру.
        void next();
        // Требование: E>0
        // Действие: Возвращает текущее ребро без перехода.
        Edge get() const;

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
        //Действие: Переход к следующему узлу.
        void next();
        // Требование: V>0
        // Действие: Возвращает текущего соседа без перехода.
        int get() const;
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

*/
//Для хранение неориентированного графа подойдет список смежностей.
/*
class Graph {
private:
    int V; //Количество вершин
    int E; //Количество рёбер
    std::vector<std::vector<int>> adjacencyList; //Списки смежности: для каждой вершины хранится список её соседей
    std::vector<std::pair<int, int>> edges; //Явный список всех рёбер графа: пары вершин (u, v), где u < v для уникальности в неориентированном графе
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

//Задание 7 - 2040 
/*
Используя дерево отрезков решите следующую задачу.
Мебибайту необходимо рассчитать энергетические нагрузки во время светомузыкального шоу. 
Управление 2^20 лампочками происходит следующим образом. 
Для каждого такта музыкального сопровождения указаны два целых числа, определяющих диапазон номеров лампочек, состояние которых должно измениться на противоположное. 
Если лампочка была выключена, она должна загореться, а горящая лампочка -- погаснуть. В начальный момент времени все лампочки выключены. 
Напишите программу, определяющую количество горящих лампочек после выполнения каждой команды.
Первая строка ввода содержит одно целое число N (1≤N≤100000) -- количество команд на переключение состояния лампочек. 
Далее следует N строк, каждая строка содержит два целых числа ai и bi (1≤ai≤bi≤220) - команда на переключение.
Вывести N строк, в i-ой строке вывести количество горящих лампочек после i-ой команды.

Работает на MinIDE
*/
/*
#include <vector>
#include <optional>
#include <functional>
#include <stdexcept>
#include <utility>
#include <cmath>     // для bit_ceil
#include <cstddef>   // для size_t
#include <algorithm> // для std::min и std::max

template <typename T, typename State>
struct Operation {
    State operator()(State s, size_t k) const {
        // Реализация операции для State
        return s;
    }
    T operator()(T v) const {
        // Реализация операции для T
        return v;
    }
    std::optional<Operation> combine(Operation other) const {
        // Реализация комбинирования двух операций
        return other;
    }
};

template <typename T, typename State>
class STree {
    using func = std::function<State(State, State)>;
    size_t n, n2;
    std::vector<std::pair<std::optional<Operation<T, State>>, State>> pyrmd;
    std::vector<T> values;
    func f;

    void update(size_t i, size_t k1, size_t k2) {
        if (i >= n2) return; // не применяется к листу
        pyrmd[i].second = f(state(2 * i, k1), state(2 * i + 1, k2)); // обновляем состояние поддерева
    }

    void add_op(size_t i, Operation<T, State> op) { // добавить или применить операцию
        if (i >= n2) values[i - n2] = op(values[i - n2]); // применить к листу
        else if (!pyrmd[i].first) pyrmd[i].first = op;
        else pyrmd[i].first = pyrmd[i].first->combine(op);
    }

    void clear_op(size_t i, size_t k) { // сдвинуть операцию вниз
        if (i >= n2 || !pyrmd[i].first) return;
        Operation<T, State> op = *(pyrmd[i].first);
        pyrmd[i].second = op(pyrmd[i].second, k);
        pyrmd[i].first = {};
        add_op(2 * i, op);
        add_op(2 * i + 1, op);
    }

    State state(size_t i, size_t k) { // состояние поддерева или листа
        if (i >= n2) {
            if (i - n2 >= n) return State();
            return State(values[i - n2]);
        }
        if (pyrmd[i].first) return (*(pyrmd[i].first))(pyrmd[i].second, k);
        return pyrmd[i].second;
    }

    State calc(size_t p, size_t k, size_t pi, size_t pj, size_t i, size_t j) {
        if (k == 1) return State(values[p - n2]); // лист
        if (i <= pi && pj <= j) // все поддерево
            return state(p, pj + 1 - pi);
        clear_op(p, pj + 1 - pi); // сдвинуть операцию
        k /= 2;
        size_t m = pi + k;
        // вернуть из одного поддерева
        if (j < m) return calc(p * 2, k, pi, m - 1, i, j);
        if (i >= m) return calc(p * 2 + 1, k, m, pj, i, j);
        // или комбинацию
        return f(calc(p * 2, k, pi, m - 1, i, j), calc(p * 2 + 1, k, m, pj, i, j));
    }

    void apply(size_t p, size_t k, size_t pi, size_t pj, size_t i, size_t j, std::optional<Operation<T, State>> op, T v) {
        if (k == 1) { // лист
            if (op) values[p - n2] = (*op)(values[p - n2]);
            else values[p - n2] = v;
            return;
        }
        if (i <= pi && pj <= j) { // полный отрезок
            if (op) add_op(p, *op);
            return;
        }
        clear_op(p, pj + 1 - pi); // сдвинуть операцию
        k /= 2;
        size_t m = pi + k;
        if (i < m) // обработать поддеревья, если есть
            apply(p * 2, k, pi, m - 1, i, j, op, v);
        if (j >= m)
            apply(p * 2 + 1, k, m, pj, i, j, op, v);
        update(p, std::min(pj + 1, m) - pi, std::max(static_cast<int>(pj + 1 - m), 0)); // пересчитать
    }

public:
    STree(size_t n, func f)
        : n(n), n2(std::bit_ceil(n)), pyrmd(2 * n2, { {}, State() }), values(n, T()), f(f) {}

    size_t size() const { return n; } // размер

    State calc(size_t i, size_t j) { // получить значение функции на отрезке
        if (i >= n || j >= n || i > j) throw std::runtime_error("Wrong index");
        return calc(1, n2, 0, n - 1, i, j);
    }

    T get(size_t i) { // получить i-й элемент
        if (i >= n) throw std::runtime_error("Wrong index");
        return values[i];
    }

    void set(size_t i, T v) { // изменить i-й элемент
        if (i >= n) throw std::runtime_error("Wrong index");
        apply(1, n2, 0, n - 1, i, i, {}, v);
    }

    void apply(size_t i, size_t j, Operation<T, State> op) { // изменить значения на отрезке
        if (i >= n || j >= n || i > j) throw std::runtime_error("Wrong index");
        apply(1, n2, 0, n - 1, i, j, op, T());
    }
};

#include <iostream> // для вывода

int main() {
    auto combine_func = [](int a, int b) { return a + b; };
    STree<int, int> tree(10, combine_func);
    tree.set(0, 1);
    tree.set(1, 2);
    tree.set(2, 3);

    int result = tree.calc(0, 2); // вычисление суммы на отрезке
    std::cout << "Результат: " << result << std::endl; // использование переменной
    return 0;
}
*/

//Задание 8
/*
Используя map из STL напишите решение следующей задачи с эффективностью O(NlogN).
Дана последовательность из n целых чисел. 
Найти непрерывную подпоследовательность максимальной длины, в которой нет одинаковых элементов. 
Вывести длину и начальный индекс найденной подпоследовательности.
*/
/*
#include <iostream>
#include <vector>
#include <map>

//У пары есть left и right
std::pair<int, int> func(std::vector<int>& nums) {
    std::map<int, int> my_slovar;
    int max_l = 0, start_ind = 0;
    int left = 0;

    for (int right = 0; right < nums.size(); right++) {
        if (my_slovar.find(nums[right]) != my_slovar.end() && my_slovar[nums[right]] >= left) {
            left = my_slovar[nums[right]] + 1; //Смещаем левый указатель правее
        }

        my_slovar[nums[right]] = right;

        if (right - left + 1 > max_l) {
            max_l = right - left + 1;
            start_ind = left;
        }
    }
    return { max_l, start_ind };
}

int main() {
    setlocale(LC_ALL, "rus");
    std::vector<int> nums = { 5, 3, 4, 3, 6, 7, 8, 3, 2 };
    auto result = func(nums);
    std::cout << "Максимальная длина: " << result.first << " Индекс, с которого найдена макс длина: " << result.second << std::endl;
    return 0;
}
*/
/*
#include <iostream>
#include <vector>
#include <map>

int main() {
    std::map<int, int> myMap;
    int left = 0; //Нижняя граница
    int right = 0; //Верхняя граница - наибольшая длина
    int s_index = 0; //Позиция, с которого начинается наибольшая длина
    std::vector<int> m = { 1,2,3,4,5 };
        
    //Идем по массиву
    for (int r = 0; r < m.size(); r++) { 
        if (myMap.count(m[r]) && myMap[m[r]] >= left) {
            left = myMap[m[r]] + 1;
        }
        myMap[m[r]] = r; //Добавляем элемент
        if ((r - left + 1) > right) {
            right = r - left + 1;
            s_index = left;
        }
    }
    for (auto elem : myMap) {
        std::cout << elem.first << ' ' << elem.second << '\n';
    }
    std::cout << '\n';
    std::cout << right << ' ' << s_index << '\n';
}*/

//Задание 9
/*
Сравните время работы set и unordered_set из STL для операций добавления N элементов, где N=100,10000,10^6,10^7. 
Ключами являются строки из случайных букв от a до z длиной ровно 16. Результат оформить в виде таблицы, время в ns. 
Привести код, использованный для измерения времени для одного значения N.
*/
/*
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <iomanip>

std::vector<double> m(0);

std::vector<std::string> generateSymbols(int N, int len = 16) {
    std::vector<std::string> strings;
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist('a', 'z');

    for (int i = 0; i < N; ++i) {
        std::string s;
        for (int j = 0; j < len; ++j)
            s += static_cast<char>(dist(gen));
        strings.push_back(s);
    }
    return strings;
}

void testSearching(std::vector<std::string>& data) {
    // Измерение времени для std::set
    {
        std::set<std::string> s;
        auto start1 = std::chrono::high_resolution_clock::now();
        for (const auto& str : data)
            s.insert(str);
        auto end1 = std::chrono::high_resolution_clock::now();
        auto duration_ns1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count();
        std::cout << "std::set: " << duration_ns1 << " ns\n";
        m.push_back(duration_ns1);
    }

    // Измерение времени для std::unordered_set
    {
        std::unordered_set<std::string> us;
        auto start2 = std::chrono::high_resolution_clock::now();
        for (const auto& str : data)
            us.insert(str);
        auto end2 = std::chrono::high_resolution_clock::now();
        auto duration_ns2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count();
        std::cout << "std::unordered_set: " << duration_ns2 << " ns\n";
        m.push_back(duration_ns2);
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int N1 = 100;
    int N2 = 10000;
    int N3 = 1000000; // Можно заменить на 100, 10000, 1'000'000, 10'000'000
    int N4 = 10000000;
    //std::vector<int> m = {100, 10000, 1000000, 10000000};
    std::vector<std::string> v1 = generateSymbols(N1);
    std::vector<std::string> v2 = generateSymbols(N2);
    std::vector<std::string> v3 = generateSymbols(N3);
    std::vector<std::string> v4 = generateSymbols(N4);

    testSearching(v1); 
    testSearching(v2);
    testSearching(v3);
    testSearching(v4);

    std::cout << '\n';
    std::cout << std::setw(30) << "set в ns" << std::setw(40) << "unordered_set в ns" << '\n';
    std::cout << "100" << std::setw(30) << m.at(0) << std::setw(30) << m.at(1) << std::setw(30) << '\n';
    std::cout << "10000" << std::setw(30) << m.at(2) << std::setw(30) << m.at(3) << std::setw(30) << '\n';
    std::cout << "1000000" << std::setw(30) << m.at(4) << std::setw(30) << m.at(5) << std::setw(30) << '\n';
    std::cout << "10000000" << std::setw(23) << m.at(6) << std::setw(30) << m.at(7) << std::setw(30) << '\n';

    return 0;
}*/

//Задание 15
/*
Напишите функцию для проверки, что в орграфе, заданном через списки смежных вершин, существует эйлеров путь (путь, проходящий по всем дугам графа). 
Сам путь находить не нужно.
*/

#include <vector>
#include <iostream>
using namespace std;

bool EylerRoute(const vector<vector<int>>& G) {
    int n = G.size();
    vector<int> in(n, 0), out(n, 0);

    for (int v = 0; v < n; ++v) {
        for (int u : G[v]) {
            out[v]++;
            in[u]++;
        }
    }

    int start_nodes = 0, end_nodes = 0;

    for (int i = 0; i < n; ++i) {
        if (out[i] - in[i] == 1)
            start_nodes++;
        else if (in[i] - out[i] == 1)
            end_nodes++;
        else if (in[i] != out[i])
            return false; 
    }
    return (start_nodes == 1 && end_nodes == 1) || (start_nodes == 0 && end_nodes == 0);
}
int main() {
    std::setlocale(LC_ALL, "Rus");
    vector<vector<int>> G = {
        {1},    // 0 → 1
        {2, 3}, // 1 → 2, 3
        {},     // 2
        {0}     // 3 → 0
    };

    std::cout << (EylerRoute(G) ? "Есть эйлеров путь\n" : "Нет эйлерова пути\n");
}



//Задание 18
/*
Модифицируйте алгоритм Дейкстры для решения задачи:
В городе есть N площадей, соединенных M дорогами. 
Известна длина каждой дороги и номера площадей ai, bi(1≤ai,bi≤N), соединенных этой дорогой. 
Посчитайте количество способов добраться с площади A до площади B так, чтобы пройденный путь был минимален.
*/

/*
#include <iostream>
#include <vector>
#include <set>
#include <iomanip>
using namespace std;

const double oo = 1e10;

void Dijkstra( 
    const vector<vector<pair<int, double>>>& G, // граф в виде списка смежности
    int s, // стартовая вершина A
    vector<double>& d, // расстояния от A
    vector<int>& to, // предки (для восстановления пути) 
    vector<int>& cnt // количество кратчайших путей
)
{
    int n = G.size();
    d.assign(n, oo);      // минимальное расстояние
    cnt.assign(n, 0);     // количество путей
    to.assign(n, -1);     // родительские вершины (необязательно)

    d[s] = 0;
    cnt[s] = 1; // до себя — один способ

    set<pair<double, int>> q;
    q.insert({ d[s], s });

    while (!q.empty()) {
        auto it = q.begin();
        int v = it->second;
        q.erase(it);

        for (auto [u, w] : G[v]) {
            if (d[v] + w < d[u]) {
                // улучшили расстояние — пересчёт
                q.erase({ d[u], u });
                d[u] = d[v] + w;
                cnt[u] = cnt[v];
                to[u] = v;
                q.insert({ d[u], u });
            }
            else if (d[v] + w == d[u]) {
                // ещё один путь той же длины
                cnt[u] += cnt[v];
            }
        }
    }
}

int main() {
    std::setlocale(LC_ALL, "Rus");
    int N = 6;
    vector<vector<pair<int, double>>> G(N);

    // Пример графа:
    // 0 --1-- 1 --1-- 2
    //  |              |
    //  2              1
    //  |              |
    //  3 --1-- 4 --1-- 5

    G[0].push_back({ 1, 1 });
    G[1].push_back({ 0, 1 });
    G[1].push_back({ 2, 1 });
    G[2].push_back({ 1, 1 });
    G[0].push_back({ 3, 2 });
    G[3].push_back({ 0, 2 });
    G[3].push_back({ 4, 1 });
    G[4].push_back({ 3, 1 });
    G[4].push_back({ 5, 1 });
    G[5].push_back({ 4, 1 });
    G[2].push_back({ 5, 1 });
    G[5].push_back({ 2, 1 });

    int A = 0, B = 5;
    vector<double> d;
    vector<int> to, cnt;

    Dijkstra(G, A, d, to, cnt);

    // Табличный вывод
    cout << left << setw(10) << "Вершина" << setw(20) << "Мин. расстояние"
        << setw(20) << "Кол-во путей" << "Родитель\n";
    cout << string(60, '-') << "\n";

    for (int i = 0; i < N; ++i) {
        cout << left << setw(10) << i
            << setw(20) << d[i]
            << setw(20) << cnt[i]
            << to[i] << '\n';
    }

    cout << "\nМинимальное расстояние от " << A << " до " << B << " = " << d[B] << '\n';
    cout << "Количество кратчайших путей = " << cnt[B] << '\n';

    return 0;
}
*/

//Задание 19
/*
Напишите функцию для получения K-го в порядке возрастания числа из двоичного файла, содержащего N (N>10^9) 64-битных беззнаковых целых чисел. 
Функции передается имя файла с числами и K. 
Можно считывать файл несколько раз. 
В памяти можно хранить не более 66000 64-битных чисел. Оцените эффективность вашего алгоритма.
*/
/*
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint> //Целочисленный тип с определенным разме
#include <limits>
#include <string>

const size_t size = 66000;

uint64_t find_kth_smallest(const std::string& filename, uint64_t K) {
    std::vector<uint64_t> buffer(size); //Память
    uint64_t left = 0; //Нижняя граница
    uint64_t right = std::numeric_limits<uint64_t>::max(); //Верхняя граница

    while (left < right) {
        uint64_t mid = left + (right - left) / 2;

        std::ifstream file(filename, std::ios::binary);
        if (!file) throw std::runtime_error("Не удалось открыть файл!");

        uint64_t count = 0;

        while (file.read(reinterpret_cast<char*>(buffer.data()), size * sizeof(uint64_t)) || file.gcount() > 0) {
            size_t read_count = file.gcount() / sizeof(uint64_t);
            for (size_t i = 0; i < read_count; ++i) {
                if (buffer[i] <= mid) {
                    ++count;
                }
            }
        }

        if (count < K) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    return left;
}*/

//Задание 20
/*
Сравните время сортировки с помощью sort, stable_sort, multiset для последовательности из 10^6 чисел от 1 до N и от N до 1. 
 Результаты оформить в виде таблицы.
*/
/*
#include <chrono>
#include <vector>
#include <set>

void testsorting(const std::vector<int>& v) {
    using Time = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using Diff = std::chrono::milliseconds;
    
    //1
    std::vector<int> v_sort = v;
    Time start1 = std::chrono::high_resolution_clock::now();
    sort(v_sort.begin(), v_sort.end());
    Time end1 = std::chrono::high_resolution_clock::now();
    Diff diff1 = std::chrono::duration_cast<Diff>(end1 - start1);

    std::cout << "Для метода .sort в милисекундах: " << diff1.count() << '\n';

    //2
    std::vector<int> v_table = v;
    Time start2 = std::chrono::high_resolution_clock::now();
    stable_sort(v_table.begin(), v_table.end());
    Time end2 = std::chrono::high_resolution_clock::now();
    Diff diff2 = std::chrono::duration_cast<Diff>(end2 - start2);

    std::cout << "Для метода .stable_sort в милисекундах: " << diff2.count() << '\n';

    //3
    std::multiset<int> ms;
    Time start3 = std::chrono::high_resolution_clock::now();
    for (int elem : v) ms.insert(elem);
    Time end3 = std::chrono::high_resolution_clock::now();
    Diff diff3 = std::chrono::duration_cast<Diff>(end3 - start3);

    std::cout << "Для метода .multiset в милисекундах: " << diff3.count() << '\n';
}

int main() {
    std::setlocale(LC_ALL,"Rus");
    const int num = 1000000;

    std::vector<int> v1; //В прямом порядке
    std::vector<int> v2; //В обратном порядке

    for (int i = 0; i < num; i++) {
        v1.push_back(i);
    }
    for (int i = num; i != 0; i--) {
        v2.push_back(i);
    }

    testsorting(v1);
    testsorting(v2);
}*/

//Задание 21
/*
Напишите функцию поиска подстроки турбо-методом Бойера-Мура. 
Сравните время работы вашей функции с методом find и алгоритмом search с использованием boyer_moore_searcher из <functional> для текста размером 10^6 
    символов и шаблона 10^4 символов.
Результаты представить в виде таблицы. 
Строки: 3 указанных алгоритма (Для алгоритма Бойер-Мура указать время, включая создание boyer_moore_searcher, и отдельно, исключая). 
Столбцы: 1) для случайного текста и шаблона; 2) текст 00...00, шаблон 00...01; 3) текст 00...00, шаблон 10...00.
*/

/*
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>
#include <functional>
#include <algorithm>

const int ASIZE = 256; // размер алфавита (например, ASCII)

void preBmBc(const std::string& x, std::vector<int>& bmBc) {
    int m = x.size();
    bmBc.assign(ASIZE, m);
    for (int i = 0; i < m - 1; ++i)
        bmBc[static_cast<unsigned char>(x[i])] = m - i - 1;
}

void suffixes(const std::string& x, std::vector<int>& suff) {
    int m = x.size();
    suff.resize(m);
    suff[m - 1] = m;
    int g = m - 1;
    int f = 0;
    for (int i = m - 2; i >= 0; --i) {
        if (i > g && suff[i + m - 1 - f] < i - g)
            suff[i] = suff[i + m - 1 - f];
        else {
            if (i < g) g = i;
            f = i;
            while (g >= 0 && x[g] == x[g + m - 1 - f])
                --g;
            suff[i] = f - g;
        }
    }
}

void preBmGs(const std::string& x, std::vector<int>& bmGs) {
    int m = x.size();
    std::vector<int> suff;
    suffixes(x, suff);
    bmGs.assign(m, m);
    int j = 0;
    for (int i = m - 1; i >= 0; --i) {
        if (suff[i] == i + 1) {
            for (; j < m - 1 - i; ++j) {
                if (bmGs[j] == m)
                    bmGs[j] = m - 1 - i;
            }
        }
    }
    for (int i = 0; i <= m - 2; ++i)
        bmGs[m - 1 - suff[i]] = m - 1 - i;
}

std::string turbo_boyer_moore(const std::string& pattern, const std::string& text) {
    std::string result;
    int m = pattern.size();
    int n = text.size();

    if (m == 0 || n < m) return result;

    std::vector<int> bmGs, bmBc;
    preBmGs(pattern, bmGs);
    preBmBc(pattern, bmBc);

    int j = 0, u = 0, shift = m;
    while (j <= n - m) {
        int i = m - 1;
        while (i >= 0 && pattern[i] == text[i + j]) {
            --i;
            if (u != 0 && i == m - 1 - shift)
                i -= u;
        }
        if (i < 0) {
            result.push_back(j);  // OUTPUT(j)
            shift = bmGs[0];
            u = m - shift;
        }
        else {
            int v = m - 1 - i;
            int turboShift = u - v;
            int bcShift = bmBc[static_cast<unsigned char>(text[i + j])] - m + 1 + i;
            shift = std::max({ turboShift, bcShift, bmGs[i] });
            if (shift == bmGs[i]) {
                u = std::min(m - shift, v);
            }
            else {
                if (turboShift < bcShift)
                    shift = std::max(shift, u + 1);
                u = 0;
            }
        }
        j += shift;
    }
    return result;
}

std::vector<double> m(0);

void testSearching(std::string& text, std::string& pattern) {
    using Clock = std::chrono::high_resolution_clock;

    //1 Сравнение функции Турбо-Бойера-Мура с методом find
    auto start1 = Clock::now();
    std::string v_TBM = turbo_boyer_moore(pattern, text);
    auto end1 = Clock::now();
    std::chrono::duration<double> diff1 = end1 - start1;
    std::cout << std::fixed << std::setprecision(10);
    //std::cout << "Метод turbo_boyer_moore: " << diff1.count() << " секунд\n";
    m.push_back(diff1.count());

    //find
    auto start2 = Clock::now();
    auto pos2 = text.find(pattern);
    auto end2 = Clock::now();
    std::chrono::duration<double> diff2 = end2 - start2;
    //std::cout << "Метод find: " << diff2.count() << " секунд\n";
    m.push_back(diff2.count());

    //2 Сравнеие функции Турбо-Бойера-Мура с использованием boyer_moore_searcher из <functional> 
    // С созданием: boyer_moore_searcher из <functional>
    auto start3 = Clock::now();
    auto searcher1 = std::boyer_moore_searcher(pattern.begin(), pattern.end());
    auto result1 = std::search(text.begin(), text.end(), searcher1);
    auto end3 = Clock::now();
    std::chrono::duration<double> diff3 = end3 - start3;
    //std::cout << "Создание метода и поиск: " << diff3.count() << " секунд\n";
    m.push_back(diff3.count());

    //#2.1 - Время работы
    auto searcher2 = std::boyer_moore_searcher(pattern.begin(), pattern.end());
    
    auto start3_1 = Clock::now();
    auto result2 = std::search(text.begin(), text.end(), searcher2);
    auto end3_1 = Clock::now();
    std::chrono::duration<double> diff3_1 = end3_1 - start3_1;
    //std::cout << "Метод boyer_moore_searcher работа поиска: " << diff3_1.count() << " секунд\n";
    m.push_back(diff3_1.count());
}

int main() {
    std::setlocale(LC_ALL, "Rus");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0,1);
    const int num1 = 1000000;
    const int num2 = 10000;
    std::string v1(num1,0); // 00...00 - исходный текст
    std::string v2; // 00...01 - шаблон
    std::string v3; // 10...00 - шаблон
    std::string v4; // случайный набор цифр из 0 и 1 - исходный текст
    std::string v5; // случайный набор цифр из 0 и 1 - шаблон

    for (int i = 0; i < num2; i++) {
        if (i == num2 - 1) v2.push_back(1);
        v2.push_back(0);
    }
    for (int i = 0; i < num2; i++) {
        if (i == 0) v3.push_back(1);
        v3.push_back(0);
    }

    for (int i = 0; i < num1; i++) v4.push_back(dis(gen));
    for (int i = 0; i < num2; i++) v5.push_back(dis(gen)); 
    //std::cout << "Текст: случайный набор цифр из 0 и 1, шаблон: случайный набор цифр из 0 и 1" << '\n';    
    testSearching(v4, v5); // текст:случайный набор цифр из 0 и 1, шаблон:случайный набор цифр из 0 и 1
    //std::cout << "Текст: 00...00, Шаблон: 00...01" << '\n';
    testSearching(v1,v2); // текст:00..00, шаблон:00...01
    //std::cout << "Текст: 00...00, шаблон: 10...00" << '\n';
    testSearching(v1,v3); // текст:00..00, шаблон:10...00 

    std::cout << '\n'; 
    std::cout << std::setw(45) << "Случайный набор цифр" << std::setw(35) << "Текст:00...00 Шаблон:00...01" << std::setw(35) << "Текст:00...00 Шаблон:10...00" << '\n';
    std::cout << "turbo_boyer_moore" << std::setw(25) << m.at(0) << std::setw(30) << m.at(4) << std::setw(30) << m.at(8) << '\n';
    std::cout << "find" << std::setw(38) << m.at(1) << std::setw(30) << m.at(5) << std::setw(30) << m.at(9) << '\n';
    std::cout << "Полный boyer_moore_searcher" << std::setw(15) << m.at(2) << std::setw(30) << m.at(6) << std::setw(30) << m.at(10) << '\n';
    std::cout << "Поиск boyer_moore_searcher" << std::setw(16) << m.at(3) << std::setw(30) << m.at(7) << std::setw(30) << m.at(11) << '\n';
}*/

//Задание 22 - сделано храниться на бумаге
/*
Постройте сжатое суффиксное дерево для строки "shesellsseashells" и найдите количеcтво различных подстрок в этой строке. 
Объясните способ подсчета с использованием суффиксного дерева
*/

//Задание 23
/*
Определите необходимые геометрические объекты и напишите следующую функцию
В декартовой системе координат на плоскости заданы две окружности. Найдите все касательные к этим окружностям (их может быть до 4).
Для точки использовать класс из лекций и его методы.
*/

/*
struct Point {
    double x, y;
    double len() const { return hypot(x, y); } // расстояние от начала координат
    double phi() const { return atan2(y, x); } // угол
    Point operator+(Point p) const { return { x + p.x,y + p.y }; }
    Point operator-(Point p) const { return { x - p.x,y - p.y }; }
    double operator*(Point p) const { return x * p.x + y * p.y; } // скалярное произведение
    double operator^(Point p) const { return x * p.y - y * p.x; } // векторное произведение
    Point operator*(double a) const { return  { a * x,a * y }; } // "масштабирование"
    Point turn(double a) const { double ca = cos(a), sa = sin(a); return { x * ca - y * sa,-x * sa + y * ca }; } // поворот
    Point turn() const { return { -y,x }; } // поворот на п/2 
    Point operator-() const { return { -x,-y }; } // поворот на п
};
inline Point operator*(double a, Point p) { return p * a; } // "масштабирование"

struct Circle {
    Point position;
    double radius;
};
*/


//Задание 25
/*
Напишите функцию разложения числа на простые множители.
*/

//Алгоритм решето-Эратосфена
/*
std::vector<int> func2(int x) {
    std::vector<int> my_list(0);
    if (x < 2) return my_list;  // Простых чисел нет

    std::vector<bool> m(x+1, true);
    m[0] = m[1] = false;
    for (int i = 2; i <= x; i++) {
        if (m[i] == true) {
            for (int j = i * i; j <= x; j+=i) {
                m[j] = false;
            }
        }
    }
    // Разложение на простые множители
    for (int i = 2; i <= x; ++i) {
        if (m[i] && x % i == 0) {
            while (x % i == 0) {
                my_list.push_back(i);
                x /= i;
            }
        }
    }
    return my_list;
}
int main() {
    for (int temp : func2(20)) {
        std::cout << temp << ' ';
    }
    return 0;
}
*/
/*
std::vector<int> func2(int num) {
    std::vector<int> my_list(0);
    int n = num;
    for (int i = 2; i <= sqrt(n); i++) {
        while (n % i == 0) {
            n = n / i;
            my_list.push_back(i);
        }
    }
    my_list.push_back(n);
    return my_list;
}

int main() {
    for (int temp : func2(20)) {
        std::cout << temp << ' ';
    }
    return 0;
}
*/
