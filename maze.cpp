#include "maze.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

Maze::Maze() : width_(0), height_(0), start_({-1, -1}), goal_({-1, -1}) {
}

Maze::Maze(int width, int height) 
    : width_(width), height_(height), start_({-1, -1}), goal_({-1, -1}) {
    grid_.resize(height_, std::vector<CellType>(width_, EMPTY));
}

bool Maze::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }
    
    std::vector<std::vector<int>> grid;
    std::string line;
    int row = 0;
    
    while (std::getline(file, line)) {
        std::vector<int> row_data;
        std::istringstream iss(line);
        int value;
        
        while (iss >> value) {
            row_data.push_back(value);
            
            // Check for start (2) or goal (3)
            if (value == 2) {
                start_ = {static_cast<int>(row_data.size()) - 1, row};
            } else if (value == 3) {
                goal_ = {static_cast<int>(row_data.size()) - 1, row};
            }
        }
        
        if (!row_data.empty()) {
            grid.push_back(row_data);
        }
        row++;
    }
    
    if (grid.empty()) {
        std::cerr << "Error: Empty maze file" << std::endl;
        return false;
    }
    
    height_ = grid.size();
    width_ = grid[0].size();
    
    createFromGrid(grid);
    return true;
}

void Maze::createFromGrid(const std::vector<std::vector<int>>& grid) {
    height_ = grid.size();
    if (height_ == 0) {
        width_ = 0;
        return;
    }
    width_ = grid[0].size();
    
    grid_.resize(height_, std::vector<CellType>(width_));
    
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            grid_[y][x] = static_cast<CellType>(grid[y][x]);
            
            if (grid[y][x] == 2) {
                start_ = {x, y};
            } else if (grid[y][x] == 3) {
                goal_ = {x, y};
            }
        }
    }
}

int Maze::getWidth() const {
    return width_;
}

int Maze::getHeight() const {
    return height_;
}

Maze::CellType Maze::getCell(int x, int y) const {
    if (!isValid(x, y)) {
        throw std::out_of_range("Cell coordinates out of range");
    }
    return grid_[y][x];
}

std::pair<int, int> Maze::getStart() const {
    return start_;
}

std::pair<int, int> Maze::getGoal() const {
    return goal_;
}

void Maze::setCell(int x, int y, CellType type) {
    if (!isValid(x, y)) {
        throw std::out_of_range("Cell coordinates out of range");
    }
    grid_[y][x] = type;
    
    if (type == START) {
        start_ = {x, y};
    } else if (type == GOAL) {
        goal_ = {x, y};
    }
}

void Maze::setStart(int x, int y) {
    if (!isValid(x, y)) {
        throw std::out_of_range("Cell coordinates out of range");
    }
    // Clear old start
    if (start_.first >= 0 && start_.second >= 0) {
        grid_[start_.second][start_.first] = EMPTY;
    }
    start_ = {x, y};
    grid_[y][x] = START;
}

void Maze::setGoal(int x, int y) {
    if (!isValid(x, y)) {
        throw std::out_of_range("Cell coordinates out of range");
    }
    // Clear old goal
    if (goal_.first >= 0 && goal_.second >= 0) {
        grid_[goal_.second][goal_.first] = EMPTY;
    }
    goal_ = {x, y};
    grid_[y][x] = GOAL;
}

bool Maze::isValid(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}

bool Maze::isWalkable(int x, int y) const {
    if (!isValid(x, y)) {
        return false;
    }
    CellType cell = getCell(x, y);
    return cell != WALL;
}

void Maze::print() const {
    for (int y = 0; y < height_; y++) {
        for (int x = 0; x < width_; x++) {
            switch (grid_[y][x]) {
                case EMPTY:
                    std::cout << ". ";
                    break;
                case WALL:
                    std::cout << "# ";
                    break;
                case START:
                    std::cout << "S ";
                    break;
                case GOAL:
                    std::cout << "G ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

