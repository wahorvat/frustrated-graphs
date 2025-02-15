# Monte Carlo Sampling of Complete Graphs 

Monte Carlo study of emergence of cliques of size n as graph size increases. 

Sampling, clique counting, and visulaization methods provided as follows.

Example use: 

 ```
# Compile
g++ clique_detector.cpp -o clique_detector

# Run detector
./clique_detector
> Enter the starting graph size (N): 5
> Enter the ending graph size (M): 15
> Enter the percentage of red edges (0-100): 50
> Enter the number of samples per size: 1000
> Enter the clique size to search for: 3

# Run visualizer
python clique_visualizer.py
```
