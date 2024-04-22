import networkx as nx
import matplotlib.pyplot as plt

# Função para ler o grafo da matriz de adjacência do arquivo
def read_adjacency_matrix(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
        num_vertices = int(lines[0])
        matrix = [list(map(int, line.split())) for line in lines[1:]]
        return num_vertices, matrix

# Função para ler as centralidades de proximidade do arquivo
def read_closeness(filename):
    with open(filename, 'r') as file:
        closeness = {}
        for line in file:
            vertex, centrality = map(float, line.split())
            closeness[int(vertex)] = centrality
        return closeness

# Ler o grafo da matriz de adjacência
num_vertices, adjacency_matrix = read_adjacency_matrix("grafo_ponderado_adjacencia.txt")

# Criar o grafo direcionado
G = nx.Graph()

# Adicionar os vértices ao grafo
for i in range(num_vertices):
    G.add_node(i)

# Adicionar as arestas ponderadas ao grafo
for i in range(num_vertices):
    for j in range(num_vertices):
        if adjacency_matrix[i][j] != 0:
            G.add_edge(i, j)

# Ler as centralidades de proximidade
closeness = read_closeness("centralidades.txt")

# Definir cores com base nas centralidades de proximidade
colors = [closeness[v] for v in G.nodes()]

# Plotar o grafo
pos = nx.spring_layout(G)  # Layout para melhor visualização
nx.draw(G, pos, with_labels=True, node_color=colors, cmap=plt.cm.plasma, node_size=500)

# Salvar a figura como um arquivo PNG
plt.savefig("grafo_com_centralidades.png", format="png", dpi=300)