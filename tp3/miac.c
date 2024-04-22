#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void inicializa(int ** arr, int numero_vertices, int vertice_inicial, int * pai, int * distancia){

    for (int i = 0; i < numero_vertices; i++){
        distancia[i] = 100;
        pai[i] = -1;
    }
    distancia[vertice_inicial] = 0;
}

void relaxa (int ** arr, int * distancia, int * pai, int v, int u){
    if (distancia[v] >= distancia[u] + arr[u][v]){
        distancia[v] = distancia[u] + arr[u][v];
        pai[v] = u;
    }
}

int extrai_minimo(int * Q, int * distancia, int numero_vertices){

    int menor =  100;
    int retorno = -1;
    
    for (int i = 0; i < numero_vertices; i++){
        if (Q[i] == 1 && distancia[i] <= menor){
            menor = distancia[i];
            retorno = i;
        } 
    }
    return retorno;
}

void dikstra(int ** arr, int vertice_inicial, int * distancia, int * pai, int numero_vertices){
    
    inicializa(arr, numero_vertices, vertice_inicial, pai, distancia);

    int S[numero_vertices], Q[numero_vertices], tam_q = numero_vertices, tam_s = 0;

    for (int i = 0; i < numero_vertices; i++){
        Q[i] = 1;
        S[i] = 0;
    }

    while (tam_q != 0){

        int vertice_atual = extrai_minimo(Q, distancia, numero_vertices);

        Q[vertice_atual] = 0; 
        tam_q--;
        S[vertice_atual] = 1;

        if (vertice_atual != -1){
            
            for (int i = 0; i < numero_vertices; i++){
                if (arr[vertice_atual][i] != 0){
                    relaxa(arr, distancia, pai, i, vertice_atual);
                }
            }
        }
        
    }
}

int main(){

    FILE *f = fopen("25.txt", "r");

    if (f == NULL) {
        printf("Unable to open file!\n");
        exit(1);
    }

    char character = '\0';
    int tam = 0;
    
    int valor;

    character = fscanf(f, "%d\n", &tam);
    printf("o tamanho eh %d\n", tam);
    
    int valores[tam];

    for(int i = 0; character != EOF; i++) {
        character = fscanf(f, "%d ", &valor);
        if(character != EOF){
            valores[i] = valor;
        }
    }
    
    int **matrizadj = (int **)malloc(tam * sizeof(int *));

    for (int i = 0; i < tam; i++) {
        printf(" o i eh %d e o tam eh %d\n", i, tam);
        matrizadj[i] = (int *)malloc(tam * sizeof(int));
        for (int j = 0; j < tam; j++) {
            matrizadj[i][j] = valores[i * tam + j];
        }
    }

    float closeness[tam];
    int total;

    for (int i = 0; i < 1; i++){
        
        total = 0;
        int pai[tam];
        int distancia[tam];

        dikstra(matrizadj, i, distancia, pai, tam);
        
        printf("Com vertice inicial %d\n", i);

        for (int j = 0; j < tam; j++){
            total = total + distancia[j];
            printf("O pai de %d eh %d e a distancia e %d\n", j, pai[j], distancia[j]);
        }
    
    }

    printf("%f\n", (float)total / (tam-1));

    fclose(f);
    free(matrizadj);

    return 0;
}