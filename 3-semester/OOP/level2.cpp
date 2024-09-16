//Лабораторная работа 1 | Романов Никита ЕТ-212 | Вариант 21

#include <iostream>
#include <vector>
/*
Тема: Определение класса с динамически размещаемыми данными
Представьте, что перед вами и вашим партнером по игре на столе лежит несколько кучек камешков. 
Правила игры разрешают забрать за один ход любое количество камешков - но только из одной кучки. 
Выигрывает тот из двух игроков, кто забирает со стола последний камешек.
*/

using namespace std;

class NIM{
      int nheap; //Количество кучек для камешек
      int *heaps = new (int)[]; //Одномерный массив, где в каждом элементе свое количество камешек в определенной кучке
   public:
      NIM(int nheap = 10) : nheap(nheap), heaps(new int [nheap]){}
      ~NIM(){ delete [] heaps}; // vector сам освобождает память
      void setheap(int i, int nmatch); //Задать количество спичек в i кучке
      void take(int i, int nmatch); //Взять из i кучки nmatch спичек
      int amount(int i) const; //Количество спичек в кучке i
      int count() const; //Количество кучек
      bool iswin() const; //Все кучки пусты
      void print() const; //Распечатать состояние объекта
};

//Реализация задания количество спичек в i кучке
// i - индекс, т.е. номер кучки, nmatch - количество камешек
void NIM::setheap(int i, int nmatch){
   if(i >= 0 && i < nheap){
      heaps[i] = nmatch;
   }
}

//Реализация взятия из i кучки nmatch спичек
void NIM::take(int i,int nmatch){
   if(i >= 0 && i < nheap && nmatch > 0 && heaps[i] >= nmatch){
      heaps[i] -= nmatch;
   }
}

//Реализация распечати количество спичек в кучке i
//Количество спичек в кучке i
int NIM::amount(int i) const{
   if(i >= 0){
      return heaps[i];
   }
   return -1; //Если ничего нет
}

//Реализация распечати количество кучек
int NIM::count() const{
   return nheap;
}

//Реализация метода на проверку, что все кучки пусты или не пусты
bool NIM::iswin() const{
   for(int hp : heaps){
      if(hp > 0) return false;
   }
   return true;
}

//Реализация  печати состояния объекта
void NIM::print() const{
   
}
//
int main(){
   
}