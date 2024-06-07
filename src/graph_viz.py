import networkx as nx
import matplotlib.pyplot as plt

# Function to read adjacency matrix from C++ program
def read_adjacency_matrix():
    # Open the file containing the adjacency matrix
    with open("adjacency_matrix.txt", "r") as file:
        # Read the number of vertices
        num_vertices = int(file.readline().strip())

        # Initialize an adjacency matrix with zeros
        adj_matrix = [[0 for _ in range(num_vertices)] for _ in range(num_vertices)]

        # Read the adjacency matrix from the file
        for i in range(num_vertices):
            row = [int(x) for x in file.readline().strip().split()]
            for j in range(num_vertices):
                adj_matrix[i][j] = row[j]

    return adj_matrix

# Function to create and plot the graph
def plot_graph(adj_matrix):
    # Create a NetworkX graph object
    G = nx.Graph()

    # Add nodes to the graph
    num_vertices = len(adj_matrix)
    G.add_nodes_from(range(num_vertices))

    # Add edges to the graph based on the adjacency matrix
    for i in range(num_vertices):
        for j in range(num_vertices):
            if adj_matrix[i][j] == 1:
                G.add_edge(i, j)

    # Draw the graph
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True)
    plt.show()

# Main function
def main():
    # Read the adjacency matrix from C++ program
    adj_matrix = read_adjacency_matrix()

    # Plot the graph
    plot_graph(adj_matrix)

if __name__ == "__main__":
    main()
