#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include "mc_graphs.cpp"
#include "clique_search.cpp"

using namespace std;


vector<double> estimateCliqueDistribution(int N, int numSamples, double edgeProbability, int cliqueSize) {
    vector<double> cliqueDistribution(N + 1, 0.0);
    vector<int> redCliqueCounts;
    vector<int> blueCliqueCounts;

        for (int i = 0; i < numSamples; i++) {
        vector<vector<int>> adjacencyMatrix = generateRandomGraph(N, edgeProbability);
        unordered_set<int> visited;

        int redCliqueCounts = hasClique(adjacencyMatrix, 1, cliqueSize, 1, visited);
        int blueCliqueCounts = hasClique(adjacencyMatrix, 1, cliqueSize, -1, visited);

        for (int j = cliqueSize; j <= N; j++) {
            cliqueDistribution[j] += redCliqueCounts[j - 1] + blueCliqueCounts[j - 1];
        }

        visited.clear(); // Clear the visited set for the next iteration
    }

    for (int j = cliqueSize; j <= N; j++) {
        cliqueDistribution[j] /= numSamples;
    }

    return cliqueDistribution;


int main() {
    int N = 10; // Graph size
    int numSamples = 10000; // Number of Monte Carlo samples
    double edgeProbability = 0.5; // Edge probability
    int cliqueSize = 3; 

    vector<double> cliqueDistribution = estimateCliqueDistribution(N, numSamples, edgeProbability, cliqueSize);

    cout << "Estimated clique distribution for a graph of size " << N << ":" << endl;
    for (int i = 1; i <= N; i++) {
        cout << "Cliques of size " << i << ": " << cliqueDistribution[i] << endl;
    }

    return 0;
}




