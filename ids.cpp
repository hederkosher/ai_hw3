#include "ids.h"
#include <iostream>
#include <algorithm>

IDS::IDS(const Maze& maze) : maze_(maze) {
    lastResult_.found = false;
    lastResult_.nodesExpanded = 0;
    lastResult_.maxDepth = 0;
    lastResult_.iterations = 0;
}

IDS::SearchResult IDS::search() {
    lastResult_.found = false;
    lastResult_.path.clear();
    lastResult_.nodesExpanded = 0;
    lastResult_.maxDepth = 0;
    lastResult_.iterations = 0;
    
    std::pair<int, int> start = maze_.getStart();
    std::pair<int, int> goal = maze_.getGoal();
    
    // Check if start and goal are valid
    if (start.first < 0 || start.second < 0 || goal.first < 0 || goal.second < 0) {
        std::cerr << "Error: Start or goal position not set" << std::endl;
        return lastResult_;
    }
    
    // Check if start is the goal
    if (start.first == goal.first && start.second == goal.second) {
        lastResult_.found = true;
        lastResult_.path.push_back(start);
        lastResult_.nodesExpanded = 1;
        lastResult_.maxDepth = 0;
        lastResult_.iterations = 1;
        return lastResult_;
    }
    
    // Iterative Deepening: try increasing depth limits
    int maxDepthLimit = maze_.getWidth() * maze_.getHeight(); // Upper bound
    int totalNodesExpanded = 0;
    
    for (int depthLimit = 0; depthLimit <= maxDepthLimit; depthLimit++) {
        lastResult_.iterations++;
        
        // Initialize visited matrix for this iteration
        std::vector<std::vector<bool>> visited(
            maze_.getHeight(), 
            std::vector<bool>(maze_.getWidth(), false)
        );
        
        std::vector<std::pair<int, int>> currentPath;
        int nodesExpandedThisIteration = 0;
        
        // Perform depth-limited DFS
        bool found = depthLimitedDFS(
            start.first, 
            start.second, 
            0, 
            depthLimit,
            currentPath,
            visited,
            nodesExpandedThisIteration
        );
        
        totalNodesExpanded += nodesExpandedThisIteration;
        
        if (found) {
            lastResult_.found = true;
            lastResult_.path = currentPath;
            lastResult_.nodesExpanded = totalNodesExpanded;
            lastResult_.maxDepth = depthLimit;
            return lastResult_;
        }
    }
    
    // Goal not found
    lastResult_.found = false;
    lastResult_.nodesExpanded = totalNodesExpanded;
    return lastResult_;
}

bool IDS::depthLimitedDFS(int x, int y, int depth, int maxDepth,
                          std::vector<std::pair<int, int>>& path,
                          std::vector<std::vector<bool>>& visited,
                          int& nodesExpanded) {
    // Check if we've exceeded depth limit
    if (depth > maxDepth) {
        return false;
    }
    
    // Check if current position is valid and walkable
    if (!maze_.isWalkable(x, y)) {
        return false;
    }
    
    // Check if already visited in this iteration
    if (visited[y][x]) {
        return false;
    }
    
    // Mark as visited and add to path
    visited[y][x] = true;
    path.push_back({x, y});
    nodesExpanded++;
    
    // Check if we've reached the goal
    std::pair<int, int> goal = maze_.getGoal();
    if (x == goal.first && y == goal.second) {
        return true;
    }
    
    // Get neighbors and explore them
    std::vector<std::pair<int, int>> neighbors = getNeighbors(x, y);
    
    for (const auto& neighbor : neighbors) {
        int nx = neighbor.first;
        int ny = neighbor.second;
        
        // Recursively search from neighbor
        if (depthLimitedDFS(nx, ny, depth + 1, maxDepth, path, visited, nodesExpanded)) {
            return true; // Goal found
        }
    }
    
    // Backtrack: remove current node from path if goal not found in this branch
    path.pop_back();
    return false;
}

std::vector<std::pair<int, int>> IDS::getNeighbors(int x, int y) const {
    std::vector<std::pair<int, int>> neighbors;
    
    // Four directions: up, down, left, right
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        if (maze_.isValid(nx, ny) && maze_.isWalkable(nx, ny)) {
            neighbors.push_back({nx, ny});
        }
    }
    
    return neighbors;
}

IDS::SearchResult IDS::getLastResult() const {
    return lastResult_;
}

