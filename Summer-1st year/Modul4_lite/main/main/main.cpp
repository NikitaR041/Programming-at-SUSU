#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


//Закраска прямой
/*
На числовой прямой окрасили N отрезков.
Известны координаты левого и правого концов каждого отрезка (Li и Ri).
Найти длину окрашенной части числовой прямой.
Ограничения: Li и Ri – целые,  -1 000 000 000 <= Li <= Ri <= 1 000 000 000, 1 <= N <= 15 000.
Ввод
В первой строке находится число N, в следующих N строках – пары Li и Ri.
Вывод
Вывести одно число – длину окрашенной части прямой.
*/

//Почти работает программа-1
/*
void count_line(vector<int>& mass, int left, int right, int* count){
   for(int i = left; i < right; i++){
      if (mass[i] == 0){
         mass[i] += 1;
         //cout << "hello" << '\n';
      }
   }
   int i = 0;
   while(mass[i] > 0){
      (*count)++;
   }

}

int main(){
   vector<int> mass(1000000001, 0);

   int N, left, right, count = 0;
   cin >> N;
   for(int i = 0; i < N; i++){
      cin >> left >> right;
      if(left > right) continue;
      else{
         count_line(mass,left, right, &count);
      }
   }

   //Вывод размера вектора
   if(count > 0){
      cout << count - 1 << '\n';
   }else{
      cout << count << '\n';
   }
   return 0;
}*/

//Вторая попытка - удачно
/*
int main() {
    //Количество отрезков и начало-конец
    int N, left, right;
    //Количество открытых точек и длина 'окрашенной части прямой'
    int open_point = 0, len = 0;

    cin >> N;
    vector<pair<int, int>> point_mass;
    for (int i = 0; i < N; i++) {
        cin >> left >> right;
        point_mass.push_back({left, 1});
        point_mass.push_back({right, -1});
    }
    sort(point_mass.begin(), point_mass.end());

    //Смотрим на последнюю точку - первая попавшаяся точка из линии
    int last_point = point_mass[0].first;

    //point_mass.size() - вернёт 2, так как два  отрезка (Не факт)
    for (int i = 0; i < point_mass.size(); i++) {
        pair<int, int>& tochka = point_mass[i];
        if (open_point > 0) { //1 -> 2 -> 1 ->
            len += tochka.first - last_point; // 1) 1; 2) 1; 3) 1; 4) [здесь мы пропускаем ход, так как open_point == 0];
        }
        open_point += tochka.second; //Увеличиваем длину (или понижаем длину) | 1) 1; 2) 2 ; 3) 1; 4) 0;
        last_point = tochka.first; // 1) 1; 2) 2; 3) 3; 4) 4;
    }
    //Выше, в цикле рассмотрел пример ввода: 2; 1-3, 2-4; ->Вывод: 3
    cout << len << '\n';
    return 0;
}*/

//Таможня
/*
Идёт 2163 год. Мишу, который работает в отделении таможни при космодроме города Нью-Питер, вызвал в кабинет шеф.
Как оказалось, недавно Министерство Налогов и Сборов выделило отделению определённую сумму денег на установку новых аппаратов для автоматического досмотра грузов. 
Естественно, средства были выделены с таким расчётом, чтобы грузы теперь находились на таможне ровно столько времени, сколько требуется непосредственно на их досмотр.

В руках шефа каким-то образом оказались сведения о надвигающейся ревизии — список из N грузов, которые будут контролироваться Министерством. 
Для каждого груза известны время его прибытия, отсчитываемое с некоторого момента, хранимого в большом секрете, и время, требуемое аппарату для обработки этого груза. 
Шеф дал Мише задание по этим данным определить, какое минимальное количество аппаратов необходимо заказать на заводе, чтобы все грузы Министерства начинали досматриваться сразу после прибытия. 
Необходимо учесть, что конструкция тех аппаратов, которые было решено установить, не позволяет обрабатывать два груза одновременно на одном аппарате. Напишите программу, которая поможет Мише справиться с его задачей.

На первой строке ввода задано число N (0 <= N <= 50 000). На следующих N строках находится по 2 целых положительных числа Ti и Li — время прибытия соответствующего груза и время, требуемое для его обработки (1 <= Ti <= 10^6, 1 <= Li <= 10^6).
Выведите одно число — наименьшее количество аппаратов, которое нужно установить, чтобы не вызвать подозрений у Министерства.
 */
