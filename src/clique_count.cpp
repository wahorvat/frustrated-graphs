#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <numeric>
#include "mc_graphs.cpp"
#include "clique_search.cpp"

using namespace std;


vector<double> estimateCliqueDistribution(int N, int numSamples, double edgeProbability, int cliqueSize) {
    vector<double> cliqueDistribution;

        for (int i = 0; i < numSamples; i++) {
            double redCliqueCounts;
            double blueCliqueCounts;
            vector<vector<int>> adjacencyMatrix = generateRandomGraph(N, edgeProbability);
            unordered_set<int> visited;

            if (hasClique(adjacencyMatrix, 1, cliqueSize, 1, visited) == true){
                redCliqueCounts += 1;
            }
        
            if (hasClique(adjacencyMatrix, 1, cliqueSize, -1, visited) == 1){
                blueCliqueCounts += 1;
            }

            cliqueDistribution[i] += redCliqueCounts + blueCliqueCounts;

            visited.clear(); // Clear the visited set for the next iteration
        }

    return cliqueDistribution;
}

int main() {
    int N = 5; // Graph size
    int numSamples = 100; // Number of Monte Carlo samples
    double edgeProbability = 0.5; // Edge probability
    int cliqueSize = 3; 

    vector<double> cliqueDistribution = estimateCliqueDistribution(N, numSamples, edgeProbability, cliqueSize);

    double cliqueSum = accumulate(cliqueDistribution.begin(), cliqueDistribution.end(), 0.0);
    double cliqueAvg = cliqueSum / cliqueDistribution.size();

    cout << "Estimated clique distribution for a graph of size " << N << ":" << endl;
    cout << cliqueAvg << endl;

    return 0;
}




