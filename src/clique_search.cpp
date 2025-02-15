#include <iostream>
#include <vector>
#include <algorithm>
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
    int N, numSamples, cliqueSize;
    double redPercent;

    // Get user input
    std::cout << "Enter the size of the graph (N): ";
    std::cin >> N;
    
    std::cout << "Enter the percentage of red edges (0-100): ";
    std::cin >> redPercent;

    std::cout << "Enter the number of samples to generate: ";
    std::cin >> numSamples;

    std::cout << "Enter the clique size to search for: ";
    std::cin >> cliqueSize;
    
    // Validate input
    if (N < 1 || redPercent < 0 || redPercent > 100 || numSamples < 1 || cliqueSize > N) {
        std::cout << "Invalid input parameters!" << std::endl;
        return 1;
    }

    // Initialize counters for statistics
    int redCliqueCount = 0;
    int blueCliqueCount = 0;
    int bothCliqueCount = 0;
    int noCliqueCount = 0;

    // Create the generator using the imported class
    ColoredGraphGenerator generator(N, redPercent);
    
    // Generate and analyze samples
    for (int i = 1; i <= numSamples; i++) {
        std::cout << "\nAnalyzing sample " << i << "..." << std::endl;
        
        // Generate new graph using imported generator
        auto adjacencyMatrix = generator.generateGraph();
        
        // Use imported methods to print and analyze the graph
        generator.printMatrix(adjacencyMatrix, i);
        generator.calculateStats(adjacencyMatrix);
        
        // Create clique detector and analyze
        CliqueDetector detector(adjacencyMatrix, cliqueSize);
        auto [hasRed, hasBlue] = detector.findCliques();
        
        // Update statistics
        if (hasRed && hasBlue) {
            bothCliqueCount++;
            std::cout << "Found both red and blue cliques of size " << cliqueSize << std::endl;
        } else if (hasRed) {
            redCliqueCount++;
            std::cout << "Found red clique of size " << cliqueSize << std::endl;
        } else if (hasBlue) {
            blueCliqueCount++;
            std::cout << "Found blue clique of size " << cliqueSize << std::endl;
        } else {
            noCliqueCount++;
            std::cout << "No monochromatic cliques of size " << cliqueSize << " found" << std::endl;
        }
        
        std::cout << std::string(50, '-') << std::endl;  // Separator line
    }

    // Print final statistics
    std::cout << "\nFinal Statistics for " << numSamples << " samples:" << std::endl;
    std::cout << "Graph size: " << N << std::endl;
    std::cout << "Red edge percentage: " << redPercent << "%" << std::endl;
    std::cout << "Clique size searched: " << cliqueSize << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Samples with only red cliques: " << redCliqueCount 
              << " (" << (100.0 * redCliqueCount / numSamples) << "%)" << std::endl;
    std::cout << "Samples with only blue cliques: " << blueCliqueCount 
              << " (" << (100.0 * blueCliqueCount / numSamples) << "%)" << std::endl;
    std::cout << "Samples with both colored cliques: " << bothCliqueCount 
              << " (" << (100.0 * bothCliqueCount / numSamples) << "%)" << std::endl;
    std::cout << "Samples with no cliques: " << noCliqueCount 
              << " (" << (100.0 * noCliqueCount / numSamples) << "%)" << std::endl;

    return 0;
}
