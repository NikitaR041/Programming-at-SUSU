Перед тем как собрать и запустить программу
Необходимо:
1)Сохранить 7 файлов в одном папке
2)Достать из архива bottuns папку buttons с фотографиями
3)Достать из архива библиотеку winbgim
#include <iostream>
#include <cmath>
using namespace std;

/*
Задача 1 - Крутые числа
Стэну нравятся числа, которые одновременно являются кубами и квадратами. Он считает их крутыми. Например, крутым является число 64, так как 64=4^3=8^2.
Ввод содержит одно целое число X (1 ? X < 10^18).
Выведите минимальное крутое число, строго большее заданного числа X.
Пример ввода:
10
Пример вывода:
64

long long pow6(int n) {
	long long res = 1;
	for (int i = 0; i < 6; ++i) {
		res *= n;
	}
	return res;
}

int main()
{
	long long x;
	int i = 1;
	cin >> x;
	while (true) {
		if (pow6(i) > x) {
			cout << pow6(i) << '\n';
			break;
		}
		i++;
	}
}*/

/*
Задача 4 - Арифметические операции
Дано 4 положительных целых числа. Вычислите количество способов расставить между этими числами знаки арифметических операций (+, -, *, /) таким образом, чтобы значение получившегося выражения стало равно 0. 
Операции в выражении выполняются слева направо, независимо от их приоритета. 
Операция / вычисляется как целая часть частного от деления, т.е. как div в языке Pascal.
Например, если даны числа 1 3 5 8, то ноль можно получить, расставив знаки так "1*3+5-8" или так "1-3+5/8".
Первая строка содержит 4 целых числа в диапазоне от 1 до 200.
Вывести количество способов расставить знаки операций для получения выражения равного 0.
Пример ввода: 1 3 5 8
Пример вывода: 17

Удобно использовать switch!!!
*/
int operation_arithm(int x1, int x2, int x3, int x4, char symb_1, char symb_2, char symb_3) {
	int finish = 0;
	switch (symb_1) {
	case '+': { 
		finish = x1 + x2; 
		break; 
	}
	case '-': {
		finish = x1 - x2;
		break;
	}
	case '*': {
		finish = x1 * x2;
		break;
	}
	case '/': {
		finish = x1 / x2;
		break;
	}
	}

	switch (symb_2) {
	case '+': {
		finish = finish + x3;
		break;
	}
	case '-': {
		finish = finish - x3;
		break;
	}
	case '*': {
		finish = finish * x3;
		break;
	}
	case '/': {
		finish = finish / x3;
		break;
	}
	}

	switch (symb_3) {
	case '+': {
		finish = finish + x4;
		break;
	}
	case '-': {
		finish = finish - x4;
		break;
	}
	case '*': {
		finish = finish * x4;
		break;
	}
	case '/': {
		finish = finish / x4;
		break;
	}
	}
	return finish;
}

int main() {
	int g_count = 0;
	char arithm[4] = { '+', '-', '*', '/' };
	int x1, x2, x3, x4;
	cin >> x1 >> x2 >> x3 >> x4;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int g = 0; g < 4; g++) {
				if (operation_arithm(x1, x2, x3, x4, arithm[i], arithm[j], arithm[g]) == 0) {
					g_count++;
					//Без break, т.к. может быть так, что с другим арифметическим знаком, может получится ответ!
				}
			}
		}
	}
	cout << g_count << '\n';
	return 0;
}
