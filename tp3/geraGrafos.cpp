#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

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

        // Escreve o número de vértices no arquivo
        outfile << num_vertices << endl;

        // Lista de vértices
        vector<int> vertices(num_vertices);
        for (int j = 0; j < num_vertices; ++j) {
            vertices[j] = j;
        }

        // Embaralha a lista de vértices
        random_shuffle(vertices.begin(), vertices.end());

        // Gera o grafo aleatório com pesos de 1 a 10
        for (int j = 0; j < num_vertices; ++j) {
            // Número aleatório de arestas para o vértice j entre 2 e 6
            int num_arestas = rand() % 5 + 2;

            // Embaralha a lista de vértices excluindo o próprio vértice j
            vector<int> outros_vertices = vertices;
            outros_vertices.erase(find(outros_vertices.begin(), outros_vertices.end(), j));

            random_shuffle(outros_vertices.begin(), outros_vertices.end());

            // Seleciona aleatoriamente num_arestas vértices para conectar a j
            for (int k = 0; k < min(num_arestas, int(outros_vertices.size())); ++k) {
                int vertice_destino = outros_vertices[k];
                int peso = rand() % 10 + 1;
                outfile << j << " " << vertice_destino << " " << peso << endl;
            }
        }

        // Fecha o arquivo
        outfile.close();
    }

    cout << "Arquivos gerados com sucesso!" << endl;

    return 0;
}