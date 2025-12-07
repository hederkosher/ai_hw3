#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include <utility>

/**
 * Represents a maze with walls, start position, and goal position
 */
class Maze {
public:
    enum CellType {
        EMPTY = 0,
        WALL = 1,
        START = 2,
        GOAL = 3
    };

    // Constructor
    Maze();
    Maze(int width, int height);
    
    // Load maze from file or create programmatically
    bool loadFromFile(const std::string& filename);
    void createFromGrid(const std::vector<std::vector<int>>& grid);
    
    // Getters
    int getWidth() const;
    int getHeight() const;
    CellType getCell(int x, int y) const;
    std::pair<int, int> getStart() const;
    std::pair<int, int> getGoal() const;
    
    // Setters
    void setCell(int x, int y, CellType type);
    void setStart(int x, int y);
    void setGoal(int x, int y);
    
    // Check if position is valid
    bool isValid(int x, int y) const;
    bool isWalkable(int x, int y) const;
    
    // Print maze
    void print() const;
    
private:
    int width_;
    int height_;
    std::vector<std::vector<CellType>> grid_;
    std::pair<int, int> start_;
    std::pair<int, int> goal_;
};

#endif // MAZE_H

