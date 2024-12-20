#include <iostream>
#include <algorithm>
#include <utility>
using namespace std::rel_ops;

/*
������������ ������ 3 | ���������� ������� � ������� | ������ 21
*/

class Rect{
   int l, t, r, b; // ����� ���������� ��������������
   //��� l � t - ��� ����� ������� ����� (l, t); ��� r � t - ��� ������ ������ ����� (r,t).
   public:
      //�����������
      Rect(int l = 0, int t = 0, int r = 0, int b = 0) : l(l), t(t), r(r), b(b) {};  
      //������ ��� ��������� �������� ������
      int getLeft() const {return l;} //���������� l - ����� �������
      int getTop() const {return t;} //���������� t - ������� �������
      int getRight() const {return r;} //���������� r - ������ �������
      int getBottom() const {return b;} //���������� b - ������ �������
      
      //���������� ����������
      Rect& operator+=(const Rect&); //��������� ��������� += ��� �����������
      Rect& operator*=(const Rect&); //���������� ��������� *= ��� ����������� 
      bool operator!() const; //���������� ��������� ! - �������� �� �������
      
      friend bool operator==(const Rect&, const Rect&);
      friend bool operator<(const Rect&, const Rect&);
      
      friend std::ostream& operator<<(std::ostream&, const Rect&); //���������� ��������� <<
      friend std::istream& operator>>(std::istream&, Rect&); //���������� ��������� >>
};

//���������� ��������� + ��� ������� Rect - �����������
//������ �������� ���������� �� ��������
inline Rect operator+(Rect x, const Rect& other){
      return x += other;
}

//���������� ��������� * ��� ������� Rect - �����������
//������ �������� ���������� �� ��������
inline Rect operator*(Rect x, const Rect& other) {
      return x *= other;
}

//���������� ��������� +=  ��� ������� Rect - ����������� �������� �������
Rect& Rect::operator+=(const Rect& other){
      this->l = std::min(this->l, other.l);
      this->t = std::min(this->t, other.t);
      this->r = std::max(this->r, other.r);
      this->b = std::max(this->b, other.b);
      return *this;
}

//���������� ��������� *=  ��� ������� Rect - ��������� �������� �������
Rect& Rect::operator*=(const Rect& other){
      //�� ������ ��������� �� ����������� ���� ���������������
      this->l = std::max(this->l, other.l);
      this->t = std::max(this->t, other.t);
      this->r = std::min(this->r, other.r);
      this->b = std::min(this->b, other.b);
   
      if(this->l > this->r || this->t > this->b){
         std::cout << "��� �����������, ���������� ������ ������: " << '\n';
         return *this = Rect(); //�������� ������� ������, ��� ��� ������
      }

      return *this; 
}
//���������� ��������� ! (�������� �� ������� ������ ������� ����� ����������� ���� ��������)
bool Rect::operator!() const {
    return (l >= r || t >= b);
}
//���������� ��������� ==
inline bool operator==(const Rect& other1, const Rect& other2){
      return other1.l == other2.l && other1.t == other2.t && other1.r == other2.r && other1.b == other2.b;
}
//���������� ��������� !=
inline bool operator!=(const Rect& other1, const Rect& other2){
      return !(other1==other2);
}

// ���������� ��������� < ��� ������ Rect
inline bool operator<(const Rect& other1, const Rect& other2) {
    // ������ ������: ���� ������������� ������ �������, ���� ��� ����� ������� ����� "������", � ������ ������ ����� "������"
    return (other1.l < other2.l) && (other1.t < other2.t) && (other1.r < other2.r) && (other1.b < other2.b);
}

//���������� ��������� >= - ������ ������ ��������� ����� � ������ �������
inline bool operator>=(const Rect& other1, const Rect& other2){
      return !(other1<other2);
}
//���������� ��������� <=  - ������ ������ ��������� ����� �� ������ �������
inline bool operator<=(const Rect& other1, const Rect& other2){
      return !(other2<other1);
}

//���������� ��������� << ��������� �����
std::ostream &operator<<(std::ostream& out, const Rect& other){
      return out << '[' << other.l << ' ' << other.t << ' ' << other.r << ' ' << other.b << ']';
}

//���������� ��������� >> ��������� ����
std::istream &operator>>(std::istream &in, Rect& other){
    char h1, h2; // ��� ������ []
    in >> h1; // ������ ������ ������
    if (h1 != '[') {
        std::cerr << "��������� ����������� ������ '['" << '\n';
        return in;
    }
    
    in >> other.l >> other.t >> other.r >> other.b >> h2;
    return in;
}
int main(){
   //�������� �������� ���� Rect
   Rect a(1, 1, 5, 5), b(2, 2, 6, 6);
   Rect c, d;
   
   //��������� ���� � �����
   std::cout << "���������� ������� ��������� ��� ��������� �������� � ������� �� �������� [a b c d]." << '\n';
   std::cin >> c; 
   std::cout << "��� ���� �������: " << a << ' ' << b << ' ' << c << '\n' << '\n';
   
   //��������� ������ �� ��������� ��������� ������������� �������
   std::cout << "������ ����� (left,top) � ������� A " << '(' << a.getLeft() << ' ' << a.getTop() << ')' << '\n';
   std::cout << "������ ����� (right,bottom) � ������� A " << '(' << a.getRight() << ' ' << a.getBottom() << ')' << '\n' << '\n';
   
   //��������� ������ �� ����������� � ����������� ���� ��������
   std::cout << "����������� a+b " << a+b << ' ' << "����������� b*c " << b*c << '\n' << '\n';
   
   //�������� ������� �� �����������
   d = b * c;
   if(!d){
      if(b == c) std::cout << "������� b � c ������!" << '\n';
      else if(b!=c) std::cout << "������� b � c �� ������!" << '\n';
   }else {
      if(d <= c) std::cout << "������ d ����� � c" << '\n';
      else if(c >= b) std::cout << "������ � ����� � b" << '\n';
      else std::cout <<"������ C ����� �� �����" << '\n';
   }
   return 0;
}
