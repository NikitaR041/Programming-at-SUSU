#include "MyGraph.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
int main(){
   vector<string> test = {"15.02.2025", "53.23.2023", "01.01.202"};
   
   for (const auto& i : test) {
      MyGraph sm;
      cout << "Строка " << i << '\n';
      cout << "Начальное состояние " << sm.state() << '\n';
      
      for (auto j : i) {
         sm.signal(j);
         cout << "Сигнал " << j << "-> состояние " << sm.state() << '\n';
      }
      cout << "Завершенное состояние " << sm.state() << '\n';
   }
}