#include <iostream>
#include <vector>
#include <cmath>
#include "mc_graphs.cpp"
#include "clique_search.cpp"

using namespace std;

vector<double> estimateCliqueDistribution(int N, int numSamples, double edgeProbability) {
    vector<double> cliqueDistribution(N + 1, 0.0);

    for (int i = 0; i < numSamples; i++) {
        vector<vector<int>> adjacencyMatrix = generateRandomGraph(N, edgeProbability);
        vector<int> cliqueCounts = countCliques(adjacencyMatrix);

        for (int j = 1; j <= N; j++) {
            cliqueDistribution[j] += cliqueCounts[j];
        }
    }

    for (int j = 1; j <= N; j++) {
        cliqueDistribution[j] /= numSamples;
    }

    return cliqueDistribution;
}

int main() {
    int N = 10; // Graph size
    int numSamples = 10000; // Number of Monte Carlo samples
    double edgeProbability = 0.5; // Edge probability

    vector<double> cliqueDistribution = estimateCliqueDistribution(N, numSamples, edgeProbability);

    cout << "Estimated clique distribution for a graph of size " << N << ":" << endl;
    for (int i = 1; i <= N; i++) {
        cout << "Cliques of size " << i << ": " << cliqueDistribution[i] << endl;
    }

    return 0;
}
