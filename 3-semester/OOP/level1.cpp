//Романов Никита ЕТ-212
//Вариант 21
//Задание 0
//Структура программы на С++, ввод-вывод, динамическое выделение памяти
#include <iostream>
#include <stdlib.h>
using namespace std;

int main(){
   int size, a, b;
   cin >> a >> b >> size;
   srand(time(0));
   int* m = new int [size];
   for(int i = 0; i < size; i++){
      m[i] = rand() % (b-a+1)+a;
      cout << m[i] << ' ';
   }
   cout << endl;
   
   
   int* m1 = new int [size];
   int zero_pos = 0, negative_pos = 0, pozitive_pos = 0;
   
   for(int i = 0; i < size; i++){
      if(m[i] == 0){
         m1[zero_pos] = m[i];
         zero_pos++;
      }
   }
   
   negative_pos = zero_pos;
   for(int i = 0; i < size; i++){
      if(m[i] < 0){
         m1[negative_pos] = m[i];
         negative_pos++;
      }
   }
   
   pozitive_pos = negative_pos;
   for(int i = 0; i < size; i++){
      if(m[i] > 0){
         m1[pozitive_pos] = m[i];
         pozitive_pos++;
      }
   }
   
   for(int i = 0; i < size; i++){
      cout << m1[i] << ' ';
   }
   cout << endl;
   
   delete[] m;
   delete[] m1;
}