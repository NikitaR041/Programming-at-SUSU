#include <iostream>
#include <algorithm>
#include <utility>
using namespace std::rel_ops;

/*
Лабораторная работа 3 | Перегрузки функций и шаблоны | варант 21
*/

class Rect{
   int l, t, r, b; // Целые координаты прямоугольника
   //Где l и t - это левая верхняя точка (l, t); где r и t - это правая нижняя точка (r,t).
   public:
      //Конструктор
      Rect(int l = 0, int t = 0, int r = 0, int b = 0) : l(l), t(t), r(r), b(b) {};  
      //Методы для получения значений сторон
      int getLeft() const {return l;} //Координата l - левая сторона
      int getTop() const {return t;} //Координата t - верхняя сторона
      int getRight() const {return r;} //Координата r - правая сторона
      int getBottom() const {return b;} //Координата b - нижняя сторона
      
      //Перегрузка операторов
      Rect& operator+=(const Rect&); //Перегузка оператора += для объединения
      Rect& operator*=(const Rect&); //Перегрузка оператора *= для пересечения 
      bool operator!() const; //Перегрузка оператора ! - проверка на пустоту
      
      friend bool operator==(const Rect&, const Rect&);
      friend bool operator<(const Rect&, const Rect&);
      
      friend std::ostream& operator<<(std::ostream&, const Rect&); //Перегрузка оператора <<
      friend std::istream& operator>>(std::istream&, Rect&); //Перегрузка оператора >>
};

//Перегрузка оператора + для объекта Rect - объединение
//Первый параметр передается по значению
inline Rect operator+(Rect x, const Rect& other){
      return x += other;
}

//Перегразка оператора * для объекта Rect - пересечение
//Первый параметр передается по значению
inline Rect operator*(Rect x, const Rect& other) {
      return x *= other;
}

//Перегрузка оператора +=  для объекта Rect - объединение текущего объекта
Rect& Rect::operator+=(const Rect& other){
      this->l = std::min(this->l, other.l);
      this->t = std::min(this->t, other.t);
      this->r = std::max(this->r, other.r);
      this->b = std::max(this->b, other.b);
      return *this;
}

//Перегразка оператора *=  для объекта Rect - изменение текущего объекта
Rect& Rect::operator*=(const Rect& other){
      //Мы должны проверить на пересечение двух прямоугольников
      this->l = std::max(this->l, other.l);
      this->t = std::max(this->t, other.t);
      this->r = std::min(this->r, other.r);
      this->b = std::min(this->b, other.b);
   
      if(this->l > this->r || this->t > this->b){
         std::cout << "Нет пересечений, возвращено пустой объект: " << '\n';
         return *this = Rect(); //Обнуляем текущий объект, так как ошибка
      }

      return *this; 
}
//Перегрузка оператора ! (проверка на пустоту нового объекта после пересечения двух объектов)
bool Rect::operator!() const {
    return (l >= r || t >= b);
}
//Перегрузка оператора ==
inline bool operator==(const Rect& other1, const Rect& other2){
      return other1.l == other2.l && other1.t == other2.t && other1.r == other2.r && other1.b == other2.b;
}
//Перегрузка оператора !=
inline bool operator!=(const Rect& other1, const Rect& other2){
      return !(other1==other2);
}

// Перегрузка оператора < для класса Rect
inline bool operator<(const Rect& other1, const Rect& other2) {
    // Пример логики: один прямоугольник меньше другого, если его левая верхняя точка "меньше", а правая нижняя точка "меньше"
    return (other1.l < other2.l) && (other1.t < other2.t) && (other1.r < other2.r) && (other1.b < other2.b);
}

//Перегрузка оператора >= - второй объект полностью лежит в первом объекте
inline bool operator>=(const Rect& other1, const Rect& other2){
      return !(other1<other2);
}
//Перегрузка оператора <=  - первый объект полностью лежит во втором объекте
inline bool operator<=(const Rect& other1, const Rect& other2){
      return !(other2<other1);
}

//Перегрузка оператора << потоковый вывод
std::ostream &operator<<(std::ostream& out, const Rect& other){
      return out << '[' << other.l << ' ' << other.t << ' ' << other.r << ' ' << other.b << ']';
}

//Перегрузка оператора >> потоковый ввод
std::istream &operator>>(std::istream &in, Rect& other){
    char h1, h2; // Для скобок []
    in >> h1; // Читаем первую скобку
    if (h1 != '[') {
        std::cerr << "Ожидалась открывающая скобка '['" << '\n';
        return in;
    }
    
    in >> other.l >> other.t >> other.r >> other.b >> h2;
    return in;
}
int main(){
   //Создание объектов типа Rect
   Rect a(1, 1, 5, 5), b(2, 2, 6, 6);
   Rect c, d;
   
   //Тестируем ввод и вывод
   std::cout << "Пожалуйста введите аргументы для следующих объектов в формате со скобками [a b c d]." << '\n';
   std::cin >> c; 
   std::cout << "Вот ваши объекты: " << a << ' ' << b << ' ' << c << '\n' << '\n';
   
   //Тестируем методы на получение координат определенного объекта
   std::cout << "Первая точка (left,top) у объекта A " << '(' << a.getLeft() << ' ' << a.getTop() << ')' << '\n';
   std::cout << "Первая точка (right,bottom) у объекта A " << '(' << a.getRight() << ' ' << a.getBottom() << ')' << '\n' << '\n';
   
   //Тестируем методы на объединение и пересечение двух объектов
   std::cout << "Объединение a+b " << a+b << ' ' << "Пересечение b*c " << b*c << '\n' << '\n';
   
   //Проверка условии на пересечение
   d = b * c;
   if(!d){
      if(b == c) std::cout << "Объекты b и c похожи!" << '\n';
      else if(b!=c) std::cout << "Объекты b и c НЕ похожи!" << '\n';
   }else {
      if(d <= c) std::cout << "Объект d лежит в c" << '\n';
      else if(c >= b) std::cout << "Объект с лежит в b" << '\n';
      else std::cout <<"Объект C нигде не лежит" << '\n';
   }
   return 0;
}