/*
1)Ввод:
3
3 2
4 2
5 2
1)Вывод:
2
*/

/*
Идея:
1)Сначала запишем все это и отсортируем по времени пребывания - это то, что будет работать в строгом порядке
2)Обрабатываем по времени окончания работы
*/

//Первая попытка - неудачно
/*
int main() {
    //Количество отрезков и начало-конец
    int N, time_in, time_process;
    int count_N = 0;
    //Количество открытых точек и длина 'окрашенной части прямой'
    //int open_point = 0, len = 0;

    cin >> N;
    vector<pair<int, int>> point_mass;
    for (int i = 0; i < N; i++) {
        cin >> time_in >> time_process;
        point_mass.push_back({ time_in, time_process });
    }
    //Сортировка по первому элементу - по умолчанию
    sort(point_mass.begin(), point_mass.end());

    vector<int> mass(N, 0); //Массив с ровным количеством устройств и их время работы (по умолч. 0)  
    int i = 0;
    int flag = 0;
    int flag_finish = 0;
    //В условии цикла проверка, если i == N, то минимальное количество - это и есть максимальное количество всех устройств
    while (i != N) {
        pair<int, int>& device = point_mass[i];
        //Если одна из ячеек не пуста, но уже работает, то мы убираем ему время по-секундно 
        if (flag == 1) {
            for (int j = 0; j < N; j++) {
                if (mass[j] != 0) {
                    mass[j]--;
                }
                if (mass[j] == 0) {
                    count_N--;
                    i--;
                }
            }
        }

        //Если одна из ячеек(устройств) пуста, то даем ей работу
        if (mass[i] == 0) {
            mass[i] = device.second;
            flag = 1;
            count_N++;
            i++;
        }

        //Это проверка выполнится только тогда, когда в массиве не останется ничего
        if (flag_finish == 1 && mass.empty() == true) {
            break;
        }
    }
}*/

//Дубль 2
/*
int main() {
    int N;
    cin >> N;
    //Заносим в вектор пары 
    vector<pair<int, int>> mass(N);
    for (int i = 0; i < N; i++) {
        cin >> mass[i].first >> mass[i].second;
        mass[i].second += mass[i].first;
    }
    sort(mass.begin(), mass.end());

    //Делаем проверку 
    multiset<int> device; //Сразу сортирует данные в 'сете'
    for (int i = 0; i < mass.size(); i++) {
        pair<int, int>& point = mass[i];
        
        if(!device.empty() && *device.begin() <= point.first) {
            device.erase(device.begin()); // Удаляем начальное время из 'сета' и добавляем новое время
        }
        device.insert(point.second); //Добавляем в 'сет'
    }

    cout << device.size() << '\n';
    return 0;
}*/

//Пещера 
/*
В пещере на Марсе необходимо проложить канал для связи между поселениями. 
За миллионы лет на потолке пещеры выросли сталактиты, а на полу - сталагмиты. Чтобы проложить канал связи, нужно пробить на некоторой высоте эти образования. 
Высота туннеля для канала равна 1.

Напишите программу, вычисляющую минимальное количество сталактитов и сталагмитов, которые нужно пробить при прокладке канала.

Первая строка ввода содержит два целых числа - высота пещеры H (2<=H<=500000) и количество сталактитов и сталагмитов N (1<=N<=500000). 
Вторая строка ввода содержит N целых чисел - длины сталактитов от 1 до H−1. 
Третья строка ввода содержит N целых чисел - длины сталагмитов от 1 до H−1.

Вывести два целых числа - минимальное количество пробиваемых при прокладке канала сталактитов и сталагмитов и количество уровней (целых значений высот), на которых данный минимум достигается.
Пример ввода:
5 7
3 2 4 4 3 2 3
1 4 2 3 3 3 3

Пример вывода:
7 2
*/

