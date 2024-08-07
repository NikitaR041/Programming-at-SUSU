#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

/*
������ 2:
����� ����� N ���������� ������ ���������, ���� ��� �������� ��������� ������-���� ������ �����, �� ���� ���������� ����� ����� S, ��� N = S^2.
���� ����� ����� F � L.
��������� ����� ���������� ������ ��������� �� F �� L ������������.
��������, �� 5 �� 25 ������������ ��� ������ �������� � 9 = 3^2, 16 = 4^2 � 25 = 5^2.
� ������ ������ �������� ����� ���������� ��� ����� ����� F � L (0 <= F <= L <= 10^9).
�������� � �������� ���� ���� ������� �����.

int main(){
   int F, L;
   int count = 0;
   cin >> F >> L;
   F = ceil(sqrt(F));
   L = floor(sqrt(L));
   while(F <= L){
      count++;
      F++;
   }
   cout << count << '\n';
   return 0;
}*/

/*
������ 3:
������� ��� ������� ����� �� M �� N ������������.
����
� ������ ������ ��������� ���������� �������� M � N (1 <= M <= N <= 1 000 000).
�����
������� ����� � ������� �����������, �� ������ � ������. ���� ����� M � N ������������ ��� ������� � ������� "Absent".

bool prosto(int n){
   if (n == 1) return false;
   int i = 2;
   while (i * i <= n){
         if(n % i == 0){
               return false;
            }
         i++;
      }
      return true;
}

int main(){
   int M, N;
   int flag = 0;
   cin >> M >> N;
   for(M; M <= N; M++){
         if(prosto(M) == true){
               cout << M << '\n';
               flag++;
         }
      }
   if (flag == 0){
      cout << "Absent" << '\n';
   }
}
*/

/*
������ 4:
������� ������������� ������ ����� N � ���� ������������ ������� �����.
����
� ������ ������ ��������� ������������ ����� N (2 <= N <= 2^31 - 1).
�����
��������� ������ ����� � ������� ����������, ���������� ������ "*".
*/
/*
bool prosto(int n){
   if (n == 1) return false;
   int i = 2;
   while (i * i <= n){
         if(n % i == 0){
               return false;
            }
         i++;
      }
      return true;
}*/
/*������ �������, �� �� �������� ������-��
int main(){
   string s;
   unsigned int N;
   cin >> N;
   for(int i = 2; i <= N; i++){
      if(prosto(i) == true){
         while(N % i == 0){
            N = N / i;
            if(N != 1){
               s += to_string(i) + '*';
            }else{
               s += to_string(i);
            }
         }
      }
   }

   return 0;
}*/
/* ������ �������, �� �� �������� ������-��
int main() {
   string s;
   unsigned int N;
   cin >> N;
   for (int i = 2; i <= sqrt(N); i++) {
      while (N % i == 0) {
         N = N/i;
         if (N != 1) {
            s += to_string(i) + '*';
         } else {
            s += to_string(i);
         }
      }
   }
   cout << s << '\n';
   return 0;
}
/* ������ ������� ������
int main(){
   int N;
   cin >> N;
   for(int i = 2; i <= sqrt(N); i++){
      while(N % i == 0){
         N = N / i;
         cout << i;
         if (N != 1) cout << '*';
      }
   }
   if (N != 1) cout << N;
   cout << '\n';
   return 0;
}*/

/*
������ 4: ����������
���� �������� ��������� � ����� �100 �����������, �� ������������ ����� �����������, � ��������, � ������������ ����� ������. 
��������, ��� ���������� ������, ������� ��������� ���������� ���������� ��� ������ �� N �������. 
���� �������� �������, ��� ���� N � ������� �����, �� ���������� ������ 2 ����������: � ������� �� ������ (1*N) � � ������� (N*1). 
��� ����������� ���������� �������� ��� ������ N > 1 (��� N = 1 ���������� ������ ���� ���������� 1 ? 1, ������� �� �������� �� ��������, �� ��������). 
���� N � ��������� �����, �� ���������� � ������ ������������� ����������. ��� 100 ������� ���������� ������ ����������: 1*100, 2*50, 4*25, 5*20, 10*10, 20*5, 25*4, 50*2 � 100*1.
�������� ���������, ������� ������� ����� ��������� ���������� ��� ������ �� N �������.
� ������ ������ ����� ���������� ���� ����� ����� N (1 <= N <= 10^9).
������� ���� ����� ����� � ���������� ��������� ���������� ��� ������ �� N �������.
*/
/*
����:
1)�������� ������� �� ���������� ��������� �����
*/
/*
int main(){
   vector<int> mass;
   int n, count = 0;
   cin >> n;
   //������� �������� ����� - ����������
   int i = 1;
   while(i*i <= n){
      if(i*i == n){
         mass.push_back(i);
      }else if(n % i == 0){
         mass.push_back(i);
         mass.push_back((n / i));
      }
      i++;
   }
   cout << mass.size() << '\n';
   return 0;
}*/

/*
������ 5: ���� � ������� ����� - ������������
� ��������� ���� � ����� ����� ���������� ����� �� ���� ��������� �����.
��� ���� ���������� ���� � ������������ ����� �� ������ ��������� ���������� ���� ���� � �����-������.
����������� ��������� ���, ��� �������� ���������� ���������� ����.
�������� ��������� ��� ���� � �����, ������� ���������� ������� ����� �� ���� ��������� �����.
������ ������ ����� �������� ���� ����� N (1<=N<=10^7).
������� ���������� ��������� ������� �����, ������� ����� ��������� �� ���� ����� N.
*/
/*
int main() {
    std::string s = "abc";
    do {
        std::cout << s << '\n';
    } while(std::next_permutation(s.begin(), s.end()));
    return 0;
}
*/
/*
bool prosto(int n) {
   if (n == 1) return false;
   int i = 2;
   while (i * i <= n) {
      if (n % i == 0) {
         return false;
      }
      i++;
   }
   return true;
}

int main() {
   string s;
   cin >> s;
   int count = 0, len;
   len = s.length();
   for(int i = 0; i < len; i++){
      if(s[i] == '2' || s[i] == '3' || s[i] == '5' || s[i] == '7') count++;
   }
   sort(s.begin(), s.end());
   for (int i = 1; i <= len; i++) {
      do {
         //cout <<s.substr(0, i) << '\n';
         if(prosto(stoi(s.substr(0, i)))) count++;
      } while(next_permutation(s.begin(), s.begin()+i));
   }
   cout << count << '\n';
   return 0;
}*/

/*
����:
1)����� �������, ������� ��������� �� �������� ����� ��� �����
2)�� ���� ��������� ����� ->���������� �� ����� -> ��������� �� �������� ����
->���������� �������� ->��������� �� ��������� (��� ��������� ���) -> ������� ����� � ����������
*/
