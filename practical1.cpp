#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:

    Graph(int vertices) {
        V = vertices;
        adj.resize(V);
    }

    // Add edge for undirected graph / tree
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Parallel BFS
    void parallelBFS(int start) {

        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "\nParallel BFS Traversal:\n";

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            cout << node << " ";

            // Parallel processing of neighbors
            #pragma omp parallel for
            for (int i = 0; i < adj[node].size(); i++) {

                int neighbor = adj[node][i];

                if (!visited[neighbor]) {

                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }

        cout << endl;
    }

    // Parallel DFS Utility
    void parallelDFSUtil(int node, vector<bool>& visited) {

        visited[node] = true;

        #pragma omp critical
        cout << node << " ";

        // Parallel exploration of neighbors
        #pragma omp parallel for
        for (int i = 0; i < adj[node].size(); i++) {

            int neighbor = adj[node][i];

            if (!visited[neighbor]) {
                parallelDFSUtil(neighbor, visited);
            }
        }
    }

    // Parallel DFS
    void parallelDFS(int start) {

        vector<bool> visited(V, false);

        cout << "\nParallel DFS Traversal:\n";

        parallelDFSUtil(start, visited);

        cout << endl;
    }
};

int main() {

    // Example Tree / Undirected Graph

    Graph g(7);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    // BFS
    g.parallelBFS(0);

    // DFS
    g.parallelDFS(0);

    return 0;
}
