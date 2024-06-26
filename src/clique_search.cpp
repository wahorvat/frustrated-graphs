#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// Function to check if a clique of a given size exists
int HasClique(const vector<vector<int>>& adj_matrix, int start, int length, int edge_type, unordered_set<int>& visited, int curr_length = 0, int curr_node = -1) {
    if (curr_length == length) {
        // Check if the last node can form a cycle with the start node
        if (adj_matrix[curr_node][start] == edge_type) {
            return true;
        } else {
        return false;
        }
    }

    visited.insert(curr_node);

    for (int i = 0; i < adj_matrix.size(); i++) {
        if (adj_matrix[curr_node][i] == edge_type && visited.count(i) == 0) {
            if (HasClique(adj_matrix, start, length, edge_type, visited, curr_length + 1, i)) {
                return true;
            }
        }
    }

    visited.erase(curr_node);
    return 0;
}