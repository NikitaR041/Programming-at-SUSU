#include <iostream>
/*
Задание 4 | Шаблоны, исключительные ситуации | Романов Никита ЕТ-212 
Вариант 21      
*/

//Исключительные структуры
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

//Реализуем шаблонный класс вектор для любых типов данных
//deque - циклический массив
template <typename T>
class Deque{
   T *m; //Указатель на очередь
   int lenght; //Текущее количество элементов в двусторонней очереди
   int capasity; //Максимальный размер двусторонней очереди
   int left; //Индекс начала
   int right; //Индекс конца
public:
   //Конструктор
   Deque(int capasity) : lenght(0), capasity(capasity), left(0), right(-1), m(new T[capasity]) {}
   //Конструктор копий
   Deque (const Deque<T>&);
   //Деструктор
   ~Deque() {delete []m; } 
   
   void pushLeft(const T&); //Добавление элемента в начале двусторонней очереди
   void pushRight(const T&); //Добавление элемента в конец двусторонней очереди
   T popLeft(); //Извелечение с начала двусторонней очереди
   T popRight(); //Извлечение с конца двусторонней очереди
   
   Deque<T>& operator=(const Deque<T>&); //Оператор присваивания
   
   void printDeque() const; //Получение элеметов
};

//Реализация методов и операторов
//Определение конструктора копий
template <typename T>
Deque<T>::Deque(const Deque<T>& other) : lenght(other.lenght), capasity(other.capasity), left(other.left), right(other.right), m(new T[other.capasity]) {
   std::cout << "Конструктор копий заработал!" << '\n';
   for(int i = 0; i < lenght; i++){
      m[i] = other.m[i];
   }
}

//Переопределение оператора присваивания  (Например, obj1 = obj2, где obj1 и obj2 - оба объекта класса Deque)
template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& other){
   if (this == &other) return *this;
   try {
      if (capasity <= other.lenght) {
         throw DequeFull();
      }

      lenght = other.lenght;
      capasity = other.capasity;
      left = other.left;
      right = other.right;

      delete[] m;
      m = new T[capasity];

      for (int i = 0; i < lenght; i++) {
         m[i] = other.m[i];
      }
    } catch (DequeFull& e) {
        std::cout << "Ошибка при присваивании: " << e.what() << '\n';
    }
   return *this;
}

template <typename T>
void Deque<T>::pushLeft(const T& val) {
   if (lenght == capasity) throw DequeFull();
   left = (left - 1 + capasity) % capasity;
   m[left] = val;
   lenght++;
}

template <typename T>
void Deque<T>::pushRight(const T& val){
   if(lenght == capasity) throw DequeFull();
   right = (right + 1) % capasity;
   m[right] = val;
   lenght++;
}

template <typename T>
T Deque<T>::popLeft(){
   if(lenght == 0) throw DequeEmpty();
   T val = m[left];
   left = (left + 1) % capasity;
   lenght--;
   return val;
}

template <typename T>
T Deque<T>::popRight(){
   if(lenght == 0) throw DequeEmpty();
   T val = m[right];
   right = (right - 1 + capasity) % capasity;
   lenght--;
   return val;
}

template <typename T>
void Deque<T>::printDeque() const {
   for (int i = 0; i < lenght; i++) {
      std::cout << m[(left + i) % capasity] << " ";
   }
   std::cout << std::endl;
}

int main() {
   // Инициализация дек с размером 3
   Deque<int> obj(3);
   std::cout << "\nТест 1. Добавление элементов при помощи методов pushLeft и pushRight" << '\n';
   try {
      // Добавляем элементы с левой и правой стороны
      obj.pushLeft(4);
      obj.pushLeft(10);
      obj.pushRight(2);
      obj.pushLeft(5);  // Попытка добавить элемент при полном деке
      obj.pushRight(6); // Попытка добавить элемент при полном деке
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n';  // Ошибка переполнения
   }
   
   std::cout << "Элементы в двустороннем очереди" << '\n';
   obj.printDeque();
   
   // Вывод состояния дека после добавления элементов
   std::cout << "\nТест 2. Удаление элементов при помощи методов popLeft и popRight" << '\n';
   try {
      std::cout << "Удаление элемента слева: " << obj.popLeft() << '\n';  // Удаляем с левой стороны
      std::cout << "Удаление элемента справа: " << obj.popRight() << '\n'; // Удаляем с правой стороны
      std::cout << "Удаление элемента слева: " << obj.popLeft() << '\n';  // Удаляем с левой стороны
      std::cout << "Удаление элемента справа: " << obj.popRight() << '\n'; // Попытка удалить из пустого деки
   } catch (DequeEmpty& e) {
      std::cout << e.what() << '\n';  // Ошибка пустого дека
   }
   
   std::cout << "Элементы в двустороннем очереди" << '\n';
   obj.printDeque(); //Вывод пустого
   
   std::cout << "\nТест 3. Конструктор копий" << '\n';
   Deque<int> copyObj = obj; //Должен быть вывод сообщения из конструктора копий
   try {
      copyObj.pushLeft(7);
      copyObj.pushRight(3);
      std::cout << "Копия дек: " << copyObj.popLeft() << ", " << copyObj.popRight() << '\n';
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n'; 
   }
   
   // Тест 4. Оператор присваивания
   std::cout << "\nТест 4. Оператор присваивания" << '\n';
   Deque<int> assignObj(3);
   assignObj.pushLeft(10);
   assignObj.pushRight(20);
   Deque<int> assignedObj(2);  // Дек с меньшим размером для проверки
   assignedObj = assignObj;  // Использование оператора присваивания
   try {
      std::cout << "После присваивания: " << assignedObj.popLeft() << ", " << assignedObj.popRight() << '\n';
   } catch (DequeEmpty& e) {
      std::cout << e.what() << '\n';
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n';
   }
   
   return 0;
}


