#include <iostream>
#include <algorithm>
/*
������������ ������ 3 | ���������� ������� � �������

*/

class Rect{
   int l, t, r ,b; // ����� ���������� ��������������
   public:
      //�����������
      Rect(int l = 0, int t = 0, int r = 0, int b = 0) : l(l), t(t), r(r), b(b) {};  
      //������ ��� ��������� �������� ������
      int getLeft() {return l;} //���������� l - ����� �������
      int getTop() {return t;} //���������� t - ������� �������
      int getRight() {return r;} //���������� r - ������ �������
      int getBottom() {return b;} //���������� b - ������ �������
      
      //���������� ����������
      Rect operator+(const Rect&); //���������� ��������� ����������� +
      Rect operator*(const Rect&); //���������� ��������� ����������� *
      Rect& operator+=(const Rect&); //��������� ��������� += ��� �����������
      Rect& operator*=(const Rect&); //���������� ��������� *= ��� ����������� 
      bool operator!() const; //���������� ��������� ! - �������� �� �������
      
      //���������� ���������� ���������
      friend bool operator==(const Rect&, const Rect&); //���������� ��������� ==
      friend bool operator!=(const Rect&, const Rect&); //���������� ��������� !=
      friend bool operator<=(const Rect&, const Rect&); //���������� ��������� <=
      friend bool operator>=(const Rect&, const Rect&); //���������� ��������� >=
      
      //��������� ����� � ������
      friend std::ostream& operator<<(std::ostream&, const Rect&); //���������� ��������� <<
      friend std::istream& operator>>(std::istream&, Rect&); //���������� ��������� >>
};

//���������� ��������� + ��� ������� Rect - �����������
Rect Rect::operator+(const Rect& other){
      Rect temp;
      temp.l = std::min(this->l, other.l);
      temp.t = std::min(this->t, other.t);
      temp.r = std::max(this->r, other.r);
      temp.b = std::max(this->b, other.b);
      return temp;
}

//���������� ��������� * ��� ������� Rect - �����������
Rect Rect::operator*(const Rect& other){
      //�� ������ ��������� �� ����������� ���� ���������������
      int x1, y1, x2, y2;
      x1 = std::max(this->l, other.l);
      y1 = std::max(this->t, other.t);
      x2 = std::min(this->r, other.r);
      y2 = std::min(this->b, other.b);
   
      if(x1 > x2 || y1 > y2){
         std::cout << "��� �����������, ���������� ������ ������: " << '\n';
         return Rect(); //���������� ������, ��� ��� ������ �����������
      }

      return Rect(x1, y1, x2, y2); 
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
//���������� ��������� ! (�������� �� �������)
bool Rect::operator!() const {
    return (l >= r || t >= b);
}
//���������� ��������� ==
inline bool operator==(const Rect& other1, const Rect& other2){
      return other1.l == other2.l && other1.t == other2.t && other1.r == other2.r && other1.b == other2.b;
}

//���������� ��������� !=
inline bool operator!=(const Rect& other1, const Rect& other2){
      return !(other1.l == other2.l && other1.t == other2.t && other1.r == other2.r && other1.b == other2.b);
}

//���������� ��������� <=  - ������ ������ ��������� ����� �� ������ �������
inline bool operator<=(const Rect& other1, const Rect& other2){
      return other1.l >= other2.l && other1.t >= other2.t && other1.r <= other2.r && other1.b <= other2.b;
}

//���������� ��������� >= - ������ ������ ��������� ����� � ������ �������
inline bool operator>=(const Rect& other1, const Rect& other2){
   return other1.l <= other2.l && other1.t <= other2.t && other1.r >= other2.r && other1.b >= other2.b;
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
   //������� ��������� �������� ������ Rect
   Rect a = {1, 2, 3, 4}; //������, ������� ����� ������������������
   Rect b, c;
   Rect answer;  //���� ������ ��� �������������� ��������� !
   
   //��������� ���� � �����
   std::cout << "���������� ������� ��������� ��� ��������� �������� � ������� �� �������� [a b c d]." << '\n';
   std::cin >> b; //������� ����� ��� b: [1 2 3 4], [0 0 5 5], [1 1 5 5], [1 1 4 4], [0 0 2 2], [1 1 5 5]
   std::cin >> c; //������� ����� ��� b: [1 2 3 4],  [1 1 3 3], [2 2 6 6],  [2 2 5 5], [3 3 5 5], [2 2 6 6]
   std::cout << "��� ���� �������: " << a << ' ' << b << ' ' << c << '\n';
   
   std::cout << '\n';
   
   //��������� ������ �� ��������� ��������� ������������� �������
   std::cout << "���������� L � ������� b: " << b.getLeft() << '\n';
   std::cout << "���������� T � ������� b: " << b.getTop() << '\n';
   std::cout << "���������� R � ������� b: " << b.getRight() << '\n';
   std::cout << "���������� B � ������� b: " << b.getBottom() << '\n';
   
   std::cout << '\n';
   
   //��������� ������ �� ����������� � ����������� ���� ��������
   std::cout << "����������� ���� �������� a + b: " << a + b << '\n';
   std::cout << "����������� ���� �������� b * c: " << b * c << '\n';
   std::cout << "����������� ���� �������� b + c: " << b + c<< '\n';
   
   
   std::cout << '\n';
   
   //��������� ������������� ��������� += � *=
   a+=b;
   std::cout << "������ ������ ��������� += ���� �������� a � b: " << a << '\n';
   b*=c;
   std::cout << "������ ������ ��������� *= ���� �������� b � �: " << b << '\n';
   b+=c;
   std::cout << "������ ������ ��������� += ���� �������� b � c: " << a << '\n';
   
   std::cout << '\n';
   
   //��������� ������������� �������� !
   answer = b * c; //� �������, ����� ����������, ��� ������ ����� ��������� [0 0 0 0] ��� [5, 5, 3, 3]
   if(!answer) std::cout << "��, ������ answer ������!" << '\n';
   else std::cout << "���, ������ �� ������!" << '\n';
   
   std::cout << '\n';
   
   //��������� ������������� ��������� ==, !=, <=, >=
   if(b<=c){
      std::cout<< "������ b <= c" << '\n';
   }else if(b >= c){
      std::cout << "������ b >= c" << '\n';
   }
   
   if(a == b){
      std::cout<< "������� a � b �����!" << '\n';
   }else if (a != b){
      std::cout<< "������� a � b �� �����!" << '\n';
   }
   
   std::cout << '\n';
   return 0;
}