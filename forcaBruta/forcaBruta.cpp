#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> // Para gerar números aleatórios
#include <ctime>   // Para obter o tempo atual para semente aleatória
#include <unistd.h> // Para usleep

using namespace std;

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

// Função para movimentar o ponto aleatoriamente na matriz
pair<int, int> movimentaPonto(const pair<int, int>& pontoEntrada, const vector<vector<char>>& matriz, const pair<int, int>& dimensoes) {
    srand(time(0)); // Inicializa a semente aleatória com o tempo atual

    int direcaoX[] = {0, 0, 1, -1}; // Movimento para cima, para baixo, para a direita e para a esquerda
    int direcaoY[] = {1, -1, 0, 0};

    int novaLinha, novaColuna;
    do {
        int direcao = rand() % 4; // Escolhe uma direção aleatória

        novaLinha = pontoEntrada.first + direcaoX[direcao];
        novaColuna = pontoEntrada.second + direcaoY[direcao];
    } while ((novaLinha < 0 || novaLinha >= dimensoes.first || novaColuna < 0 || novaColuna >= dimensoes.second) ||
             matriz[novaLinha][novaColuna] == 'X' || matriz[novaLinha][novaColuna] == 'E');

    return make_pair(novaLinha, novaColuna);
}

int main() {
    string nomeArquivo = "../labirintos/labirinto2.txt"; // Substitua "arquivo.txt" pelo nome do seu arquivo
    pair<int, int> pontoEntrada;
    pair<int, int> dimensoes;
    int nPassos = 0;
    vector<vector<char>> matriz = lerArquivo(nomeArquivo, pontoEntrada, dimensoes);

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
        pontoEntrada = movimentaPonto(pontoEntrada, matriz, dimensoes);
        cout << "Ponto atual: (" << pontoEntrada.second << ", " << (dimensoes.first - 1) - pontoEntrada.first << ")" << endl;
        nPassos++;
        //usleep(1000000); // Intervalo de 1 segundo a cada movimento (1.000.000 microssegundos)
    }

    cout << "Ponto final Encontrado em " << nPassos << " Movimentos!" << endl;

    return 0;
}
