#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define INF INT_MAX

class PrimMST {
private:
    vector<vector<int>> graph; // Adjacency matrix as vector of vectors
    vector<string> departmentNames; // Department names

public:
    // Constructor to initialize graph and names
    PrimMST(vector<vector<int>>& inputGraph, vector<string>& names) {
        graph = inputGraph;
        departmentNames = names;
    }

    // Function to find vertex with minimum key value not yet in MST
    int findMinKey( vector<int>& key, vector<bool>& inMST) {
        int minValue = INF, minIndex = -1;
        for (int i = 0; i < key.size(); i++) {
            if (!inMST[i] && key[i] < minValue) {
                minValue = key[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    // Function to compute MST using Prim’s algorithm
    void findMST() {
        int V = graph.size();
        vector<int> parent(V, -1);     // Store MST edges
        vector<int> key(V, INF);       // Minimum weights
        vector<bool> inMST(V, false);  // Track visited vertices

        key[0] = 0; // Start from first department (CS)

        for (int count = 0; count < V - 1; count++) {
            int u = findMinKey(key, inMST);
            inMST[u] = true;

            for (int v = 0; v < V; v++) {
                if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }

        // Print the MST
        cout << "Minimum Spanning Tree (MST) of College Campus:\n";
        int totalDistance = 0;
        for (int i = 1; i < V; i++) {
            cout << departmentNames[parent[i]] << " - " << departmentNames[i]
                 << "  Distance: " << graph[parent[i]][i] << " meters\n";
            totalDistance += graph[parent[i]][i];
        }
        cout << "Total Minimum Distance to Connect All Departments: " << totalDistance << " meters\n";
    }
};

int main() {
    vector<vector<int>> inputGraph = {
        {  0, 50, 80,  0,  0 }, // CS
        { 50,  0, 30, 60,  0 }, // IT
        { 80, 30,  0, 40, 70 }, // ENTC
        {  0, 60, 40,  0, 20 }, // AIML
        {  0,  0, 70, 20,  0 }  // MECH
    };

    vector<string> departmentNames = {"CS", "IT", "ENTC", "AIML", "MECH"};

    PrimMST campus(inputGraph, departmentNames);
    campus.findMST();

    return 0;
}
