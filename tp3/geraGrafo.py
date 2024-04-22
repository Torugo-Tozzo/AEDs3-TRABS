import random

# Gera um grafo aleatório conexo com 30 vértices na forma de matriz de adjacência
num_vertices = 30
adj_matrix = [[0] * num_vertices for _ in range(num_vertices)]

# Limitando o número máximo de arestas por vértice
max_edges_per_vertex = 4

# Adiciona arestas aleatórias ao grafo
for vertex in range(num_vertices):
    # Determina o número de arestas para este vértice (no máximo 4)
    num_edges = min(random.randint(1, max_edges_per_vertex), num_vertices - 1)
    # Garante que não haverá arestas duplicadas
    connected_vertices = random.sample(range(num_vertices), num_edges)
    for connected_vertex in connected_vertices:
        # Garante que não adicionamos uma aresta de um vértice para ele mesmo
        if connected_vertex != vertex:
            # Peso aleatório entre 1 e 10
            weight = random.randint(1, 10)
            # Adiciona aresta bidirecional
            adj_matrix[vertex][connected_vertex] = weight
            adj_matrix[connected_vertex][vertex] = weight

# Escrevendo o grafo ponderado na matriz de adjacência em um arquivo de texto
with open("grafo_ponderado_adjacencia.txt", "w") as file:
    file.write(f"{num_vertices}\n")
    for row in adj_matrix:
        file.write(" ".join(map(str, row)) + "\n")