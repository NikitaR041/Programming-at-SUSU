#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

// Структура для представления соседа (вершина и вес ребра)
struct Neighbor {
    int to;
    int weight;
};

// Функция для поиска минимального остовного дерева алгоритмом Прима
void primMST(int V, const vector<vector<Neighbor>>& adj) {
    // Приоритетная очередь хранит кортежи: {вес, текущая_вершина, родитель}
    // Используем greater, чтобы наверху всегда был элемент с минимальным весом
    priority_queue<tuple<int, int, int>, 
                   vector<tuple<int, int, int>>, 
                   greater<tuple<int, int, int>>> pq;

    vector<bool> inMST(V, false);
    int totalWeight = 0;

    // Начинаем с вершины 0 (вес 0, вершина 0, родитель -1)
    pq.push({0, 0, -1});

    cout << "Рёбра минимального остовного дерева (МОД):\n";

    while (!pq.empty()) {
        auto [weight, u, parent] = pq.top();
        pq.pop();

        // Если вершина уже включена в дерево, пропускаем её
        if (inMST[u]) continue;

        inMST[u] = true;
        totalWeight += weight;

        // Если это не стартовая фиктивная вершина, выводим ребро
        if (parent != -1) {
            cout << parent << " - " << u << " (вес: " << weight << ")\n";
        }

        // Перебираем всех соседей текущей вершины
        for (const auto& neighbor : adj[u]) {
            if (!inMST[neighbor.to]) {
                pq.push({neighbor.weight, neighbor.to, u});
            }
        }
    }

    cout << "Общий вес остовного дерева: " << totalWeight << "\n";
}

int main() {
    // Ускорение ввода-вывода
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int V = 8; // Количество вершин (от 0 до 4)
    vector<vector<Neighbor>> adj(V);

    // Функция для добавления неориентированного ребра
    auto addEdge = [&](int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };

    // Заполняем граф тестовыми данными
// --- Заполняем граф по варианту 18 (a=1, b=4, c=6, d=4, e=2) ---

    // 1. Горизонтальные рёбра (верхний ряд: v1-v2-v3-v4)
    addEdge(0, 1, 1); // (v1, v2) -> a = 1[cite: 1]
    addEdge(1, 2, 4); // (v2, v3) -> 4[cite: 1]
    addEdge(2, 3, 4); // (v3, v4) -> b = 4[cite: 1]

    // 2. Горизонтальные рёбра (нижний ряд: v5-v6-v7-v8)
    addEdge(4, 5, 4); // (v5, v6) -> 4[cite: 1]
    addEdge(5, 6, 2); // (v6, v7) -> 2[cite: 1]
    addEdge(6, 7, 2); // (v7, v8) -> e = 2[cite: 1]

    // 3. Вертикальные рёбра
    addEdge(0, 4, 4); // (v1, v5) -> 4[cite: 1]
    addEdge(1, 5, 3); // (v2, v6) -> 3[cite: 1]
    addEdge(2, 6, 4); // (v3, v7) -> 4[cite: 1]
    addEdge(3, 7, 4); // (v4, v8) -> 4[cite: 1]

    // 4. Диагональные рёбра
    addEdge(0, 5, 3); // (v1, v6) -> 3[cite: 1]
    addEdge(1, 6, 6); // (v2, v7) -> c = 6[cite: 1]
    addEdge(2, 7, 4); // (v3, v8) -> d = 4[cite: 1]
   /*
    addEdge(0, 1, 2);
    addEdge(0, 3, 6);
    addEdge(1, 2, 3);
    addEdge(1, 3, 8);
    addEdge(1, 4, 5);
    addEdge(2, 4, 7);
    addEdge(3, 4, 9);
      */
    
    // Запускаем алгоритм Прима
    primMST(V, adj);

    return 0;
}