#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Class representing a Maze Graph and its traversal algorithms
class MazeGraph {
private:
    vector<vector<int>> G;  // Adjacency matrix representation of the maze
    int n;                  // Number of nodes

public:
    // Constructor to initialize the maze graph
    MazeGraph(vector<vector<int>> graph) {
        G = graph;
        n = graph.size();
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
    void DFS(int start, vector<int> &visited) {
        if (visited[start] == 0) {
            cout << start << " ";
            visited[start] = 1;

            for (int j = 1; j < n; j++) {
                if (G[start][j] == 1 && visited[j] == 0) {
                    DFS(j, visited);
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

    // Creating an object of MazeGraph
    MazeGraph maze(G);

    // Performing DFS and BFS traversals
    maze.startDFS(4);
    maze.BFS(4);

    return 0;
}
