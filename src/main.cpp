#include "maze.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    maze::Maze maze("data/out1.dat");
    std::cout << maze.str();
    return 0;
}
