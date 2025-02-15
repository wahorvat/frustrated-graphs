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

    void printMatrix(const std::vector<std::vector<int>>& matrix, int sampleNumber) {
        std::cout << "\nSample #" << sampleNumber << " Adjacency Matrix (1 = Red, -1 = Blue):" << std::endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << std::setw(3) << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Method to calculate edge statistics
    void calculateStats(const std::vector<std::vector<int>>& matrix) {
        int totalEdges = (N * (N - 1)) / 2;  // Number of edges in complete graph
        int redEdges = 0;
        
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (matrix[i][j] == 1) redEdges++;
            }
        }
        
        double actualRedPercent = (static_cast<double>(redEdges) / totalEdges) * 100;
        std::cout << "Actual distribution: Red: " << std::fixed << std::setprecision(2) 
                  << actualRedPercent << "%, Blue: " << (100 - actualRedPercent) << "%" << std::endl;
    }
};

int main() {
    int N, numSamples;
    double redPercent, bluePercent;

    // Get user input
    std::cout << "Enter the size of the graph (N): ";
    std::cin >> N;
    
    std::cout << "Enter the percentage of red edges (0-100): ";
    std::cin >> redPercent;

    std::cout << "Enter the number of samples to generate: ";
    std::cin >> numSamples;
    
    bluePercent = 100 - redPercent;
    
    // Validate input
    if (N < 1 || redPercent < 0 || redPercent > 100 || numSamples < 1) {
        std::cout << "Invalid input parameters!" << std::endl;
        return 1;
    }

    std::cout << "\nGenerating " << numSamples << " complete graphs with:" << std::endl;
    std::cout << "Size: " << N << std::endl;
    std::cout << "Target distribution:" << std::endl;
    std::cout << "Red edges: " << redPercent << "%" << std::endl;
    std::cout << "Blue edges: " << bluePercent << "%" << std::endl;

    // Create and use the generator
    ColoredGraphGenerator generator(N, redPercent);
    
    // Generate and print requested number of samples
    for (int i = 1; i <= numSamples; i++) {
        auto adjacencyMatrix = generator.generateGraph();
        generator.printMatrix(adjacencyMatrix, i);
        generator.calculateStats(adjacencyMatrix);
        std::cout << std::string(50, '-') << std::endl;  // Separator line
    }

    return 0;
}
