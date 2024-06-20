#include <iostream>

#include "maze.hpp"
#include "solver.hpp"

int main(int argc, char *argv[]) {
    // [1] - Parsing the data file for the maze;
    maze::Maze maze("data/out1.dat");
    // [2] - Founding a solution and printing
    auto maze_solution = maze::Solver::solve(maze);
    if (maze_solution.has_value()) {
        std::cout << ">>> The Maze has solution!:\n"
                  << maze.str(maze_solution.value());
    } else {
        std::cout << ">>> Unfortanely this maze has no solution :(\n";
        std::cout << maze.str();
    }
    return 0;
}
