//������������ ������ 1 | ������� ������ ��-212 | ������� 21

#include <iostream>
#include <vector>
/*
����: ����������� ������ � ����������� ������������ �������
�����������, ��� ����� ���� � ����� ��������� �� ���� �� ����� ����� ��������� ����� ��������. 
������� ���� ��������� ������� �� ���� ��� ����� ���������� �������� - �� ������ �� ����� �����. 
���������� ��� �� ���� �������, ��� �������� �� ����� ��������� �������.
*/

using namespace std;

class NIM{
      int nheap; //���������� ����� ��� �������
      int *heaps = new (int)[]; //���������� ������, ��� � ������ �������� ���� ���������� ������� � ������������ �����
   public:
      NIM(int nheap = 10) : nheap(nheap), heaps(new int [nheap]){}
      ~NIM(){ delete [] heaps}; // vector ��� ����������� ������
      void setheap(int i, int nmatch); //������ ���������� ������ � i �����
      void take(int i, int nmatch); //����� �� i ����� nmatch ������
      int amount(int i) const; //���������� ������ � ����� i
      int count() const; //���������� �����
      bool iswin() const; //��� ����� �����
      void print() const; //����������� ��������� �������
};

//���������� ������� ���������� ������ � i �����
// i - ������, �.�. ����� �����, nmatch - ���������� �������
void NIM::setheap(int i, int nmatch){
   if(i >= 0 && i < nheap){
      heaps[i] = nmatch;
   }
}

//���������� ������ �� i ����� nmatch ������
void NIM::take(int i,int nmatch){
   if(i >= 0 && i < nheap && nmatch > 0 && heaps[i] >= nmatch){
      heaps[i] -= nmatch;
   }
}

//���������� ��������� ���������� ������ � ����� i
//���������� ������ � ����� i
int NIM::amount(int i) const{
   if(i >= 0){
      return heaps[i];
   }
   return -1; //���� ������ ���
}

//���������� ��������� ���������� �����
int NIM::count() const{
   return nheap;
}

//���������� ������ �� ��������, ��� ��� ����� ����� ��� �� �����
bool NIM::iswin() const{
   for(int hp : heaps){
      if(hp > 0) return false;
   }
   return true;
}

//����������  ������ ��������� �������
void NIM::print() const{
   
}
//
int main(){
   
}