#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Generate Erdos-Renyi graph with p(+1 (red)) = 0.5, remaining possible edges are -1 (blue).
Final dual adjacency matrix is that of a random complete graph with maximum disorder
*/

vector<vector<int> > GenerateRandomGraph(int nodes, double red_prob) {
    // Set the seed for random number generation
    srand(time(NULL));

    // Number of nodes
    int n = nodes;

    // Initialize the dual adjacency matrix with -1 (blue)
    vector<vector<int> > adj_matrix(n, vector<int>(n, -1));

    // Generate the adjacency matrix using Monte Carlo method
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                // Set the diagonal elements to 0
                adj_matrix[i][j] = 0;
            } else {
                // Generate a random number between 0 and 1
                double random_num = static_cast<double>(rand()) / RAND_MAX;

                // If the random number is less than redProb, set the edge to 1 = red
                if (random_num < red_prob) {
                    adj_matrix[i][j] = 1;
                    adj_matrix[j][i] = 1;
                }
            }
        }
    }

    // Print dual adjacency matrix
    // cout << "Adjacency Matrix:" << endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << adj_matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return adj_matrix;
}