//Первая попытка - неудачна
/*
int main() {
    int H, N, count = 0;
    int max_stalaktits = 0, max_stalagmits = 0;
    cin >> H >> N;
    vector<int> mass_count(N);
    vector<int> stalaktits(N), stalagmits(N);
    for (int i = 0; i < N; i++) {
        cin >> stalaktits[i];
    }
    for (int j = 0; j < N; j++) {
        cin >> stalagmits[j];
    }
    //Остортируем оба вектора для нахождения максимальной высоты сталактита и сталагмита
    sort(stalaktits.begin(), stalaktits.end());
    sort(stalagmits.begin(), stalagmits.end());
    max_stalaktits = stalaktits[N - 1];
    max_stalagmits = stalagmits[N - 1];

    //max_stalaktits = *(max_element(stalaktits.begin(), stalaktits.end()));
    //max_stalagmits = *(max_element(stalagmits.begin(), stalagmits.end()));

    for (int level = 0; level < H; level++) {
        //Гарантируется, что количество сталактитов и сталагмитов не менее 1 и высота пещеры не менее 2
        //Проверяем в массиве сталагмитов, что максимальная высота совпадала с условием, то делаем -1, что означает, как пробили этот камень
        if (H == max_stalagmits) {
            H--; //Понижаем уровень
            int i = 0;
            while (H == max_stalagmits && i != N - 1) {
                if (stalagmits[i] == H) {
                    stalagmits[i]--;
                    i++;
                    count++;
                }
                else {
                    break;
                }
            }
        }

        if (max_stalaktits != 0) {
            H--; //Понижаем уровень
            int i = 0;
            while (max_stalaktits <= H && i != N - 1) {
                if (max_stalaktits == 0) break;
                else {
                    stalaktits[i]--;
                    i++;
                    count++;
                }
            }
        }
    }

    cout << count << '\n';
    return 0;
}*/

//Вторая попытка - нет
//Важно, что нужно изобразить этот процесс на бумаге и станет ясно
/*
int main() {
    int H, N;
    cin >> H >> N;
    int min_stounes = N * 2, level = 0;
    //В векторах будем хранить количество встречающихся сталактитов и сталагмитов в 5 уровнях
    vector<int> stalaktits(H), stalagmits(H);
    //Для сталактита
    for (int i = 0; i < N; i++) {
        int chislo;
        cin >> chislo;
        stalaktits[chislo]++;
    }

    //Для сталагмита
    for (int i = 0; i < N; i++) {
        int chislo;
        cin >> chislo;
        stalagmits[chislo]++;
    }

    //Потом мы должны накопить количество встречающихся сталактитов и сталагмитов
    for (int i = 1; i < H; i++) {
        stalaktits[i] += stalaktits[i - 1];
    }
    for (int i = H - 2; i >= 0; i--) {
        stalagmits[i] += stalagmits[i + 1];
    }

    //Здесь мы должны проверять на минимальное бурение камней и количество уровней
    for (int i = 0; i < H; i++) {
        //Обязательно должны сложить количество сталактитов и сталагмитов
        int stounes = stalaktits[i] + stalagmits[i];
        if (stounes < min_stounes) {
            min_stounes = stounes;
            level = 1;
        }
        else if(stounes == min_stounes){
            level++;
        }
    }

    cout << min_stounes << ' ' << level << '\n';
    return 0;
}*/

//Разбор этого задания преподавателем
/*
bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first != b.first) {
        return a.first < b.first;
    }
    return a.second > b.second;
}

int main() {
    int h, n, t;
    cin >> h >> n;
    int cnt = n, mincnt = 1e9, levels = 0;
    vector<pair<int, int>> events(2 * n + 2);

    for (int i = 0; i < n; i++) {
        cin >> t;
        events[i].first = h - t;
        events[i].second = 1;
    }
    for (int i = 0; i < n; i++) {
        cin >> t;
        events[n + i].first = t;
        events[n + i].second = -1;
    }
    events[2 * n].first = 0;
    events[2 * n].second = 1;
    events[2 * n + 1].first = h;
    events[2 * n + 1].second = -1;
    sort(events.begin(), events.end(), cmp);

    for (size_t i = 0; i < events.size() - 1; i++) {
        cnt += events[i].second;

        if (cnt < mincnt) {
            mincnt = cnt;
            levels = events[i + 1].first - events[i].first;
        }
        else if (cnt == mincnt) {
            levels += events[i + 1].first - events[i].first;
        }
    }
    cout << (mincnt - 1) << ' ' << levels << '\n';
    return 0;
}*/

