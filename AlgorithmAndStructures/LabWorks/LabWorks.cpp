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
//Задание 25
/*
Напишите функцию разложения числа на простые множители.
*/
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
}*/
