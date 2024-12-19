#include <iostream>
/*
Задание 4 | Шаблоны, исключительные ситуации | Романов Никита ЕТ-212 
Вариант 21      
*/

struct DequeError : public std::exception{ // Базовый класс для ошибок
   virtual ~DequeError() {}; //Деструктор
   virtual const char *what() const noexcept =0; //Сообщение для печати
};

struct DequeFull : DequeError {
   const char *what() const  noexcept override { return "Ошибка: Двусторонняя очередь переполнилась!"; } //Сообщение для печати
};

struct DequeEmpty : DequeError {
   const char *what() const noexcept override {return "Ошибка: Двусторонняя очередь пуста!"; } //Сообщение для печати
};

template <typename T>
class Deque{
   T* m; //Указатель на массив константной длины
   int size; //Размер массива
   int head; //Индекс головы дека
   int tail; //Индекс хвоста дека 
public:
   Deque(int size) : size(size), head(0), tail(0), m(new T[size]) { } //Конструктор
   Deque(const Deque<T>&); //Конструктор копий
   ~Deque() { delete []m; } //Деструктор
   
   bool empty(); //Проверка на наличие элементов
   void pushBack(const T&); //Операция вставки элемента в конец дека
   void pushFront(const T&); //Операция вставки элемента в начало дека 
   T popBack(); //Операция изъятия конечного элемента
   T popFront(); //Операция изъятия начального элемента
   
   Deque<T>& operator=(const Deque<T>&); //Перегрузка оператора присваивания
   
   void printDeque() const; //Операция просмотра элементов
};

//Определение конструктора копий
template <typename T>
Deque<T>::Deque(const Deque<T>& other) : size(other.size), head(other.head), tail(other.tail), m(new T[other.size]) {
   for(int i = 0; i < size; i++){
      m[i] = other.m[i];
   }
}

//Проверка на наличие элементов
template <typename T>
bool Deque<T>::empty() {
    return head == tail;
}

//Операция вставки элемента в конец дека
template <typename T>
void Deque<T>::pushBack(const T& value){
   if(head == (tail + 1) % size){
      throw DequeFull();
   }
   m[tail] = value;
   tail = (tail + 1) % size;
}

//Операция изъятия конечного элемента
template <typename T>
T Deque<T>::popBack(){
   if(empty()) {
      throw DequeEmpty();
   }
   tail = (tail - 1 + size) % size;
   return m[tail];
}       

//Операция вставки элемента в начало дека 
template <typename T>
void Deque<T>::pushFront(const T& value){
   if(head == (tail + 1) % size){
      throw DequeFull();
   }
   head = (head - 1 + size) % size;
   m[head] = value;
}

//Операция изъятия начального элемента
template <typename T>
T Deque<T>::popFront(){
   if(empty()){
      throw DequeEmpty();
   }
   head = (head + 1) % size;
   return m[head];
}

//Перегрузка оператор присваивания
//Случай, когда перевыделения памяти не происходит
template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& other){
  if(size != other.size){
      throw DequeFull();
   } 
   
   for (int i = 0; i < size; ++i){
      m[i] = other.m[i];
   }
   return *this;
}

//Операция просмотра элементов
template <typename T>
void Deque<T>::printDeque() const {
   for (int i = 0; i < size; i++) {
      std::cout << m[i] << ' ';
   }
   std::cout << std::endl;
}

int main() {
   Deque<int> obj(3);
   std::cout << "\nТест 1. Добавление элементов при помощи методов pushFront и pushBack" << '\n';
   try {
      // Добавляем элементы с левой и правой стороны
      obj.pushFront(4);
      obj.pushFront(10);
      obj.pushBack(2);
      obj.pushFront(5);  // Попытка добавить элемент при полном деке
      obj.pushBack(6); // Попытка добавить элемент при полном деке
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n';  // Ошибка переполнения
   }
   
   std::cout << "Элементы в двустороннем очереди" << '\n';
   obj.printDeque();
   
   // Вывод состояния дека после добавления элементов
   std::cout << "\nТест 2. Удаление элементов при помощи методов popFront и popBack" << '\n';
   try {
      std::cout << "Удаление элемента слева: " << obj.popFront() << '\n';  // Удаляем с левой стороны
      std::cout << "Удаление элемента справа: " << obj.popBack() << '\n'; // Удаляем с правой стороны
      std::cout << "Удаление элемента слева: " << obj.popFront() << '\n';  // Удаляем с левой стороны
      std::cout << "Удаление элемента справа: " << obj.popBack() << '\n'; // Попытка удалить из пустого деки
   } catch (DequeEmpty& e) {
      std::cout << e.what() << '\n';  // Ошибка пустого дека
   }
   
   std::cout << "Элементы в двустороннем очереди" << '\n';
   obj.printDeque(); //Вывод пустого
   
   std::cout << "\nТест 3. Конструктор копий" << '\n';
   try {
      Deque<int> copyObj = obj; //Конструктора копий
      copyObj.pushFront(7);
      copyObj.pushBack(3);
      std::cout << "Копия дек: " << copyObj.popFront() << ", " << copyObj.popBack() << '\n';
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n'; 
   }
   
   // Тест 4. Оператор присваивания
   std::cout << "\nТест 4. Оператор присваивания" << '\n';
   try {
      Deque<int> assignObj(3);
      assignObj.pushFront(10);
      assignObj.pushBack(20);
      Deque<int> assignedObj(2);  // Дек с меньшим размером для проверки
      assignedObj = assignObj;  // Использование оператора присваивания
      
      std::cout << "Элементы у объекта assignedObj:" << '\n';
      assignedObj.printDeque();
   } catch (DequeEmpty& e) {
      std::cout << e.what() << '\n';
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n';
   }
   
   return 0;
}
