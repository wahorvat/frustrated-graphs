#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

class ColoredGraphGenerator {
private:
    int N; // graph size
    double redPercentage; // percentage of red edges
    std::mt19937 rng;

public:
    ColoredGraphGenerator(int size, double red_percent) 
        : N(size), redPercentage(red_percent) {
        // Initialize random number generator with current time
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        rng = std::mt19937(seed);
    }

    std::vector<std::vector<int>> generateGraph() {
        // Initialize adjacency matrix with zeros
        std::vector<std::vector<int>> adjacencyMatrix(N, std::vector<int>(N, 0));
        
        // Create distribution for edge coloring
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        
        // Fill the adjacency matrix
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                // Randomly assign color based on probability
                double random_value = dist(rng);
                int color = (random_value < redPercentage/100.0) ? 1 : -1;
                
                // Set symmetric entries in adjacency matrix
                adjacencyMatrix[i][j] = color;
                adjacencyMatrix[j][i] = color;
            }
        }
        
        return adjacencyMatrix;
    }

    void printMatrix(const std::vector<std::vector<int>>& matrix) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << std::setw(3) << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    int N;
    double redPercent, bluePercent;

    // Get user input
    std::cout << "Enter the size of the graph (N): ";
    std::cin >> N;
    
    std::cout << "Enter the percentage of red edges (0-100): ";
    std::cin >> redPercent;
    
    bluePercent = 100 - redPercent;
    
    // Validate input
    if (N < 1 || redPercent < 0 || redPercent > 100) {
        std::cout << "Invalid input parameters!" << std::endl;
        return 1;
    }

    std::cout << "\nGenerating complete graph with:" << std::endl;
    std::cout << "Size: " << N << std::endl;
    std::cout << "Red edges: " << redPercent << "%" << std::endl;
    std::cout << "Blue edges: " << bluePercent << "%" << std::endl;

    // Create and use the generator
    ColoredGraphGenerator generator(N, redPercent);
    auto adjacencyMatrix = generator.generateGraph();
    
    std::cout << "\nAdjacency Matrix (1 = Red, -1 = Blue):" << std::endl;
    generator.printMatrix(adjacencyMatrix);

    return 0;
}
