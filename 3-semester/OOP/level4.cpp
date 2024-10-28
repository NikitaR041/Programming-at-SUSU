#include <iostream>
#include <graphics.h>
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
      //Ниже чисто виртуальный метод
      virtual void draw() = 0; 
   public:
      Figure(int c, int x, int y);
      virtual ~Figure(){}; 
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
      //Ниже чисто вирутальный метод
      virtual void area (int &x1, int &y1, int &x2, int &y2) const = 0;
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
void Figure::setcolor(int c){
   this->c=c;
   if(visible) draw();
}
//Отображение фигуры
void Figure::show(){
   if(!visible){
         draw();
         visible=1;
      }
}
//Рисование 
void Figure::hide(){
   if(!visible) return;
   int x1,y1,x2,y2;
   area(x1,y1,x2,y2);
   setfillstyle(SOLID_FILL,BLACK);
   bar(x1,y1,x2,y2);
   visible = 0;
}

//Полукруг
class HalfCircle : public Figure{
   protected:
      int c; //Цвет линии
      int x, y; //Центр полукруга
      int radius; //Радиус
      int angle; //Угол поворота
   public:
      HalfCircle(int c, int x, int y, int radius, int angle) : HalfCircle(c, x, y), radius(radius), angle(angle){}
      ~HalfCircle();
      void setsizes(int radius, int angle); //Метод для изменения размеров фигуры
      void draw() override;
      void area (int &x1, int &y1, int &x2, int &y2) const override;
};

void HalfCircle::setsizes(int radius, int angle){
   this->radius =radius;
   this->angle = angle;
}

int main(){
   
   return 0;
}
