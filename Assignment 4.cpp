#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INF INT_MAX
#define V 5 // Number of departments

class PrimMST {
private:
    int graph[V][V]; // Adjacency matrix

public:
    // Constructor to initialize the graph
    PrimMST(int inputGraph[V][V]) {
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                graph[i][j] = inputGraph[i][j];
    }

    // Function to find the vertex with minimum key value
    int findMinKey(vector<int> &key, vector<bool> &inMST) {
        int minValue = INF, minIndex = -1;
        for (int i = 0; i < V; i++) {
            if (!inMST[i] && key[i] < minValue) {
                minValue = key[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    // Function to find the Minimum Spanning Tree (MST) using Prim's Algorithm
    void findMST() {
        vector<int> parent(V, -1);   // Stores MST edges
        vector<int> key(V, INF);     // Stores minimum weight to reach a vertex
        vector<bool> inMST(V, false); // Tracks if a vertex is in MST

        key[0] = 0; // Start from department 0 (CS)

        for (int count = 0; count < V - 1; count++) {
            int u = findMinKey(key, inMST);
            inMST[u] = true;

            for (int v = 0; v < V; v++) {
                if (graph[u][v] != 0 && !inMST[v] && graph[u][v] < key[v]) {
                    key[v] = graph[u][v];
                    parent[v] = u;
                }
            }
        }

        // Print MST
        cout << "Minimum Spanning Tree (MST) of College Campus:\n";
        int totalDistance = 0;
        for (int i = 1; i < V; i++) {
            cout << "Dept " << parent[i] << " - Dept " << i << "  Distance: " << graph[parent[i]][i] << " meters\n";
            totalDistance += graph[parent[i]][i];
        }
        cout << "Total Minimum Distance to Connect All Departments: " << totalDistance << " meters\n";
    }
};

int main() {
    // Given adjacency matrix
    int inputGraph[V][V] = {
        {  0, 50, 80,  0,  0 }, // CS
        { 50,  0, 30, 60,  0 }, // IT
        { 80, 30,  0, 40, 70 }, // ENTC
        {  0, 60, 40,  0, 20 }, // AIML
        {  0,  0, 70, 20,  0 }  // MECH
    };

    PrimMST campus(inputGraph);
    campus.findMST();

    return 0;
}
