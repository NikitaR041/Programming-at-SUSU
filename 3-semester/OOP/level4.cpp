#include <iostream>
#include <graphics.h>
#include <math.h>
using namespace std;
/*
������� 3 | ������� ������ ��-212 | ������� 21
����: ����������� ������, ������������
*/

//������������-����������� �����
class Figure{
      int c; // ����
      bool visible; //���������
   protected:
      int x,y; //������� �����
      virtual void draw() = 0;//����� ����������� ����� - ����������
   public:
      Figure(int c, int x, int y) : c(c), visible(false), x(x), y(y) {} //�����������
      virtual ~Figure(){} //����������
      void move(int x, int y); //�������� ������ � ����� (�, �)
                                            //������� ������ �������, ����� �������� � ������ �����
                                            //� ��������� ������ �������� ���� �,�
      void setcolor(int c);     //���������� ���� ������
                                          //������� ������ �������� ����� ������
                                          //� ��������� ������ �������� ���� � 
      int getcolor() const {return c;} //�������� ����
      void hide();      //��������: ���������� ������ �������������
                              //                        �� �������� area()
      void show();      //��������
      bool isvisible() const {return visible;} //������?
      virtual void area (int &x1, int &y1, int &x2, int &y2) const = 0; //����� ����������� �����
                           //�������� ������� ������������� �������, ���������� ������
};
//�������� ������ � ����� (�,�)
void Figure::move(int x, int y){
   bool flag = visible;
   if (flag) hide();
   this->x = x;
   this->y= y;
   if(flag) show();
}
//������� �����
inline void Figure::setcolor(int c){
   this->c=c;
   if(visible) draw();
}

//��������� ������� ����
void Figure::hide(){
   if(!visible) return;
   int x1,y1,x2,y2;
   area(x1,y1,x2,y2);
   setfillstyle(SOLID_FILL,BLACK);
   bar(x1,y1,x2,y2);
   visible = false;
}

//����������� ������
void Figure::show(){
   if(!visible){
      visible= true;
      draw();
   }
}

//��������
class HalfCircle : public Figure{
   protected:
      int angle; //���� ��������
      int radius; //������
      void draw() override;
      void area (int &x1, int &y1, int &x2, int &y2) const override final; //�� ����� ����������� ���������������
   public:
      HalfCircle(int c, int x, int y,  int angle,  int radius) : Figure(c, x, y), angle(angle), radius(radius){}
      ~HalfCircle() { hide(); }
      void setsizes(int angle, int radius); //����� ��� ��������� �������� ������
};

void HalfCircle::setsizes(int angle, int radius){
   bool F = isvisible();
   if(F) hide();
   this->angle = angle;
   this->radius =radius;
   if(F) show();
}

//�����, ������� ������  ��������
void HalfCircle::draw(){
   ::setcolor(getcolor()); 
   arc(x, y, angle, angle + 180, radius);
   line(x - radius, y, x + radius, y);
}

//��������� ��������������
void HalfCircle::area(int &x1, int &y1, int &x2, int &y2) const {
   x1 = x - radius; // ����� ����
   y1 = y - radius; // ������� ����
   x2 = x + radius; // ������ ����
   y2 = y + radius; // ������ ����
}

class FillHalfCircle : public HalfCircle{
   int Fillcolor; //�������� ���� ������� ������
   void draw() override final; //�� ����� ����������� ���������������
   public:
      FillHalfCircle(int c, int x, int y,  int angle, int radius, int Fillcolor) : HalfCircle(c, x,  y, angle, radius), Fillcolor(Fillcolor) {}
      ~FillHalfCircle(){ hide(); }
      void setFillcolor(int c); //�������� ���� ��������
};

//���������� ������ ��������
inline void FillHalfCircle::setFillcolor(int c){
   Fillcolor = c;
   if(isvisible()) draw();
}

//���������� � ��������� ������ ������
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
   
   // ���������, ����� �� ��������� �������������� � ����������� �������
   if (HalfCircle* hc = dynamic_cast<HalfCircle*>(obj1)) {
      hc->setsizes(180, 150); // ������ ���� � ������
      getch();
   }

   if (FillHalfCircle* fhc = dynamic_cast<FillHalfCircle*>(obj2)) {
      fhc->setsizes(180, 120); // ������ ���� � ������
      getch();
   }
   
   if(FillHalfCircle* fhc = dynamic_cast<FillHalfCircle*>(obj2)){
      fhc->setFillcolor(MAGENTA);  // ������ ���� �������
      getch();
   }
   
   getch();
   delete obj1;
   delete obj2;
   getch();
   closegraph();
   return 0;
}


