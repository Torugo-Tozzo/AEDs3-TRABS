#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

    // Leitura do arquivo
vector<vector<int>> matriz = LeitorDeArquivo("meu_arquivo.csv");

// Impressão da matriz
for (int i = 0; i < matriz.size(); i++) {
  for (int j = 0; j < matriz[i].size(); j++) {
    std::cout << matriz[i][j] << " ";
  }
  std::cout << std::endl;
}

std::vector<std::vector<int>> ConverterParaMatriz(std::vector<std::string> linhas) {
  // Identificar tipo de estrutura
  TipoEstrutura tipo = IdentificarTipo(linhas);

  // Converter para matriz de acordo com o tipo
  if (tipo == Linhas) {
    return ConverterLinhasParaMatriz(linhas);
  } else if (tipo == Colunas) {
    return ConverterColunasParaMatriz(linhas);
  } else if (tipo == Blocos) {
    return ConverterBlocosParaMatriz(linhas);
  } else {
    // Erro: tipo de estrutura não suportado
  }
}


int main()
{
    cout << "teste" << endl;

    std::vector<std::vector<int>> matriz = LeitorDeArquivo("meu_arquivo.csv");

  // Converter para matriz
  matriz = ConverterParaMatriz(matriz);

  // Imprimir a matriz
  for (int i = 0; i < matriz.size(); i++) {
    for (int j = 0; j < matriz[i].size(); j++) {
      std::cout << matriz[i][j] << " ";



    return 0;
}