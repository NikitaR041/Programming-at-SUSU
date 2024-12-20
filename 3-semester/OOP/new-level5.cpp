#include <iostream>
/*
������� 4 | �������, �������������� �������� | ������� ������ ��-212 
������� 21      
*/

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

template <typename T>
class Deque{
   T* m; //��������� �� ������ ����������� �����
   int size; //������ �������
   int head; //������ ������ ����
   int tail; //������ ������ ���� 
public:
   Deque(int size) : size(size), head(0), tail(0), m(new T[size]) { } //�����������
   Deque(const Deque<T>&); //����������� �����
   ~Deque() { delete []m; } //����������
   
   bool empty(); //�������� �� ������� ���������
   void pushBack(const T&); //�������� ������� �������� � ����� ����
   void pushFront(const T&); //�������� ������� �������� � ������ ���� 
   T popBack(); //�������� ������� ��������� ��������
   T popFront(); //�������� ������� ���������� ��������
   
   Deque<T>& operator=(const Deque<T>&); //���������� ��������� ������������
   
   void printDeque() const; //�������� ��������� ���������
};

//����������� ������������ �����
template <typename T>
Deque<T>::Deque(const Deque<T>& other) : size(other.size), head(other.head), tail(other.tail), m(new T[other.size]) {
   for(int i = 0; i < size; i++){
      m[i] = other.m[i];
   }
}

//�������� �� ������� ���������
template <typename T>
bool Deque<T>::empty() {
    return head == tail;
}

//�������� ������� �������� � ����� ����
template <typename T>
void Deque<T>::pushBack(const T& value){
   if(head == (tail + 1) % size){
      throw DequeFull();
   }
   m[tail] = value;
   tail = (tail + 1) % size;
}

//�������� ������� ��������� ��������
template <typename T>
T Deque<T>::popBack(){
   if(empty()) {
      throw DequeEmpty();
   }
   tail = (tail - 1 + size) % size;
   return m[tail];
}       

//�������� ������� �������� � ������ ���� 
template <typename T>
void Deque<T>::pushFront(const T& value){
   if(head == (tail + 1) % size){
      throw DequeFull();
   }
   head = (head - 1 + size) % size;
   m[head] = value;
}

//�������� ������� ���������� ��������
template <typename T>
T Deque<T>::popFront(){
   if(empty()){
      throw DequeEmpty();
   }
   head = (head + 1) % size;
   return m[head];
}

//���������� �������� ������������
//������, ����� ������������� ������ �� ����������
template <typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& other){
  if(size != other.size){
      throw DequeFull();
   } 
   
   for (int i = 0; i < size; ++i){
      m[i] = other.m[i];
   }
   return *this;
}

//�������� ��������� ���������
template <typename T>
void Deque<T>::printDeque() const {
   for (int i = 0; i < size; i++) {
      std::cout << m[i] << ' ';
   }
   std::cout << std::endl;
}

int main() {
   Deque<int> obj(3);
   std::cout << "\n���� 1. ���������� ��������� ��� ������ ������� pushFront � pushBack" << '\n';
   try {
      // ��������� �������� � ����� � ������ �������
      obj.pushFront(4);
      obj.pushFront(10);
      obj.pushBack(2);
      obj.pushFront(5);  // ������� �������� ������� ��� ������ ����
      obj.pushBack(6); // ������� �������� ������� ��� ������ ����
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n';  // ������ ������������
   }
   
   std::cout << "�������� � ������������ �������" << '\n';
   obj.printDeque();
   
   // ����� ��������� ���� ����� ���������� ���������
   std::cout << "\n���� 2. �������� ��������� ��� ������ ������� popFront � popBack" << '\n';
   try {
      std::cout << "�������� �������� �����: " << obj.popFront() << '\n';  // ������� � ����� �������
      std::cout << "�������� �������� ������: " << obj.popBack() << '\n'; // ������� � ������ �������
      std::cout << "�������� �������� �����: " << obj.popFront() << '\n';  // ������� � ����� �������
      std::cout << "�������� �������� ������: " << obj.popBack() << '\n'; // ������� ������� �� ������� ����
   } catch (DequeEmpty& e) {
      std::cout << e.what() << '\n';  // ������ ������� ����
   }
   
   std::cout << "�������� � ������������ �������" << '\n';
   obj.printDeque(); //����� �������
   
   std::cout << "\n���� 3. ����������� �����" << '\n';
   try {
      Deque<int> copyObj = obj; //������������ �����
      copyObj.pushFront(7);
      copyObj.pushBack(3);
      std::cout << "����� ���: " << copyObj.popFront() << ", " << copyObj.popBack() << '\n';
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n'; 
   }
   
   // ���� 4. �������� ������������
   std::cout << "\n���� 4. �������� ������������" << '\n';
   try {
      Deque<int> assignObj(3);
      assignObj.pushFront(10);
      assignObj.pushBack(20);
      Deque<int> assignedObj(2);  // ��� � ������� �������� ��� ��������
      assignedObj = assignObj;  // ������������� ��������� ������������
      
      std::cout << "�������� � ������� assignedObj:" << '\n';
      assignedObj.printDeque();
   } catch (DequeEmpty& e) {
      std::cout << e.what() << '\n';
   } catch (DequeFull& e) {
      std::cout << e.what() << '\n';
   }
   
   return 0;
}
