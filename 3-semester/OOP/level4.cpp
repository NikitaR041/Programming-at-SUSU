#include <iostream>
#include "graphics.h"
using namespace std;
/*Задание 3 | Романов Никита ЕТ-212 | Вариант 21
Тема: Виртуальные методы, наследования
*/

//Родительский-абстрактный класс

class Figure{
      int c; // Цвет
      bool visible;
   protected:
      int x,y; //Базовая точка
      virtual void draw() = 0;//чисто виртуальный метод
   public:
      Figure(int c, int x, int y) : c(c), x(x), y(y), visible(true) {}
      virtual ~Figure(){}
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
   this->y=y;
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
   visible = 0;
}

//Отображение фигуры
void Figure::show(){
   if(!visible){
      draw();
      visible=1;
   }
}

//Полукруг
class HalfCircle : public Figure{
   protected:
      int c; //Цвет линии
      int x, y; //Центр полукруга
      int angle; //Угол поворота
      int end_angle; //Конечный угол поворота
      int radius; //Радиус
      void draw() override;
      void area (int &x1, int &y1, int &x2, int &y2) const override;
   public:
      HalfCircle(int c, int x, int y, int angle, int end_angle, int radius) : Figure(c, x, y), angle(angle), end_angle(end_angle), radius(radius) {}
      ~HalfCircle() { hide(); }
      void setsizes(int angle, int end_angle, int radius); //Метод для изменения размеров фигуры
};

void HalfCircle::setsizes(int angle, int end_angle, int radius){
   bool F = isvisible();
   if(F) hide();
   this->angle = angle;
   this->end_angle = end_angle;
   this->radius =radius;
   if(F) show();
}

//Метод, который рисует  полукруг
void HalfCircle::draw(){
   ::setcolor(getcolor()); //?
   arc(x, y, angle,  end_angle, radius);
}

//Получение прямоугольника
void HalfCircle::area(int &x1, int &y1, int &x2, int &y2) const {
   x1 = x - radius; // Левый край
   y1 = y - radius; // Верхний край
   x2 = x + radius; // Правый край
   y2 = y + radius; // Нижний край
}


int main(){
   initwindow(800,600);
   

   
   Figure* obj = new HalfCircle(RED, 10,10, 45, 135, 100);
   
   cout << "Hrll"<<'\n';
   obj->show();
   cout << "sdfs"<<'\n';
   getch();
   //obj->move(30, 150);
   //getch();
   //obj->setcolor(RED);
   //obj.show();
   delete obj;
   closegraph();
   return 0;
}



/*
int main(void)
{
   initwindow(800,800);
   //int gdriver = DETECT, gmode, errorcode;
   int midx, midy;
   int stangle = 45, endangle = 135;
   int radius = 100;


   midx = getmaxx() / 2;
   midy = getmaxy() / 2;
   setcolor(getmaxcolor());

   
   arc(midx, midy, stangle, endangle, radius);
   

   getch();
   closegraph();
   return 0;
}*/