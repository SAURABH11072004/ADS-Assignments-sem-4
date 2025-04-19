#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Class representing a Maze Graph and its traversal algorithms
class MazeGraph {
private:
    vector<vector<int>> adj;  // Adjacency list
    int n;                    // Number of nodes

public:
    // Constructor to convert adjacency matrix to adjacency list
    MazeGraph(const vector<vector<int>>& matrix) {
        n = matrix.size();
        adj.resize(n);

        // Convert matrix to adjacency list (1-based indexing)
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 1) {
                    adj[i].push_back(j);
                }
            }
        }
    }

    // Function to perform BFS traversal in the maze graph
    void BFS(int start) {
        vector<int> visited(n, 0);
        queue<int> Q;

        cout << "BFS Traversal from " << start << ": ";
        cout << start << " ";
        visited[start] = 1;
        Q.push(start);

        while (!Q.empty()) {
            int i = Q.front();
            Q.pop();

            for (int neighbor : adj[i]) {
                if (!visited[neighbor]) {
                    cout << neighbor << " ";
                    visited[neighbor] = 1;
                    Q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Function to perform DFS traversal in the maze graph
    void DFS(int start, vector<int>& visited) {
        if (!visited[start]) {
            cout << start << " ";
            visited[start] = 1;

            for (int neighbor : adj[start]) {
                if (!visited[neighbor]) {
                    DFS(neighbor, visited);
                }
            }
        }
    }

    // Helper function to start DFS with fresh visited array
    void startDFS(int start) {
        vector<int> visited(n, 0);
        cout << "DFS Traversal from " << start << ": ";
        DFS(start, visited);
        cout << endl;
    }
};

int main() {
    // Graph represented as adjacency matrix (1-based, with row 0 and col 0 unused)
    vector<vector<int>> G = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0}
    };

    // Creating an object of MazeGraph
    MazeGraph maze(G);

    // Performing DFS and BFS traversals
    maze.startDFS(4);
    maze.BFS(4);

    return 0;
}
