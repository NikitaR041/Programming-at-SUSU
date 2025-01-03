#include <iostream>
/*
������� 4 | �������, �������������� �������� | ������� ������ ��-212 
������� 21      
*/

//�������������� ���������
struct DequeError : public std::exception{ // ������� ����� ��� ������
   virtual ~DequeError() {}; //����������
   virtual const char *what() const noexcept =0; //��������� ��� ������
};

struct DequeFull : DequeError {
   const char *what() const  noexcept override { return "������: ������������ ������� �������������!"; } //��������� ��� ������
};

struct DequeEmpty : DequeError {
   const char *what() const noexcept override {return "������: ������������ ������� �����!"; } //��������� ��� ������
};

//��������� ��������� ����� ������ ��� ����� ����� ������
//deque - ����������� ������
template <typename T>
class Deque{
   T *m; //��������� �� �������
   int lenght; //������� ���������� ��������� � ������������ �������
   int capasity; //������������ ������ ������������ �������
   int left; //������ ������
   int right; //������ �����
public:
   //�����������
   Deque(int capasity) : lenght(0), capasity(capasity), left(0), right(-1), m(new T[capasity]) {}
   //����������� �����
   Deque (const Deque<T>&);
   //����������
   ~Deque() {delete []m; } 
   
   void pushLeft(const T&); //���������� �������� � ������ ������������ �������
   void pushRight(const T&); //���������� �������� � ����� ������������ �������
   T popLeft(); //����������� � ������ ������������ �������
   T popRight(); //���������� � ����� ������������ �������
   
   Deque<T>& operator=(const Deque<T>&); //�������� ������������
   
   void printDeque() const; //��������� ��������
};

//���������� ������� � ����������
//����������� ������������ �����
template <typename T>
Deque<T>::Deque(const Deque<T>& other) : lenght(other.lenght), capasity(other.capasity), left(other.left), right(other.right), m(new T[other.capasity]) {
   std::cout << "����������� ����� ���������!" << '\n';
   for(int i = 0; i < lenght; i++){
      m[i] = other.m[i];
   }
}

//��������������� ��������� ������������  (��������, obj1 = obj2, ��� obj1 � obj2 - ��� ������� ������ Deque)
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
        std::cout << "������ ��� ������������: " << e.what() << '\n';
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
   // ������������� ��� � �������� 3
   Deque<int> obj(3);
   std::cout << "\n���� 1. ���������� ��������� ��� ������ ������� pushLeft � pushRight" << '\n';
   try {
      // ��������� �������� � ����� � ������ �������
      obj.pushLeft(4);
      obj.pushLeft(10);
      obj.pushRight(2);
      obj.pushLeft(5);  // ������� �������� ������� ��� ������ ����
      obj.pushRight(6); // ������� �������� ������� ��� ������ ����
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n';  // ������ ������������
   }
   
   std::cout << "�������� � ������������ �������" << '\n';
   obj.printDeque();
   
   // ����� ��������� ���� ����� ���������� ���������
   std::cout << "\n���� 2. �������� ��������� ��� ������ ������� popLeft � popRight" << '\n';
   try {
      std::cout << "�������� �������� �����: " << obj.popLeft() << '\n';  // ������� � ����� �������
      std::cout << "�������� �������� ������: " << obj.popRight() << '\n'; // ������� � ������ �������
      std::cout << "�������� �������� �����: " << obj.popLeft() << '\n';  // ������� � ����� �������
      std::cout << "�������� �������� ������: " << obj.popRight() << '\n'; // ������� ������� �� ������� ����
   } catch (DequeEmpty& e) {
      std::cout << e.what() << '\n';  // ������ ������� ����
   }
   
   std::cout << "�������� � ������������ �������" << '\n';
   obj.printDeque(); //����� �������
   
   std::cout << "\n���� 3. ����������� �����" << '\n';
   Deque<int> copyObj = obj; //������ ���� ����� ��������� �� ������������ �����
   try {
      copyObj.pushLeft(7);
      copyObj.pushRight(3);
      std::cout << "����� ���: " << copyObj.popLeft() << ", " << copyObj.popRight() << '\n';
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n'; 
   }
   
   // ���� 4. �������� ������������
   std::cout << "\n���� 4. �������� ������������" << '\n';
   Deque<int> assignObj(3);
   assignObj.pushLeft(10);
   assignObj.pushRight(20);
   Deque<int> assignedObj(2);  // ��� � ������� �������� ��� ��������
   assignedObj = assignObj;  // ������������� ��������� ������������
   try {
      std::cout << "����� ������������: " << assignedObj.popLeft() << ", " << assignedObj.popRight() << '\n';
   } catch (DequeEmpty& e) {
      std::cout << e.what() << '\n';
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n';
   }
   
   return 0;
}


