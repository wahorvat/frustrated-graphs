#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "mc_graphs.cpp"  // Include the existing file

class CliqueDetector {
private:
    int N;              // graph size
    int cliqueSize;     // desired clique size
    std::vector<std::vector<int>> graph;

    bool isMonochromaticClique(const std::vector<int>& vertices, int color) {
        for (size_t i = 0; i < vertices.size(); i++) {
            for (size_t j = i + 1; j < vertices.size(); j++) {
                if (graph[vertices[i]][vertices[j]] != color) {
                    return false;
                }
            }
        }
        return true;
    }

    bool findCliqueRecursive(std::vector<int>& currentClique, int vertexStart, int color) {
        if (currentClique.size() == cliqueSize) {
            return isMonochromaticClique(currentClique, color);
        }

        for (int v = vertexStart; v < N; v++) {
            bool canAdd = true;
            for (int u : currentClique) {
                if (graph[u][v] != color) {
                    canAdd = false;
                    break;
                }
            }

            if (canAdd) {
                currentClique.push_back(v);
                if (findCliqueRecursive(currentClique, v + 1, color)) {
                    return true;
                }
                currentClique.pop_back();
            }
        }
        return false;
    }

public:
    CliqueDetector(const std::vector<std::vector<int>>& adjacencyMatrix, int targetCliqueSize) 
        : graph(adjacencyMatrix), N(adjacencyMatrix.size()), cliqueSize(targetCliqueSize) {}

    std::pair<bool, bool> findCliques() {
        std::vector<int> currentClique;
        bool hasRedClique = findCliqueRecursive(currentClique, 0, 1);
        currentClique.clear();
        bool hasBlueClique = findCliqueRecursive(currentClique, 0, -1);
        return {hasRedClique, hasBlueClique};
    }
};

int main() {
    int startN, endN, numSamples, cliqueSize;
    double redPercent;

    // Get user input
    std::cout << "Enter the starting graph size (N): ";
    std::cin >> startN;
    std::cout << "Enter the ending graph size (M): ";
    std::cin >> endN;
    std::cout << "Enter the percentage of red edges (0-100): ";
    std::cin >> redPercent;
    std::cout << "Enter the number of samples per size: ";
    std::cin >> numSamples;
    std::cout << "Enter the clique size to search for: ";
    std::cin >> cliqueSize;
    
    // Validate input
    if (startN < 1 || endN < startN || redPercent < 0 || redPercent > 100 || 
        numSamples < 1 || cliqueSize > startN) {
        std::cout << "Invalid input parameters!" << std::endl;
        return 1;
    }

    // Open output file
    std::ofstream outFile("clique_analysis.csv");
    outFile << "graph_size,total_samples,has_clique,no_clique\n";

    // For each graph size
    for (int currentN = startN; currentN <= endN; currentN++) {
        std::cout << "\nAnalyzing graphs of size " << currentN << "..." << std::endl;
        
        int hasCliqueCount = 0;
        int noCliqueCount = 0;

        ColoredGraphGenerator generator(currentN, redPercent);
        
        // Generate and analyze samples
        for (int i = 1; i <= numSamples; i++) {
            auto adjacencyMatrix = generator.generateGraph();
            CliqueDetector detector(adjacencyMatrix, cliqueSize);
            auto [hasRed, hasBlue] = detector.findCliques();
            
            if (hasRed || hasBlue) {
                hasCliqueCount++;
            } else {
                noCliqueCount++;
            }
            
            if (i % 10 == 0) {
                std::cout << "Processed " << i << "/" << numSamples << " samples\r" << std::flush;
            }
        }
        
        // Write results to file
        outFile << currentN << "," << numSamples << "," 
                << hasCliqueCount << "," << noCliqueCount << "\n";
        
        std::cout << "\nCompleted analysis for size " << currentN << std::endl;
        std::cout << "Has clique: " << hasCliqueCount << ", No clique: " << noCliqueCount << std::endl;
    }

    outFile.close();
    std::cout << "\nResults have been written to clique_analysis.csv" << std::endl;

    return 0;
}
