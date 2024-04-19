#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

// Definição de um grafo ponderado como lista de adjacência de pares (vértice destino, peso da aresta)
typedef vector<vector<pair<int, int>>> WeightedGraph;

// Função para calcular as distâncias de todos os vértices a partir de um vértice fonte usando o algoritmo de Dijkstra
vector<int> dijkstra_distances(const WeightedGraph& graph, int source) {
    int num_vertices = graph.size();
    vector<int> distances(num_vertices, numeric_limits<int>::max()); // Inicializa todas as distâncias como infinito
    distances[source] = 0; // A distância do vértice fonte a ele mesmo é 0
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Fila de prioridade para armazenar os vértices a serem visitados
    pq.push({0, source});
    while (!pq.empty()) {
        int current_vertex = pq.top().second;
        int current_distance = pq.top().first;
        pq.pop();
        if (current_distance > distances[current_vertex]) continue; // Se a distância atual for maior que a armazenada, ignore
        for (auto& edge : graph[current_vertex]) {
            int neighbor = edge.first;
            int weight = edge.second;
            int new_distance = current_distance + weight;
            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                pq.push({new_distance, neighbor});
            }
        }
    }
    return distances;
}

// Função para calcular a closeness centrality de um vértice em um grafo ponderado
double closeness_centrality(const WeightedGraph& graph, int vertex) {
    int num_vertices = graph.size();
    double total_distance = 0;
    // Calcula as distâncias de todos os vértices a partir do vértice atual usando Dijkstra
    vector<int> distances = dijkstra_distances(graph, vertex);
    // Soma todas as distâncias encontradas
    for (int dist : distances) {
        total_distance += dist;
    }
    // Retorna o inverso da soma das distâncias como closeness centrality
    return 1.0 / total_distance;
}

int main() {
    // Exemplo de uso
    int num_vertices = 5;
    WeightedGraph g(num_vertices);

    // Adiciona arestas ao grafo (exemplo)
    g[0] = {{1, 2}, {2, 3}, {3, 4}};
    g[1] = {{0, 2}, {4, 1}};
    g[2] = {{0, 3}, {4, 2}};
    g[3] = {{0, 4}};
    g[4] = {{1, 1}, {2, 2}};

    // Calcula a closeness centrality para todos os vértices
    for (int i = 0; i < num_vertices; ++i) {
        cout << "Closeness Centrality of vertex " << i << ": " << closeness_centrality(g, i) << endl;
    }

    return 0;
}