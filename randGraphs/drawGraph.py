import networkx as nx
import matplotlib.pyplot as plt


def load_graph_from_file(filename):
    with open(filename, "r") as f:
        # Read header
        first_line = f.readline().split()
        num_nodes = int(first_line[0])
        num_edges = int(first_line[1])
        weighted = int(first_line[2]) == 1

        # Create graph (undirected)
        G = nx.Graph()

        # Add nodes explicitly (0 .. num_nodes-1)
        G.add_nodes_from(range(num_nodes))

        # Read edges
        for _ in range(num_edges):
            parts = f.readline().split()
            u = int(parts[0])
            v = int(parts[1])

            if weighted:
                w = float(parts[2])
                G.add_edge(u, v, weight=w)
            else:
                G.add_edge(u, v)

    return G, weighted


def draw_graph(G, weighted):
    plt.figure(figsize=(8, 8))

    # Layout determines how the graph looks
    pos = nx.spring_layout(G, seed=42)

    # Draw nodes and edges
    nx.draw(
        G,
        pos,
        with_labels=True,
        node_size=600,
        node_color="lightblue",
        edge_color="gray",
        font_size=10,
    )

    # If weighted, draw edge labels
    if weighted:
        edge_labels = nx.get_edge_attributes(G, "weight")
        nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

    plt.title("Graph Visualization")
    plt.show()


if __name__ == "__main__":
    filename = input("Enter graph file name: ").strip()
    G, weighted = load_graph_from_file(filename)
    draw_graph(G, weighted)
