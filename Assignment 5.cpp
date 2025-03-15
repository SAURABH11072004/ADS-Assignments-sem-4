#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define V 6 // Number of supply chain locations
#define INF INT_MAX

class DijkstraSCM {
private:
    vector<vector<int>> graph;
    vector<string> locationNames; // Stores names of locations

public:
    // Constructor to initialize the supply chain graph and location names
    DijkstraSCM(vector<vector<int>> &inputGraph, vector<string> names) {
        graph = inputGraph;
        locationNames = names;
    }

    // Function to find the vertex with the minimum distance value
    int findMinDistance(vector<int> &dist, vector<bool> &visited) {
        int minValue = INF, minIndex = -1;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < minValue) {
                minValue = dist[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    // Dijkstra's Algorithm to find the shortest transportation path
    void findShortestPath(int src) {
        vector<int> dist(V, INF);
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);

        dist[src] = 0; // Distance to itself is zero

        for (int count = 0; count < V - 1; count++) {
            int u = findMinDistance(dist, visited);
            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (!visited[v] && graph[u][v] && dist[u] != INF && (dist[u] + graph[u][v] < dist[v])) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }

        // Print the shortest path results with names
        cout << "Shortest Transportation Path from Source (" << locationNames[src] << "):\n";
        for (int i = 0; i < V; i++) {
            cout << "To " << locationNames[i] << " - Distance: " << dist[i] << " | Path: ";
            int temp = i;
            vector<string> path;
            while (temp != -1) {
                path.push_back(locationNames[temp]);
                temp = parent[temp];
            }
            for (int j = path.size() - 1; j >= 0; j--) {
                cout << path[j] << (j > 0 ? " -> " : "\n");
            }
        }
    }
};

int main() {
    // Adjacency matrix representing transportation costs between locations
    vector<vector<int>> supplyChainGraph = {
        {0, 10, 0, 30, 100, 0}, // Supplier
        {10, 0, 50, 0, 0, 20},  // Warehouse
        {0, 50, 0, 20, 10, 0},  // Distribution Center 1
        {30, 0, 20, 0, 60, 0},  // Distribution Center 2
        {100, 0, 10, 60, 0, 50},// Retail Store 1
        {0, 20, 0, 0, 50, 0}    // Retail Store 2
    };

    // Names corresponding to locations
    vector<string> locationNames = {
        "Supplier", "Warehouse", "Distribution Center 1", 
        "Distribution Center 2", "Retail Store 1", "Retail Store 2"
    };

    DijkstraSCM scm(supplyChainGraph, locationNames);
    int source = 0; // Start from "Supplier"
    scm.findShortestPath(source);

    return 0;
}
