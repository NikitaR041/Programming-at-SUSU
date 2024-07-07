#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Задача: Сдача

//Задача: Слияние чисел
/*
Слить два натуральных числа в новое число, вставив цифры одного числа между цифрами другого числа, сохранив при этом порядок следования цифр в исходных числах. 
Новое число должно быть максимальным из всех возможных.
Ввод
Во входном файле содержатся две строки, в каждой строке по одному натуральному числу длиной до 100 цифр.
Вывод
В выходной файл вывести полученное при слиянии число, максимальное из возможных.
*/
/*
int main() {
	int n, m;
	char s_num[100], s_mum[100];
	



	return 0;
}*/


//Задача: Перестановка
/*
Дана строка, состоящая из прописных латинских букв. Нужно переставить буквы в строке таким образом, чтобы буквы в соответсвующих позициях исходной и новой строки не совпадали.
Ввод содержит одну строку длиной от 1 до 100000.
Вывести перестановку. Если существует несколько вариантов, то вывести первую перестановку в лексикографическом порядке из них. Если искомой перестановки не существует, то вывести сообщение "No solution" (без кавычек).

Пример ввода 1
ABBAT
Пример вывода 1
BAATB
Пример ввода 2
AABBCAA
Пример вывода 2
No solution
*/

/*
int main() {
	string s;
	string copy_s = s;
	vector<string> mass;
	cin >> s;
	do {
		mass.push_back(s);
	} while (std::next_permutation(s.begin(), s.end()));
	
	int i = 0; //Берем из элемента символ
	int j = 0; // Берем элемент
	
	for (auto elem : mass) {
		while (true) {
			if (copy_s[i] != mass[j][i]) {
				i++;
			}
			else if (copy_s[i] == mass[j][i]) {
				j++;
				break;
			}
		}
	}
	if (i == mass[j].size()) {
		cout << mass[j] << '\n';
	}
	else {
		cout << "No solution" << '\n';
	}
}
*/

/*
//Функция по-элементо считает true или false
int is_true(const string a, const string b) {
	int flag = false;
	for (int i = 0; i < b.length(); i++) {
		if (a[i] != b[i]) {
			flag = true;
		}
		else {
			flag = false;
			return false;
		}
	}
	if (flag == true) {
		return true;
	}
}

int main() {
	int count = 0;
	string s;
	vector<string> mass;
	cin >> s;
	string copy_s = s;

	do {
		mass.push_back(s);
	} while (std::next_permutation(s.begin(), s.end()));
	
	for (int i = 0; i < mass.size(); i++) {
		//Если похожий элемент
		if (copy_s == mass[i]) continue;
		//Иначе нет
		if (is_true(copy_s, mass[i]) == true) {
			cout << mass[i] << '\n';
			count++;
			break;
		}
		
	}
	if (count == 0) {
		cout << "No solution" << '\n';
	}
	return 0;
}
*/

/*
void copy_finish(string s, string copy_s, string& f) {
	int i = 0;
	int j = 0;
	while (j < copy_s.size()) {
		if (copy_s[j] != s[i]) {
			f.push_back(s[i]);
			i = 0;
			j++;
		}
		else {
			i++;
		}
	}
}

int main() {
	string s, copy_s;
	string finish;
	cin >> s;
	copy_s = s;
	sort(s.begin(), s.end());

	copy_finish(s, copy_s, finish);

	if (finish.length() == 0) {
		cout << "No solution" << '\n';
	}
	else {
		cout << finish << '\n';
	}
	return 0;
}*/


//По идеи норм задача, но не проходит по времени
/*
bool is_true(const string& original, const string& permutation) {
	for (size_t i = 0; i < original.size(); ++i) {
		if (original[i] == permutation[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	string s;
	cin >> s;
	string copy_s = s;

	// Сортируем строку в лексикографическом порядке
	sort(s.begin(), s.end());

	do {
		// Если перестановка удовлетворяет условию задачи, выводим ее и завершаем программу
		if (is_true(copy_s, s) == true) {
			cout << s << '\n';
			return 0;
		}
	} while (next_permutation(s.begin(), s.end()));

	// Если после проверки всех перестановок подходящая не найдена, выводим сообщение "No solution"
	cout << "No solution" << '\n';
	return 0;
}*/
