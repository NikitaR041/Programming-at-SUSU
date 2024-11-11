#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;
/*
Задание 3 | Романов Никита ЕТ-212 | Вариант 21
Тема: Виртуальные методы, наследования
*/

//Родительский-абстрактный класс
class Figure{
      int c; // Цвет
      bool visible; //Видимость
   protected:
      int x,y; //Базовая точка
      virtual void draw() = 0;//чисто виртуальный метод - нарисовать
   public:
      Figure(int c, int x, int y) : c(c), visible(false), x(x), y(y) {} //Конструктор
      virtual ~Figure(){} //Деструктор
      void move(int x, int y); //сместить фигуру в точку (х, у)
                                            //Видимая фигура гасится, зачет рисуется в другом месте
                                            //У невидимой просто меняются поля х,у
      void setcolor(int c);     //Установить цвет фигуры
                                          //Видимая фигура рисуется новым цветом
                                          //У невидимой просто меняется поле с 
      int getcolor() const {return c;} //Получить цвет
      void hide();      //Спрятать: нарисовать черный прямоугольник
                              //                        по размерам area()
      void show();      //Показать
      bool isvisible() const {return visible;} //Видима?
      virtual void area (int &x1, int &y1, int &x2, int &y2) const = 0; //чисто вирутальный метод
                           //получить размеры прямоугольной области, содержащей фигуру
};
//Смещение фигуру в точку (х,у)
void Figure::move(int x, int y){
   bool flag = visible;
   if (flag) hide();
   this->x = x;
   this->y= y;
   if(flag) show();
}
//Задание цвета
inline void Figure::setcolor(int c){
   this->c=c;
   if(visible) draw();
}

//Рисование черного фона
void Figure::hide(){
   if(!visible) return;
   int x1,y1,x2,y2;
   area(x1,y1,x2,y2);
   setfillstyle(SOLID_FILL,BLACK);
   bar(x1,y1,x2,y2);
   visible = false;
}

//Отображение фигуры
void Figure::show(){
   if(!visible){
      visible= true;
      draw();
   }
}

//Полукруг
class HalfCircle : public Figure{
   protected:
      int angle; //Угол поворота
      int radius; //Радиус
      void draw() override;
      void area (int &x1, int &y1, int &x2, int &y2) const override final; //Не будет дальнейшего переопределения
   public:
      HalfCircle(int c, int x, int y,  int angle,  int radius) : Figure(c, x, y), angle(angle), radius(radius){}
      ~HalfCircle() { hide(); }
      void setsizes(int angle, int radius); //Метод для изменения размеров фигуры
};

void HalfCircle::setsizes(int angle, int radius){
   bool F = isvisible();
   if(F) hide();
   this->angle = angle;
   this->radius =radius;
   if(F) show();
}

//Метод, который рисует  полукруг
void HalfCircle::draw(){
   ::setcolor(getcolor()); 
   arc(x, y, angle, angle + 180, radius);
   line(x - radius, y, x + radius, y);
}

//Получение прямоугольника
void HalfCircle::area(int &x1, int &y1, int &x2, int &y2) const {
   x1 = x - radius; // Левый край
   y1 = y - radius; // Верхний край
   x2 = x + radius; // Правый край
   y2 = y + radius; // Нижний край
}

class FillHalfCircle : public HalfCircle{
   int Fillcolor; //Сплошной цвет заливки фигуры
   void draw() override final; //Не будет дальнейшего переопределения
   public:
      FillHalfCircle(int c, int x, int y,  int angle, int radius, int Fillcolor) : HalfCircle(c, x,  y, angle, radius), Fillcolor(Fillcolor) {}
      ~FillHalfCircle(){ hide(); }
      void setFillcolor(int c); //Изменить цвет закраски
};

//Заполненый цветом полукруг
inline void FillHalfCircle::setFillcolor(int c){
   Fillcolor = c;
   if(isvisible()) draw();
}

//Нарисовать и заполнить цветом фигуру
void FillHalfCircle::draw(){
   ::setcolor(getcolor());
   setfillstyle(SOLID_FILL, Fillcolor);
   pieslice(x, y, angle, angle + 180, radius);
}


int main(){
   initwindow(800,600);
   
   Figure* obj1 = new HalfCircle(WHITE, 100, 100, 0, 100);
   Figure* obj2 = new FillHalfCircle(RED, 100, 400, 0, 100, BLUE);
   
   obj1->show();
   obj2->show();
   getch();
   obj1->hide();
   obj2->hide();
   getch();
   obj1->move(300, 150);
   obj2->move(400, 400);
   getch();
   obj1->show();
   obj2->show();
   getch();
   obj1->setcolor(RED);
   obj2->setcolor(WHITE);
   getch();
   
   // Проверяем, можно ли выполнить преобразование к производным классам
   if (HalfCircle* hc = dynamic_cast<HalfCircle*>(obj1)) {
      hc->setsizes(180, 150); // Меняем угол и радиус
      getch();
   }

   if (FillHalfCircle* fhc = dynamic_cast<FillHalfCircle*>(obj2)) {
      fhc->setsizes(180, 120); // Меняем угол и радиус
      getch();
   }
   
   if(FillHalfCircle* fhc = dynamic_cast<FillHalfCircle*>(obj2)){
      fhc->setFillcolor(MAGENTA);  // Меняем цвет заливки
      getch();
   }
   
   getch();
   delete obj1;
   delete obj2;
   getch();
   closegraph();
   return 0;
}


