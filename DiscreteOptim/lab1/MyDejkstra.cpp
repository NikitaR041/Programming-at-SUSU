#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

const int INF = 1e9;

struct Edge {
    int to;
    int weight;
};

void printPath(int startNode, int endNode, const std::vector<int>& parent) {
    if (parent[endNode] == -1 && startNode != endNode) {
        std::cout << "Путь отсутствует";
        return;
    }

    std::vector<int> path;
    for (int v = endNode; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << "V" << path[i] << (i + 1 < path.size() ? " -> " : "");
    }
}

void dijkstra(int startNode, int n, const std::vector<std::vector<Edge>>& graph) {
    std::vector<int> dist(n + 1, INF);
    std::vector<int> parent(n + 1, -1);
    
    std::priority_queue<std::pair<int, int>, 
                        std::vector<std::pair<int, int>>, 
                        std::greater<std::pair<int, int>>> pq;
                        
    dist[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    std::cout << "Кратчайшие пути из верщины V" << startNode << ":\n";
    for (int i = 1; i <= n; ++i) {
        std::cout << "До V" << i << " | ";
        if (dist[i] == INF) {
            std::cout << "Недостижима\n";
        } else {
            std::cout << "Длина = " << dist[i] << " \t| Путь: ";
            printPath(startNode, i, parent);
            std::cout << "\n";
        }
    }
}

// Пример 1
   /*
   graph[1].push_back({2, 5});
    
    graph[2].push_back({3, 1});
    
    graph[3].push_back({4, 3});
    
    graph[4].push_back({1, 3});
    graph[4].push_back({2, 6});
    
    graph[5].push_back({1, 9});
    graph[5].push_back({4, 5});
    graph[5].push_back({3, 1});
   */

int main() {
   setlocale(LC_ALL, "Rus");
   int n1 = 5, start1 = 5;  
   int n2 = 5, start2 = 1;
   std::vector<std::vector<Edge>> graph1(n1 + 1);
   std::vector<std::vector<Edge>> graph2(n2 + 1);

   //Пример 1
    graph1[1].push_back({2, 5});
    
    graph1[2].push_back({3, 1});
    
    graph1[3].push_back({4, 3});
    
    graph1[4].push_back({1, 3});
    graph1[4].push_back({2, 6});
    
    graph1[5].push_back({1, 9});
    graph1[5].push_back({4, 5});
    graph1[5].push_back({3, 1});
   
   // Пример 2
    graph2[2].push_back({1, 1});
    graph2[2].push_back({3, 2});

    graph2[3].push_back({1, 5});
    graph2[3].push_back({4, 3});

    graph2[1].push_back({4, 2});

    graph2[4].push_back({5, 5});
    graph2[4].push_back({3, 1});
    graph2[4].push_back({4, 2});
    
    graph2[5].push_back({1, 3});
   
    std::cout << "Результат для Графа 1 \n";
    dijkstra(start1, n1, graph1);
        
    std::cout << "Результат для Графа 2 \n";
    dijkstra(start2, n2, graph2);

    return 0;
}