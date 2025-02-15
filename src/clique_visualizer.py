import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def visualize_clique_distribution():
    # Read the data
    df = pd.read_csv('clique_analysis.csv')
    
    # Calculate percentages
    df['has_clique_pct'] = df['has_clique'] / df['total_samples'] * 100
    df['no_clique_pct'] = df['no_clique'] / df['total_samples'] * 100
    
    # Create the stacked bar plot
    plt.figure(figsize=(12, 6))
    
    # Plot bars
    bars1 = plt.bar(df['graph_size'], df['no_clique_pct'], 
                    label='No Clique', color='lightcoral', alpha=0.7)
    bars2 = plt.bar(df['graph_size'], df['has_clique_pct'], bottom=df['no_clique_pct'],
                    label='Has Clique', color='lightgreen', alpha=0.7)
    
    # Customize the plot
    plt.xlabel('Graph Size')
    plt.ylabel('Percentage of Samples')
    plt.title(f'Distribution of Clique Occurrence by Graph Size\n'
              f'(Sample size per graph: {df["total_samples"].iloc[0]})')
    
    # Add grid for better readability
    plt.grid(True, axis='y', linestyle='--', alpha=0.7)
    
    # Add legend
    plt.legend()
    
    # Add percentage labels on the bars
    def add_labels(bars):
        for bar in bars:
            height = bar.get_height()
            if height > 5:  # Only show labels if segment is more than 5%
                plt.text(bar.get_x() + bar.get_width()/2, bar.get_y() + height/2,
                        f'{height:.1f}%', ha='center', va='center')
    
    add_labels(bars1)
    add_labels(bars2)
    
    # Adjust layout and display
    plt.tight_layout()
    plt.show()
    
    # Print summary statistics
    print("\nSummary Statistics:")
    print("-" * 50)
    print(f"Graph size range: {df['graph_size'].min()} to {df['graph_size'].max()}")
    print(f"Samples per size: {df['total_samples'].iloc[0]}")
    print("\nPercentage of graphs with cliques:")
    print(df[['graph_size', 'has_clique_pct']].to_string(index=False))

if __name__ == "__main__":
    visualize_clique_distribution()
