#include <fstream>
#include <istream>
#include <list>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "color.h"
#include "maze.hpp"

// TODO: Implement colors in output

namespace {
std::optional<std::ifstream> open_file(const std::string &filename) {
    std::ifstream ifs_file(filename);
    if (not ifs_file.is_open())
        return std::nullopt;
    return ifs_file;
}
std::optional<std::pair<size_t, size_t>>
read_array_dimensions(const std::string &line) {
    std::istringstream iss(line);
    size_t height, width;
    iss >> height >> width;
    if (iss.fail() or iss.bad())
        return std::nullopt;
    return std::make_pair(height, width);
}
} // namespace

namespace maze {
Maze::Maze(const std::string &filename) : m_start(0, 0), m_finish(0, 0) {
    auto file = open_file(filename);
    if (not file.has_value())
        throw std::invalid_argument("Couldn't open file: " + filename);
    std::string file_line;
    size_t line_count = 0;
    bool first_line = true;
    while (std::getline(file.value(), file_line)) {
        if (first_line) {
            auto dimensions = read_array_dimensions(file_line);
            if (not dimensions.has_value())
                throw std::invalid_argument(
                    "Failed in reading header for maze file");
            m_height = dimensions.value().first;
            m_width = dimensions.value().second;
            resize_maze();
            first_line = false;
            continue;
        }
        size_t col_count = 0;
        for (const auto &ch : file_line) {
            if (ch == ' ' or ch == '\n')
                continue;
            auto cell = (Maze::Cell)(ch - '0');
            if (cell == Maze::Cell::Start)
                m_start = Position(col_count, line_count);
            if (cell == Maze::Cell::Finish)
                m_finish = Position(col_count, line_count);
            m_maze[line_count][col_count++] = cell;
        }
        line_count++;
    }
}

std::string Maze::str() const {
    constexpr char wall[] = "█";
    constexpr char free = ' ';
    constexpr char start[] = "Σ";
    constexpr char finish[] = "Ω";
    constexpr char path[] = "█";
    std::ostringstream oss;
    for (const auto &row : m_maze) {
        for (const auto &cell : row) {
            if (cell == Cell::Free)
                oss << free;
            else if (cell == Cell::Wall)
                oss << Color::tcolor(wall, Color::GREEN);
            else if (cell == Cell::Start)
                oss << Color::tcolor(start, Color::YELLOW);
            else if (cell == Cell::Finish)
                oss << Color::tcolor(finish, Color::MAGENTA);
            else if (cell == Cell::Path)
                oss << Color::tcolor(path, Color::RED);
        }
        oss << '\n';
    }
    oss << '\n'
        << Color::tcolor(start, Color::YELLOW) << " - Start\n"
        << Color::tcolor(finish, Color::MAGENTA) << " - Finish\n";
    return oss.str();
}

std::string Maze::str(std::list<Direction> &solution) const {
    auto maze_copy(*this);
    auto current_pos = start();

    for (const auto &dir : solution) {
        current_pos = current_pos + dir;
        maze_copy.m_maze[current_pos.coord_y][current_pos.coord_x] =
            (current_pos != m_finish) ? Cell::Path : Cell::Finish;
    }
    return maze_copy.str();
}
} // namespace maze
