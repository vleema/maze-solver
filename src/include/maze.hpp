#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace maze {
enum class Direction { Up, Down, Left, Right };
struct Position {
    size_t coord_x;
    size_t coord_y;
    /// Constructor
    Position(size_t x, size_t y) : coord_x(x), coord_y(y) {}

    bool operator==(const Position &rhs) const {
        return coord_x == rhs.coord_x and coord_y == rhs.coord_y;
    }
    Position operator+(const Position &rhs) const {
        return Position(coord_x + rhs.coord_x, coord_y + rhs.coord_y);
    }
    /// Overload to go in certain direction
    Position operator+(const Direction &dir) const {
        const std::array<Position, 4> directions = {
            Position(0, 1), Position(0, -1), Position(-1, 0),
            Position(1, 0)}; //!< Up, Down, Left, Right
        return *this + directions[(size_t)dir];
    }
};
class Maze {
  public:
    enum class Cell {
        Free = 0,
        Wall,
        Start,
        Finish,
    };

    /// Constructor
    Maze(const std::string &filename);

    /// Given a Position `pos` tells if `pos` is in bounds
    [[nodiscard]] bool in_bound(const Position &pos) const {
        return (pos.coord_y < m_height and pos.coord_x < m_width);
    }
    [[nodiscard]] Position start() const { return m_start; }
    /// Given a Position `pos` tells if `pos` is the finish or not
    [[nodiscard]] bool found_finish(const Position &pos) const {
        return pos == m_finish;
    }
    /// Given a Position `pos` and a direction `dir` see tells if the subsequent
    /// position is acessible or not
    bool is_blocked(const Position &pos, const Direction &dir) const {
        auto move = pos + dir;
        return in_bound(move) and
               m_maze[move.coord_y][move.coord_y] == Cell::Wall;
    }
    /// Converts the maze into a readable string
    [[nodiscard]] std::string str() const;

  private:
    std::vector<std::vector<Cell>> m_maze;
    size_t m_height;
    size_t m_width;
    Position m_start = Position(0, 0);
    Position m_finish = Position(0, 0);

    /// For initializing the maze
    void resize_maze() {
        m_maze.resize(m_height);
        for (auto &row : m_maze) {
            row.resize(m_width);
        }
    }
};
} // namespace maze
