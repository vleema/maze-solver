#!/usr/bin/python3
import argparse
import random

def create_maze(height, width):
    maze = [[1 for _ in range(width)] for _ in range(height)]

    def carve_path(x, y):
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        random.shuffle(directions)
        for dx, dy in directions:
            nx, ny = x + dx * 2, y + dy * 2
            if 0 <= nx < height and 0 <= ny < width and maze[nx][ny] == 1:
                maze[nx][ny] = 0
                maze[x + dx][y + dy] = 0
                carve_path(nx, ny)

    start_x, start_y = random.randrange(0, height, 2), random.randrange(0, width, 2)
    maze[start_x][start_y] = 0
    carve_path(start_x, start_y)

    finish_x, finish_y = random.randrange(0, height, 2), random.randrange(0, width, 2)
    maze[start_x][start_y] = 2
    maze[finish_x][finish_y] = 3

    return maze, start_x, start_y, finish_x, finish_y

def save_maze(file_name, maze):
    with open(file_name, 'w') as file:
        height = len(maze)
        width = len(maze[0])
        file.write(f"{height} {width}\n")
        for row in maze:
            file.write("".join(map(str, row)) + "\n")

def main():
    parser = argparse.ArgumentParser(description="Generate a maze with a start and finish.")
    parser.add_argument("FILE", help="File to save the maze")
    parser.add_argument("HEIGHT", type=int, nargs='?', default=random.randint(10, 20), help="Height of the maze")
    parser.add_argument("WIDTH", type=int, nargs='?', default=random.randint(10, 20), help="Width of the maze")
    args = parser.parse_args()

    maze, start_x, start_y, finish_x, finish_y = create_maze(args.HEIGHT, args.WIDTH)
    save_maze(args.FILE, maze)

if __name__ == "__main__":
    main()
