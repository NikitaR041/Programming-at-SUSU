#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Задача: Пары
*/

/*
#include <iostream>
#include <algorithm>
using namespace std;

int compare(const void *x1, const void *x2)     // функция сравнения элементов массива
{
   return (*(int *)x1 - *(int *)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}


int main() {
   int n;
   cin >> n;

   int m[n];
   for (int i = 0; i < n; i++) {
      cin >> m[i];
   }

   qsort(m, n, sizeof(int), compare);

   int count = 0;
   int i = 0;

   while (i < n) {
      int j = i + 1;
      while (j < n && m[j] == m[i]) {
         ++j;
      }
      int t = j - i;
      count += (t * (t - 1)) / 2;
      i = j;
   }

   cout << count << '\n';
   return 0;
}*/

/*
Задача: Все одинаковые
Не получилось
*/

/*
int compare(const void *x1, const void *x2)     // функция сравнения элементов массива
{
   return (*(int *)x1 - *(int *)x2);              // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}

int main(){
   int n;
   cin >> n;
   int m[n];

   for(int i = 0; i < n; i++){
      cin >> m[i];
   }

   qsort(m, n, sizeof(int), compare);

   int madian = m[n/2];

   long int t = 0;
   for(int i = 0; i < n; i++){
      t += abs(m[i] - madian);
   }

   cout << t << '\n';
   cout << madian << '\n';
   return 0;
}*/

/*
Задача: Максимальное число
*/

/*
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

bool compare(const string &a, const string &b) {
   return (a + b > b + a);
}

int main() {
   int n;
   cin >> n;

   vector<string> nums(n);
   for (int i = 0; i < n; ++i) {
      cin >> nums[i];
   }

   sort(nums.begin(), nums.end(), compare);

   for (int i = 0; i < n; ++i) {
      cout << nums[i] << ' ';
   }
   cout << '\n' ;

   return 0;
}*/

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main() {
   int n, k;
   cin>>n>>k;
   vector<int> a(n);
   int r=0;
   int r1=0;
   int r2=0;
   for(int i=0; i<n; ++i) {
      cin>>a[i];
      r+=a[i];
   }
   sort(a.begin(), a.end());
   for(int i=0; i<k && a[i]<0; ++i) {
      r1+=a[i];
   }
   for(int i=n-1; i>=n-k && a[i]>0; i--) {
      r2+=a[i];
   }
   r1=abs(-2*r1+r);
   r2=abs(r-2*r2);
   cout<<max(r1, r2);
}
