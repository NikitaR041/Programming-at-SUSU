#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

//Удаление клеток
/*
Из прямоугольного листа клетчатой бумаги (M строк, N столбцов) удалили некоторые клетки. На сколько кусков распадётся оставшаяся часть листа? 
Две клетки не распадаются, если они имеют общую сторону.
Ограничения: 1 ≤ M, N ≤ 100.
Ввод
В первой строке находятся числа M и N, в следующих M строках – по N символов. Е
сли клетка не была вырезана, этому соответствует знак #, если вырезана – точка.
Вывод
Вывести одно число.
*/
/*
Пример ввода
4 8
#.##.#.#
......##
#.###.##
##.##.##
Пример вывода
6
*/

/*
string karta[100]; //Карта рисунка
bool visit_karta[100][100]; //Карта посещенных пунктов

void dfs(int x, int y, int M, int N) {
	//Проверка на то, что вершина не попадает в вершину, иначе функция будет обработана
	if (x < 0 || x >= M || y < 0 || y >= N || karta[x][y] == '.' || visit_karta[x][y]) return;

	//Помечаем эту важную вершину, как пройденную
	visit_karta[x][y] = true;

	//И расходимся на разные ветви
	dfs(x - 1, y, M, N);
	dfs(x + 1, y, M, N);
	dfs(x, y - 1, M, N);
	dfs(x, y + 1, M, N);
}

int main() {
	int M, N;
	cin >> M >> N;

	//В цикле запишем эту картинку в карту типа string
	for (int i = 0; i < M; i++) {
		cin >> karta[i];
	}

	//Инициализируем каждую вершину false - значит не посещали
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			visit_karta[i][j] = false;
		}
	}

	int count = 0;

	//Далее делаем проверку на то, что можно посетить эту вершину
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (karta[i][j] == '#' && visit_karta[i][j] == false) {
				dfs(i, j, M, N);
				count++;
			}
		}
	}

	cout << count << '\n';
	return 0;
}*/


//Задача: Lines
/*
В таблице из N строк и N столбцов некоторые клетки заняты шариками, другие свободны. Выбран шарик, который нужно переместить, и место, куда его нужно переместить. 
Выбранный шарик за один шаг перемещается в соседнюю по горизонтали или вертикали свободную клетку. 
Требуется выяснить, возможно ли переместить шарик из начальной клетки в заданную, и, если возможно, то найти путь из наименьшего количества шагов.
Ввод
В первой строке находится число N (2 ≤ N ≤ 250), в следующих N строках – по N символов. 
Символом точки обозначена свободная клетка, латинской заглавной O – шарик, @ – исходное положение шарика, который должен двигаться, латинской заглавной X – конечное положение шарика.
Вывод
В первой строке выводится "Y", если движение возможно, или "N", если нет. Если движение возможно, далее следует N строк по N символов – как и на вводе, но буква X, а также все точки по пути заменяются плюсами.
*/
/*
char karta[250][250]; //Карта рисунка	
int visit_karta[250][250];

void min_hod(int count_vertical, int count_gorisont) {
	if (count_gorisont > count_vertical) {
			
	}
	else if (count_gorisont < count_vertical) {
	
	}
	else if (count_gorisont == count_vertical) {
	
	}
}

int main() {
	int M, N;
	int save_x = -1, save_y = -1; //Не нашли шарик '@'
	cin >> M >> N;

	//В цикле запишем эту картинку в карту типа string
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> karta[i][j];
			if (karta[i][j] == '@') {
				save_x = i;
				save_y = j;
			}
		}
	}	

	//Распознаем количество шагов до стенки
	int count_vertical = 1;
	int count_gorisont = 1;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			//Рассмотрим путь по вертикали
			if (karta[save_x - i][save_y - j] == '.') {
				count_vertical++;
			}

			//Рассмотрим путь по горизонтали
			if (karta[save_x - i][save_y - j] == '.') {
				count_gorisont++;
			}
		}
	}


	int count = 0;
	//Далее делаем проверку на то, что можно посетить эту вершину
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (karta[i][j] == '#' && visit_karta[i][j] == false) {
				dfs(i, j, M, N);
				count++;
			}
		}
	}
}
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct P {
	int x, y;
};

const vector<int> dx = { 0, 0, 1, -1 };
const vector<int> dy = { 1, -1, 0, 0 };

bool IV(int x, int y, int n, vector<vector<char>>& a, vector<vector<bool>>& v) {
	return x >= 0 && x < n && y >= 0 && y < n && a[x][y] != 'O' && !v[x][y];
}

void bfs(int startX, int startY, int endx, int endy, int n, vector<vector<char>>& a, vector<vector<int>>& dist, vector<vector<P>>& par, vector<vector<bool>>& v) {
	queue<P> q;
	q.push({ startX, startY });
	dist[startX][startY] = 0;
	v[startX][startY] = true;

	while (!q.empty()) {
		P c = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i) {
			int nx = c.x + dx[i];
			int ny = c.y + dy[i];

			if (IV(nx, ny, n, a, v)) {
				v[nx][ny] = true;
				dist[nx][ny] = dist[c.x][c.y] + 1;
				par[nx][ny] = { c.x, c.y };
				q.push({ nx, ny });

				if (nx == endx && ny == endy) return;
			}
		}
	}
}

int main() {
	int n;
	cin >> n;

	vector<vector<char>> a(n, vector<char>(n));
	P start, end;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> a[i][j];

			if (a[i][j] == '@') start = { i, j };
			else if (a[i][j] == 'X') end = { i, j };
		}
	}

	vector<vector<int>> dist(n, vector<int>(n, -1));
	vector<vector<bool>> v(n, vector<bool>(n, false));
	vector<vector<P>> par(n, vector<P>(n, { -1, -1 }));

	bfs(start.x, start.y, end.x, end.y, n, a, dist, par, v);

	if (dist[end.x][end.y] == -1) {
		cout << "N" << endl;
	}
	else {
		cout << "Y" << endl;
		P c = end;

		while (c.x != -1 && c.y != -1) {
			a[c.x][c.y] = '+';
			c = par[c.x][c.y];
		}

		a[start.x][start.y] = '@';
		a[end.x][end.y] = '+';

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cout << a[i][j];
			}
			cout << endl;
		}
	}

	return 0;
}
