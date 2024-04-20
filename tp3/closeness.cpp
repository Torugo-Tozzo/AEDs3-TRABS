#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include <iomanip>

using namespace std;

const double INF = numeric_limits<double>::max();

int minDistance(const vector<double>& dist, const vector<bool>& sptSet) {
    double minDist = INF;
    int minIndex = -1;
    for (size_t v = 0; v < dist.size(); ++v) {
        if (!sptSet[v] && dist[v] <= minDist) {
            minDist = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

vector<double> dijkstraDistances(const vector<vector<int>>& graph, int source) {
    int V = graph.size();
    vector<double> dist(V, INF);
    vector<bool> sptSet(V, false);
    dist[source] = 0.0;

    for (int count = 0; count < V - 1; ++count) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; ++v) {
            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    return dist;
}

double closenessCentrality(const vector<vector<int>>& graph, int vertex) {
    int V = graph.size();
    vector<double> distances = dijkstraDistances(graph, vertex);

    double total_distance = 0.0;
    int reachable_vertices = 0;
    for (double dist : distances) {
        if (dist != INF) {
            total_distance += dist;
            reachable_vertices++;
        }
    }
    
    // Evitar divisão por zero
    return (reachable_vertices > 1) ? (reachable_vertices - 1) / total_distance : 0;
}

int main() {
    ifstream inFile("grafo_aleatorio_adjacencia.txt");
    int num_vertices;
    inFile >> num_vertices;

    vector<vector<int>> graph(num_vertices, vector<int>(num_vertices, 0));
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            inFile >> graph[i][j];
        }
    }
    inFile.close();

    vector<double> centralities(num_vertices);
    for (int i = 0; i < num_vertices; ++i) {
        centralities[i] = closenessCentrality(graph, i);
    }

    // Escrever as centralidades em um arquivo de texto para o script Python
    ofstream outFile("centralidades.txt");
    for (int i = 0; i < num_vertices; ++i) {
        outFile << i << " " << scientific << setprecision(10) << centralities[i] << endl;
    }
    outFile.close();

    return 0;
}