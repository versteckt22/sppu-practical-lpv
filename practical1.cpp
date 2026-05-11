#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

int graph[10][10];
bool visited[10];
int nodes = 7;

// Parallel BFS
void parallelBFS(int start) {

    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "Parallel BFS: ";

    while (!q.empty()) {

        int node = q.front();
        q.pop();

        cout << node << " ";

        #pragma omp parallel for
        for (int i = 0; i < nodes; i++) {

            if (graph[node][i] == 1 && !visited[i]) {

                visited[i] = true;

                #pragma omp critical
                q.push(i);
            }
        }
    }

    cout << endl;
}

// Parallel DFS
void parallelDFS(int node) {

    visited[node] = true;

    cout << node << " ";

    #pragma omp parallel for
    for (int i = 0; i < nodes; i++) {

        if (graph[node][i] == 1 && !visited[i]) {
            parallelDFS(i);
        }
    }
}

int main() {

    // Tree / Undirected Graph

    graph[0][1] = 1;
    graph[0][2] = 1;

    graph[1][3] = 1;
    graph[1][4] = 1;

    graph[2][5] = 1;
    graph[2][6] = 1;

    // Since undirected graph

    graph[1][0] = 1;
    graph[2][0] = 1;

    graph[3][1] = 1;
    graph[4][1] = 1;

    graph[5][2] = 1;
    graph[6][2] = 1;

    // BFS
    parallelBFS(0);

    // Reset visited array
    for (int i = 0; i < 10; i++)
        visited[i] = false;

    // DFS
    cout << "Parallel DFS: ";
    parallelDFS(0);

    return 0;
}
