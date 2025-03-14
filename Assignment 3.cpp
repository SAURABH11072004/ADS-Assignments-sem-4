#include <iostream>
#include <vector>
#include <queue>
using namespace std;
// Function to perform BFS traversal in the maze graph
void BFS(vector<vector<int>> &G, int start, int n) {
    vector<int> visited(n, 0);
    queue<int> Q;

    cout << "BFS Traversal from " << start << ": ";
    cout << start << " ";
    visited[start] = 1;
    Q.push(start);

    while (!Q.empty()) {
        int i = Q.front();
        Q.pop();

        for (int j = 1; j < n; j++) {
            if (G[i][j] == 1 && visited[j] == 0) {
                cout << j << " ";
                visited[j] = 1;
                Q.push(j);
            }
        }
    }
    cout << endl;
}

// Function to perform DFS traversal in the maze graph
void DFS(vector<vector<int>> &G, int start, int n, vector<int> &visited) {
    if (visited[start] == 0) {
        cout << start << " ";
        visited[start] = 1;

        for (int j = 1; j < n; j++) {
            if (G[start][j] == 1 && visited[j] == 0) {
                DFS(G, j, n, visited);
            }
        }
    }
}

int main() {
    // Graph representation of a sample maze (0 = no path, 1 = path exists)
    vector<vector<int>> G = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0}
    };

    cout << "DFS Traversal from 4: ";
    vector<int> visited(7, 0);
    DFS(G, 4, 7, visited);
    cout << endl;

    BFS(G, 4, 7);

    return 0;
}
