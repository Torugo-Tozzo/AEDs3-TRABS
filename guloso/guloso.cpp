#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_set> // Para usar o conjunto não ordenado
#include <functional>    // Para usar std::hash
#include <utility>       // Para usar std::pair
#include <cstdlib>       // Para gerar números aleatórios
#include <ctime>         // Para obter o tempo atual para semente aleatória
#include <unistd.h>      // Para usleep

using namespace std;

// Definição de hash para pares de inteiros
struct pair_hash {
    template <class T1, class T2>
    size_t operator () (const pair<T1,T2> &p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

// Função para ler o arquivo e armazenar os caracteres em uma matriz
vector<vector<char>> lerArquivo(const string& nomeArquivo, pair<int, int>& pontoEntrada, pair<int, int>& dimensoes) {
    ifstream arquivo(nomeArquivo);
    vector<vector<char>> matriz;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        exit(1);
    }

    string linha;
    int linhaIndex = 0;
    while (getline(arquivo, linha)) {
        vector<char> linhaMatriz;
        for (size_t colunaIndex = 0; colunaIndex < linha.size(); colunaIndex++) {
            char c = linha[colunaIndex];
            linhaMatriz.push_back(c);
            if (c == 'E') {
                pontoEntrada = make_pair(linhaIndex, colunaIndex);
            }
        }
        matriz.push_back(linhaMatriz);
        linhaIndex++;
    }

    dimensoes = make_pair(matriz.size(), matriz[0].size());

    arquivo.close();
    return matriz;
}

// Função para movimentar o ponto na matriz
pair<int, int> movimentaPonto(const pair<int, int>& pontoEntrada, const vector<vector<char>>& matriz, const pair<int, int>& dimensoes, stack<pair<int, int>>& caminhos, vector<vector<int>>& visitados, pair<int, int>& lastMove) {
    int direcaoX[] = {0, 0, 1, -1}; // Movimento para cima, para baixo, para a direita e para a esquerda
    int direcaoY[] = {1, -1, 0, 0};

    vector<pair<int, int>> opcoes;
    bool encontrouSaida = false;

    // Adicionando a posição atual ao conjunto de visitados
    visitados[pontoEntrada.first][pontoEntrada.second]++;

    for (int i = 0; i < 4; ++i) {
        int novaLinha = pontoEntrada.first + direcaoX[i];
        int novaColuna = pontoEntrada.second + direcaoY[i];

        // Verificando se a nova posição está dentro dos limites da matriz e não é uma parede
        if (novaLinha >= 0 && novaLinha < dimensoes.first && novaColuna >= 0 && novaColuna < dimensoes.second && matriz[novaLinha][novaColuna] != 'X') {
            // Verificando se a nova posição já foi visitada menos de duas vezes
            if (visitados[novaLinha][novaColuna] < 2) {
                opcoes.push_back(make_pair(novaLinha, novaColuna));
                if (matriz[novaLinha][novaColuna] == 'S') {
                    encontrouSaida = true;
                    break; // Se encontrarmos a saída, não precisamos continuar procurando
                }
            }
        }
    }

    if (encontrouSaida) {
        lastMove = pontoEntrada; // Atualiza a última posição movida
        return make_pair(-1, -1); // Retorna uma posição inválida para indicar que encontramos a saída
    }

    if (opcoes.size() == 1) {
        lastMove = pontoEntrada; // Atualiza a última posição movida
        return opcoes.front(); // Se houver apenas uma opção de caminho, siga por ela
    } else if (opcoes.size() > 1) {
        caminhos.push(pontoEntrada); // Armazena a posição atual na pilha de caminhos
        lastMove = pontoEntrada; // Atualiza a última posição movida
        return opcoes.front(); // Escolhe uma opção de caminho e retorna
    } else if (!caminhos.empty()) {
        pair<int, int> ultimaBifurcacao = caminhos.top(); // Recupera a última bifurcação
        caminhos.pop(); // Remove a última bifurcação da pilha
        return ultimaBifurcacao; // Retorna para a última bifurcação
    } else {
        lastMove = pontoEntrada; // Atualiza a última posição movida
        return pontoEntrada; // Se não houver caminhos disponíveis e a pilha estiver vazia, permanece na posição atual
    }
}

int main() {
    string nomeArquivo = "../labirintos/labirinto5.txt"; // Substitua "arquivo.txt" pelo nome do seu arquivo
    pair<int, int> pontoEntrada, dimensoes, lastMove;
    stack<pair<int, int>> caminhos;
    int nPassos = 0;
    vector<vector<char>> matriz = lerArquivo(nomeArquivo, pontoEntrada, dimensoes);

    // Inicializando a matriz de visitados
    vector<vector<int>> visitados(dimensoes.first, vector<int>(dimensoes.second, 0));

    // Exibindo a matriz
    cout << "Matriz gerada a partir do arquivo:" << endl;
    for (const auto& linha : matriz) {
        for (char c : linha) {
            cout << c << " ";
        }
        cout << endl;
    }

    cout << "Ponto de entrada inicial: (" << pontoEntrada.second << ", " << (dimensoes.first - 1) - pontoEntrada.first << ")" << endl;

    while (matriz[pontoEntrada.first][pontoEntrada.second] != 'S') {
        pontoEntrada = movimentaPonto(pontoEntrada, matriz, dimensoes, caminhos, visitados, lastMove);
        if (pontoEntrada.first == -1 && pontoEntrada.second == -1) {
            cout << "Ponto final: S" << endl;
            break;
        }
        cout << "Ponto atual: (" << pontoEntrada.second << ", " << (dimensoes.first - 1) - pontoEntrada.first << ")" << endl;
        nPassos++;
        //usleep(500000); // Intervalo de 0.5 segundo a cada movimento (500.000 microssegundos)
    }

    cout << "Ponto final Encontrado em " << nPassos << " Movimentos!" << endl;

    return 0;
}
