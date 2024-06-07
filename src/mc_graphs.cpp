#include <iostream>
#include <vector>
#include <random>

using namespace std;

// Declare the prototype for mc_complete_coloring
void mc_complete_coloring(vector<vector<int> >& adjacencyMatrix, int numVertices, double edgeProbability, mt19937& gen, uniform_real_distribution<>& dis);

vector<vector<int> > generateRandomGraph(int numVertices, double edgeProbability) {
    vector<vector<int> > adjacencyMatrix(numVertices, vector<int>(numVertices, -1));
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < numVertices; i++) {
        adjacencyMatrix[i][i] = 0; // Set diagonal elements to 0 (no self-loops)
    }

    mc_complete_coloring(adjacencyMatrix, numVertices, edgeProbability, gen, dis);

    return adjacencyMatrix;
}

void mc_complete_coloring(vector<vector<int> >& adjacencyMatrix, int numVertices, double edgeProbability, mt19937& gen, uniform_real_distribution<>& dis) {
    for (int i = 0; i < numVertices; i++) {
        for (int j = i + 1; j < numVertices; j++) {
            double randomValue = dis(gen);
            if (randomValue <= edgeProbability) {
                adjacencyMatrix[i][j] = 1;
                adjacencyMatrix[j][i] = 1; // Undirected graph
            }
        }
    }
}

void printAdjacencyMatrix(const vector<vector<int> >& adjacencyMatrix) {
    int numVertices = adjacencyMatrix.size();
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int numVertices = 10;
    double edgeProbability = 0.5;

    vector<vector<int> > adjacencyMatrix = generateRandomGraph(numVertices, edgeProbability);

    cout << "Adjacency Matrix:" << endl;
    printAdjacencyMatrix(adjacencyMatrix);

    return 0;
}
