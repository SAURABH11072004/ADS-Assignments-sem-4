#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define V 5 // Number of departments

class KruskalMST {
private:
    vector<vector<int>> edges; // Stores {weight, u, v}

public:
    // Constructor to initialize the graph from adjacency matrix
    KruskalMST(int inputGraph[V][V]) {
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (inputGraph[i][j] != 0) {
                    edges.push_back({inputGraph[i][j], i, j});
                }
            }
        }
    }

    // Find function for Disjoint Set
    int find(vector<int> &parent, int i) {
        if (parent[i] == -1) return i;
        return parent[i] = find(parent, parent[i]);
    }

    // Union function for Disjoint Set
    void unionSet(vector<int> &parent, vector<int> &rank, int u, int v) {
        int rootU = find(parent, u);
        int rootV = find(parent, v);
        
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

    // Function to find the Minimum Spanning Tree (MST) using Kruskal's Algorithm
   void findMST() {
    sort(edges.begin(), edges.end());
    vector<int> parent(V, -1);
    vector<int> rank(V, 0);
    
    vector<vector<int>> mst; // Store {u, v, weight}
    int totalDistance = 0;

    for (auto &edge : edges) {
        int weight = edge[0], u = edge[1], v = edge[2];
        if (find(parent, u) != find(parent, v)) {
            unionSet(parent, rank, u, v);
            mst.push_back({u, v, weight}); // Include weight
            totalDistance += weight;
        }
    }

    // Print MST with correct weights
    cout << "Minimum Spanning Tree (MST) of College Campus:\n";
    for (auto &e : mst) {
        cout << "Dept " << e[0] << " - Dept " << e[1] 
             << "  Distance: " << e[2] << " meters\n";
    }
    cout << "Total Minimum Distance: " << totalDistance << " meters\n";
}
};

int main() {
    // Given adjacency matrix
    int inputGraph[V][V] = {
      { 0, 2, 0, 6, 0 },
{ 2, 0, 3, 8, 5 },
{ 0, 3, 0, 0, 7 },
{ 6, 8, 0, 0, 9 },
{ 0, 5, 7, 9, 0 } // MECH
    };

    KruskalMST campus(inputGraph);
    campus.findMST();

    return 0;
}
