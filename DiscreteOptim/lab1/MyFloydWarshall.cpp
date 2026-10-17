#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

const int INF = 1e9;

void floydWarshall(vector<vector<int>>& dist, const vector<string>& labels) {
    int n = dist.size();
   
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    cout << setw(5) << " ";
    for (int i = 0; i < n; ++i) {
        cout << setw(5) << labels[i];
    }
    cout << "\n";

    for (int i = 0; i < n; ++i) {
        cout << setw(5) << labels[i];
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {
                cout << setw(5) << "INF";
            } else {
                cout << setw(5) << dist[i][j];
            }
        }
        cout << "\n";
    }
}

int main() {
    cout << "Результат для Графа 1 \n";
    vector<string> labels1 = {"V1", "V2", "V3", "V4", "V5"};
    
    vector<vector<int>> graph1 = {
        {  0,   5, INF, INF, INF}, 
        {INF,   0,   1, INF, INF}, 
        {INF, INF,   0,   3, INF}, 
        {  3,   6, INF,   0, INF}, 
        {  9, INF,   1,   5,   0}  
    };

    floydWarshall(graph1, labels1);

    cout << "\n" << string(35, '-') << "\n\n";

    cout << "Результат для Графа 2 \n";
    vector<string> labels2 = {"A", "B", "C", "D", "E"};

    vector<vector<int>> graph2 = {
        {  0, INF, INF,   2, INF},
        {  1,   0,   2, INF, INF}, 
        {  5, INF,   0,   3, INF}, 
        {INF, INF,   1,   0,   5}, 
        {  3, INF, INF, INF,   0}
    };

    floydWarshall(graph2, labels2);

    return 0;
}