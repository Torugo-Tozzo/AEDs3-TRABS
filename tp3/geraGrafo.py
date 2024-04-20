import random

# Gera um grafo aleatório com 25 vértices na forma de matriz de adjacência
num_vertices = 25
adj_matrix = [[0] * num_vertices for _ in range(num_vertices)]

# Definindo o número máximo de arestas por vértice
max_edges_per_vertex = 3

# Adicionando arestas aleatórias ao grafo
for vertex in range(num_vertices):
    # Determina o número de arestas para este vértice (no máximo 3)
    num_edges = min(random.randint(1, max_edges_per_vertex), num_vertices - 1)
    # Garante que não haverá arestas duplicadas
    connected_vertices = random.sample(range(num_vertices), num_edges)
    # Adiciona as arestas ao grafo
    for connected_vertex in connected_vertices:
        # O peso da aresta é um valor aleatório entre 1 e 10
        weight = random.randint(1, 10)
        adj_matrix[vertex][connected_vertex] = weight

# Escrevendo o grafo na matriz de adjacência em um arquivo de texto
with open("grafo_aleatorio_adjacencia.txt", "w") as file:
    file.write(f"{num_vertices}\n")
    for row in adj_matrix:
        file.write(" ".join(map(str, row)) + "\n")