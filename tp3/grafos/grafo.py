import networkx as nx
import matplotlib.pyplot as plt

# Carregar o grafo a partir de um arquivo
G = nx.read_edgelist("grafo3.txt", nodetype=int, data=(('weight',int),))

# Calcular a closeness centrality de cada vértice
closeness = nx.closeness_centrality(G)

# Definir cores com base na closeness centrality
cores = [closeness[v] for v in G.nodes()]

# Plotar o grafo
nx.draw(G, with_labels=True, node_color=cores, cmap=plt.cm.plasma)
plt.show()