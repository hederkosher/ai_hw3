# Iterative Deepening Search (IDS) for Maze Solving

This project implements the Iterative Deepening Search (IDS) algorithm to find a path from a start position to a goal position in a maze.

## Project Structure

The project is organized in a modular way with separate header and implementation files:

- `maze.h` / `maze.cpp` - Maze representation and management
- `ids.h` / `ids.cpp` - Iterative Deepening Search algorithm implementation
- `main.cpp` - Main program that demonstrates the algorithm
- `Makefile` - Build configuration

## Building the Project

To build the project, simply run:

```bash
make
```

This will create an executable named `maze_solver`.

## Running the Program

Run the program with:

```bash
./maze_solver
```

Or with a maze file:

```bash
./maze_solver maze.txt
```

## Maze File Format

If you want to load a maze from a file, the format should be:
- `0` = empty cell (walkable)
- `1` = wall (not walkable)
- `2` = start position
- `3` = goal position

Example:
```
1 1 1 1 1
1 2 0 0 1
1 1 1 0 1
1 0 0 0 1
1 1 1 3 1
```

## Algorithm Description

The Iterative Deepening Search (IDS) algorithm:
1. Performs a series of depth-limited DFS searches
2. Starts with depth limit 0 and increments by 1 each iteration
3. If the goal is not found, increases the depth limit and searches again
4. Continues until the goal is found or all possible depths are exhausted

**Time Complexity:** O(b^d) where b is the branching factor and d is the depth of the solution
**Space Complexity:** O(d) - only stores nodes along the current search path

## Cleaning

To remove build artifacts:

```bash
make clean
```

