#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <numeric>
#include "mc_graphs.cpp"
#include "clique_search.cpp"

using namespace std;


vector<double> EstimateCliqueDistribution(int N, int num_samples, double edge_probability, int clique_size) {
    vector<double> cliqueDistribution;

        for (int i = 0; i < num_samples; i++) {
            double red_clique_counts;
            double blue_clique_counts;
            vector<vector<int>> adjacency_matrix = GenerateRandomGraph(N, edge_probability);
            unordered_set<int> visited;

            if (HasClique(adjacency_matrix, 1, clique_size, 1, visited) == true){
                red_clique_counts += 1;
            }
        
            if (HasClique(adjacency_matrix, 1, clique_size, -1, visited) == 1){
                blue_clique_counts += 1;
            }

            cliqueDistribution[i] += red_clique_counts + blue_clique_counts;

            visited.clear(); // Clear the visited set for the next iteration
        }

    return cliqueDistribution;
}

int main() {
    int N = 5; // Graph size
    int num_samples = 100; // Number of Monte Carlo samples
    double edge_probability = 0.5; // Edge probability
    int clique_size = 3; 

    vector<double> clique_distribution = EstimateCliqueDistribution(N, num_samples, edge_probability, clique_size);

    double clique_sum = accumulate(clique_distribution.begin(), clique_distribution.end(), 0.0);
    double clique_avg = clique_sum / clique_distribution.size();

    cout << "Estimated clique distribution for a graph of size " << N << ":" << endl;
    cout << clique_avg << endl;

    return 0;
}




