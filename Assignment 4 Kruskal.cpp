#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define V 5 // Number of departments

class KruskalMST {
private:
    vector<vector<int>> edges; // Stores {weight, u, v}
    vector<string> departments; // Stores department names

public:
    // Constructor to initialize the graph from adjacency matrix
    KruskalMST(int inputGraph[V][V], vector<string> deptNames) {
        departments = deptNames; // Assign department names
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                if (inputGraph[i][j] != 0) {
                    edges.push_back({inputGraph[i][j], i, j});
                }
            }
        }
    }

    // Find function for Disjoint Set
    int find(vector<int>& parent, int i) {
        if (parent[i] == -1) return i;
        return parent[i] = find(parent, parent[i]);
    }

    // Union function for Disjoint Set
    void unionSet(vector<int>& parent, vector<int>& rank, int u, int v) {
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
        sort(edges.begin(), edges.end()); // Sort edges by weight (first element)
        vector<int> parent(V, -1);
        vector<int> rank(V, 0);
        
        vector<vector<int>> mst; // Store {u, v, weight}
        int totalDistance = 0;

        for (int i = 0; i < edges.size(); ++i) {
            int weight = edges[i][0];
            int u = edges[i][1];
            int v = edges[i][2];

            if (find(parent, u) != find(parent, v)) {
                unionSet(parent, rank, u, v);
                mst.push_back({u, v, weight});
                totalDistance += weight;
            }
        }

        // Print MST with department names
        cout << "Minimum Spanning Tree (MST) of College Campus:\n";
        for (int i = 0; i < mst.size(); ++i) {
            cout << departments[mst[i][0]] << " - " << departments[mst[i][1]] 
                 << "  Distance: " << mst[i][2] << " meters\n";
        }
        cout << "Total Minimum Distance: " << totalDistance << " meters\n";
    }
};

int main() {
    // Given adjacency matrix
    int inputGraph[V][V] = {
        { 0, 2, 0, 6, 0 },  // CS
        { 2, 0, 3, 8, 5 },  // IT
        { 0, 3, 0, 0, 7 },  // ENTC
        { 6, 8, 0, 0, 9 },  // AIML
        { 0, 5, 7, 9, 0 }   // MECH
    };

    // Department names
    vector<string> departments = {"CS", "IT", "ENTC", "AIML", "MECH"};

    KruskalMST campus(inputGraph, departments);
    campus.findMST();

    return 0;
}