//Интервалы - разобрать!
/*
Дан набор из N целых чисел a_1, …, a_N. 
Найти минимальную длину интервала L, для которой можно найти N целых чисел x1, …, xN таких, что каждый интервал [ x_i, x_i + L ] содержит не менее K точек из набора a_1, …, a_N, в том числе a_i.
Первая строка ввода содержит два целых числа N и K (1 ≤ K ≤ N ≤ 2⋅10^5). 
Вторая строка содержит N целых чисел a1, …. aN (−10^9 ≤ ai ≤ 10^9).
Вывести одно целое число – минимальную длину интервала L.
Пример ввода
5 3
1 -2 10 5 4
Вывод для примера
6
*/
/*
int main() {
    int n, k, res = -1;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    multiset<int> lens;

    for (int i = 0; i < n; i++) {
        int right = i + k - 1;
        if (right < n) {
            lens.insert(a[right] - a[i]);
        }
        int left = i - k;
        if (left >= 0) {
            lens.erase(lens.find(a[i - 1] - a[left]));
        }
        res = max(res, *lens.begin());
    }
    cout << res;
    return 0;
}*/

//Задача на тему "Двух указателей"
//Борода - разобрать!
/*
Заметив, что Хоттабыч помогает команде «Шайба», Волька выхватил у одного из болельщиков стакан с боржомом и выплеснул на бороду джинна. 
Предположим, что в бороде Хоттабыча растут волоски разного типа и для управления перемещением нужен определенный набор волосков.

Напишите программу, которая определяет, какую минимальную по длине непрерывную подпоследовательность волосков должен был намочить Волька, чтобы Хоттабыч не мог найти сухих волосков из набора, необходимых для управления перемещением.

Первая строка ввода содержит последовательность длиной от 1 до 100000 из строчных латинских букв – перечисление типов волосков в бороде Хоттабыча слева направо. 
Каждая буква соответствует некоторому типу волоска. 
Вторая строка ввода содержит последовательность длиной от 1 до 1000 из строчных латинских букв – набор волосков для управления перемещением. 
Порядок букв в этом наборе является несущественным, важно только количество.

Вывести два целых числа – минимальную длину подпоследовательности, которую нужно намочить, и позицию, с которой нужно начать. 
Нумерация волосков в бороде начинается с 1. 
Если есть несколько вариантов с минимальной длиной, то можно вывести любой из них.
*/
const int alp_size = 26;

bool can(const vector<int>& exist, const vector<int>& required) {
    for (int i = 0; i < alp_size; i++) {
        if (exist[i] < required[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    string s, p;
    cin >> s >> p;
    vector<int> exist(alp_size), required(alp_size);
    for (int i = 0; i < (int)s.length(); i++) {
        exist[s[i] - 'a']++;
    }
    for (int i = 0; i < (int)p.length(); i++) {
        required[p[i] - 'a']++;
    }

    if (!can(exist, required)) {
        cout << "0 1\n";
        return 0;
    }
    int right = 0, minlen = s.length(), minleft = -1;
    //segment is[left; right]
    for (int left = 0; left < (int)s.length(); left++) {
        while (right < (int)s.length() && can(exist, required)) {
            exist[s[right] - 'a']--;
            right++;
        }
        
        //last
        if (can(exist, required)) {
            continue;
        }

        int len = right - left;
        if (len <= minlen) {
            minlen = len;
            minleft = left;
        }
        exist[s[left] - 'a']++;
    }
    cout << minlen << ' ' << (minleft + 1);
    return 0;
}