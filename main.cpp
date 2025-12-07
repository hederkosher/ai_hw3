#include "maze.h"
#include "ids.h"
#include <iostream>
#include <vector>

/**
 * Creates a sample maze for testing
 */
Maze createSampleMaze() {
    // Create a 7x7 maze
    // 0 = empty, 1 = wall, 2 = start, 3 = goal
    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1, 1, 1, 1},
        {1, 2, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 3, 1},
        {1, 1, 1, 1, 1, 1, 1}
    };
    
    Maze maze;
    maze.createFromGrid(grid);
    return maze;
}

/**
 * Creates a simple maze for testing
 */
Maze createSimpleMaze() {
    // Create a 5x5 maze
    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1, 1},
        {1, 2, 0, 0, 1},
        {1, 1, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {1, 1, 1, 3, 1}
    };
    
    Maze maze;
    maze.createFromGrid(grid);
    return maze;
}

void printPath(const std::vector<std::pair<int, int>>& path) {
    std::cout << "Path (" << path.size() << " steps): ";
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << "(" << path[i].first << "," << path[i].second << ")";
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout << "=== Iterative Deepening Search (IDS) Algorithm ===" << std::endl;
    std::cout << std::endl;
    
    Maze maze;
    
    // Try to load from file if provided, otherwise use sample maze
    if (argc > 1) {
        std::string filename = argv[1];
        std::cout << "Loading maze from file: " << filename << std::endl;
        if (!maze.loadFromFile(filename)) {
            std::cout << "Failed to load maze from file. Using sample maze instead." << std::endl;
            maze = createSampleMaze();
        }
    } else {
        std::cout << "No file provided. Using sample maze." << std::endl;
        maze = createSampleMaze();
    }
    
    std::cout << std::endl;
    std::cout << "Maze:" << std::endl;
    maze.print();
    std::cout << std::endl;
    
    std::pair<int, int> start = maze.getStart();
    std::pair<int, int> goal = maze.getGoal();
    
    std::cout << "Start position: (" << start.first << ", " << start.second << ")" << std::endl;
    std::cout << "Goal position: (" << goal.first << ", " << goal.second << ")" << std::endl;
    std::cout << std::endl;
    
    // Perform IDS search
    std::cout << "Performing Iterative Deepening Search..." << std::endl;
    std::cout << std::endl;
    
    IDS ids(maze);
    IDS::SearchResult result = ids.search();
    
    // Print results
    if (result.found) {
        std::cout << "✓ Goal found!" << std::endl;
        std::cout << std::endl;
        printPath(result.path);
        std::cout << std::endl;
        std::cout << "Statistics:" << std::endl;
        std::cout << "  - Nodes expanded: " << result.nodesExpanded << std::endl;
        std::cout << "  - Maximum depth: " << result.maxDepth << std::endl;
        std::cout << "  - Iterations: " << result.iterations << std::endl;
        std::cout << "  - Path length: " << result.path.size() << " steps" << std::endl;
    } else {
        std::cout << "✗ Goal not found!" << std::endl;
        std::cout << std::endl;
        std::cout << "Statistics:" << std::endl;
        std::cout << "  - Nodes expanded: " << result.nodesExpanded << std::endl;
        std::cout << "  - Iterations: " << result.iterations << std::endl;
    }
    
    return 0;
}

