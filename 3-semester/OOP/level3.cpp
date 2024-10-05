#include <iostream>
#include <algorithm>
/*
Лабораторная работа 3 | Перегрузки функций и шаблоны

*/

class Rect{
   int l, t, r ,b; // Целые координаты прямоугольника
   public:
      //Конструктор
      Rect(int l = 0, int t = 0, int r = 0, int b = 0) : l(l), t(t), r(r), b(b) {};  
      //Методы для получения значений сторон
      int getLeft() {return l;} //Координата l - левая сторона
      int getTop() {return t;} //Координата t - верхняя сторона
      int getRight() {return r;} //Координата r - правая сторона
      int getBottom() {return b;} //Координата b - нижняя сторона
      
      //Перегрузка операторов
      Rect operator+(const Rect&); //Перегрузка оператора объединения +
      Rect operator*(const Rect&); //Перегрузка оператора пересечения *
      Rect& operator+=(const Rect&); //Перегузка оператора += для объединения
      Rect& operator*=(const Rect&); //Перегрузка оператора *= для пересечения 
      bool operator!() const; //Перегрузка оператора ! - проверка на пустоту
      
      //Перегрузки операторов сравнения
      friend bool operator==(const Rect&, const Rect&); //Перегрузка оператора ==
      friend bool operator!=(const Rect&, const Rect&); //Перегрузка оператора !=
      friend bool operator<=(const Rect&, const Rect&); //Перегрузка оператора <=
      friend bool operator>=(const Rect&, const Rect&); //Перегрузка оператора >=
      
      //Операторы ввода и вывода
      friend std::ostream& operator<<(std::ostream&, const Rect&); //Перегрузка оператора <<
      friend std::istream& operator>>(std::istream&, Rect&); //Перегрузка оператора >>
};

//Перегрузка оператора + для объекта Rect - объединение
Rect Rect::operator+(const Rect& other){
      Rect temp;
      temp.l = std::min(this->l, other.l);
      temp.t = std::min(this->t, other.t);
      temp.r = std::max(this->r, other.r);
      temp.b = std::max(this->b, other.b);
      return temp;
}

//Перегразка оператора * для объекта Rect - пересечение
Rect Rect::operator*(const Rect& other){
      //Мы должны проверить на пересечение двух прямоугольников
      int x1, y1, x2, y2;
      x1 = std::max(this->l, other.l);
      y1 = std::max(this->t, other.t);
      x2 = std::min(this->r, other.r);
      y2 = std::min(this->b, other.b);
   
      if(x1 > x2 || y1 > y2){
         std::cout << "Нет пересечений, возвращено пустой объект: " << '\n';
         return Rect(); //Возвращаем пустой, так как ошибка пересечения
      }

      return Rect(x1, y1, x2, y2); 
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
//Перегрузка оператора ! (проверка на пустоту)
bool Rect::operator!() const {
    return (l >= r || t >= b);
}
//Перегрузка оператора ==
inline bool operator==(const Rect& other1, const Rect& other2){
      return other1.l == other2.l && other1.t == other2.t && other1.r == other2.r && other1.b == other2.b;
}

//Перегрузка оператора !=
inline bool operator!=(const Rect& other1, const Rect& other2){
      return !(other1.l == other2.l && other1.t == other2.t && other1.r == other2.r && other1.b == other2.b);
}

//Перегрузка оператора <=  - первый объект полностью лежит во втором объекте
inline bool operator<=(const Rect& other1, const Rect& other2){
      return other1.l >= other2.l && other1.t >= other2.t && other1.r <= other2.r && other1.b <= other2.b;
}

//Перегрузка оператора >= - второй объект полностью лежит в первом объекте
inline bool operator>=(const Rect& other1, const Rect& other2){
   return other1.l <= other2.l && other1.t <= other2.t && other1.r >= other2.r && other1.b >= other2.b;
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
   //Создаем несколько объектов класса Rect
   Rect a = {1, 2, 3, 4}; //Объект, который сразу проинициализирован
   Rect b, c;
   Rect answer;  //Этот объект для перегруженного оператора !
   
   //Тестируем ввод и вывод
   std::cout << "Пожалуйста введите аргументы для следующих объектов в формате со скобками [a b c d]." << '\n';
   std::cin >> b; //Примеры ввода для b: [1 2 3 4], [0 0 5 5], [1 1 5 5], [1 1 4 4], [0 0 2 2], [1 1 5 5]
   std::cin >> c; //Примеры ввода для b: [1 2 3 4],  [1 1 3 3], [2 2 6 6],  [2 2 5 5], [3 3 5 5], [2 2 6 6]
   std::cout << "Вот ваши объекты: " << a << ' ' << b << ' ' << c << '\n';
   
   std::cout << '\n';
   
   //Тестируем методы на получение координат определенного объекта
   std::cout << "Координата L у объекта b: " << b.getLeft() << '\n';
   std::cout << "Координата T у объекта b: " << b.getTop() << '\n';
   std::cout << "Координата R у объекта b: " << b.getRight() << '\n';
   std::cout << "Координата B у объекта b: " << b.getBottom() << '\n';
   
   std::cout << '\n';
   
   //Тестируем методы на объединение и пересечение двух объектов
   std::cout << "Объединение двух объектов a + b: " << a + b << '\n';
   std::cout << "Пересечение двух объектов b * c: " << b * c << '\n';
   std::cout << "Объединение двух объектов b + c: " << b + c<< '\n';
   
   
   std::cout << '\n';
   
   //Тестируем перегруженные операторы += и *=
   a+=b;
   std::cout << "Пример работы оператора += двух объектов a и b: " << a << '\n';
   b*=c;
   std::cout << "Пример работы оператора *= двух объектов b и с: " << b << '\n';
   b+=c;
   std::cout << "Пример работы оператора += двух объектов b и c: " << a << '\n';
   
   std::cout << '\n';
   
   //Тестируем перегруженные оператор !
   answer = b * c; //К примеру, можно посмотреть, что объект будет принимать [0 0 0 0] или [5, 5, 3, 3]
   if(!answer) std::cout << "Да, объект answer пустой!" << '\n';
   else std::cout << "Нет, объект не пустой!" << '\n';
   
   std::cout << '\n';
   
   //Тестируем перегруженные операторы ==, !=, <=, >=
   if(b<=c){
      std::cout<< "Объект b <= c" << '\n';
   }else if(b >= c){
      std::cout << "Объект b >= c" << '\n';
   }
   
   if(a == b){
      std::cout<< "Объекты a и b равны!" << '\n';
   }else if (a != b){
      std::cout<< "Объекты a и b не равны!" << '\n';
   }
   
   std::cout << '\n';
   return 0;
}