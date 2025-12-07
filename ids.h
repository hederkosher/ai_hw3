#ifndef IDS_H
#define IDS_H

#include "maze.h"
#include <memory>
#include <utility>
#include <vector>

/**
 * Implements Iterative Deepening Search (IDS) algorithm
 * Performs a series of depth-limited DFS searches with increasing depth limits
 */
class IDS {
public:
  // Result structure containing path and statistics
  struct SearchResult {
    bool found;
    std::vector<std::pair<int, int>> path;
    int nodesExpanded;
    int maxDepth;
    int iterations;
  };

  // Constructor
  IDS(const Maze &maze);

  // Main search function - performs IDS
  SearchResult search();

  // Get the last search result
  SearchResult getLastResult() const;

private:
  const Maze &maze_;
  SearchResult lastResult_;

  // Depth-limited DFS (recursive helper)
  bool depthLimitedDFS(int x, int y, int depth, int maxDepth,
                       std::vector<std::pair<int, int>> &path,
                       std::vector<std::vector<bool>> &visited,
                       int &nodesExpanded);

  // Get valid neighbors (up, down, left, right)
  std::vector<std::pair<int, int>> getNeighbors(int x, int y) const;
};

#endif // IDS_H
