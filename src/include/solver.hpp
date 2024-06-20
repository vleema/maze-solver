#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <list>
#include <map>
#include <optional>
#include <queue>
#include <string>
#include <unordered_set>

#include "maze.hpp"

namespace maze {
class Solver {
  public:
    using MaybeDirList = std::optional<std::list<Direction>>;
    using PositionUSet = std::unordered_set<Position, Position::Hash>;

    /// Method to solve the maze
    static MaybeDirList solve(const Maze &maze);

    /// Method to print the solution from start to finish
    static std::string str(const Maze &maze, std::list<Direction> &solution);

  private:
    /// Method to get the opposite direction
    static Direction opposite(const Direction &dir) {
        switch (dir) {
        case Direction::Up:
            return Direction::Down;
        case Direction::Down:
            return Direction::Up;
        case Direction::Left:
            return Direction::Right;
        case Direction::Right:
            return Direction::Left;
        default:
            return Direction::None;
        }
    }
    /// Method to reconstruct the shorter path from start to finish
    static std::list<Direction>
    reconstruct_path(std::map<Position, Direction> &came_from, Position start,
                     Position end) {
        std::list<Direction> path;
        Position current = end;
        while (current != start) {
            path.push_front(came_from[current]);
            current = current + opposite(came_from[current]);
        }
        return path;
    }
    /// Method to verify that a Position was already visited
    static bool already_visited(const Position &pos,
                                const PositionUSet &visited) {
        return visited.find(pos) != visited.cend();
    }
    /// Method to visit a position and save that o Solver variables
    static void visit_position(const Position &pos,
                               std::queue<Position> &to_visit,
                               PositionUSet &visited) {
        to_visit.push(pos);
        visited.insert(pos);
    }
};
} // namespace maze

#endif // !SOLVER_HPP
