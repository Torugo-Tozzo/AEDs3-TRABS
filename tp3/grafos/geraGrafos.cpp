#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Seed para geração de números aleatórios
    srand(time(0));

    for (int i = 1; i <= 10; ++i) {
        // Nome do arquivo
        string filename = "grafo" + to_string(i) + ".txt";

        // Abre o arquivo para escrita
        ofstream outfile(filename);

        // Número aleatório de vértices entre 25 e 75
        int num_vertices = rand() % 51 + 25;

        // Número aleatório de arestas para cada vértice entre 2 e 6
        vector<vector<pair<int, int>>> lista_adjacencia(num_vertices);

        for (int j = 0; j < num_vertices; ++j) {
            int num_arestas = rand() % 5 + 2;

            for (int k = 0; k < num_arestas; ++k) {
                int vertice_destino = rand() % num_vertices;
                int peso = rand() % 10 + 1;
                lista_adjacencia[j].push_back({vertice_destino, peso});
            }
        }

        // Escreve o número de vértices no arquivo
        outfile << num_vertices << endl;

        // Escreve a lista de adjacência no arquivo
        for (int j = 0; j < num_vertices; ++j) {
            for (auto& aresta : lista_adjacencia[j]) {
                outfile << j << " " << aresta.first << " " << aresta.second << endl;
            }
        }

        // Fecha o arquivo
        outfile.close();
    }

    cout << "Arquivos gerados com sucesso!" << endl;

    return 0;
}
