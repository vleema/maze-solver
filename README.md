# Maze Solver

Program to solve a maze in c++ using BFS.

```
>>> The Maze has solution!:
  ·····█   █       █·········█         █
 █·███·█ █ ███ ███ █·███████·███████ █ █
 █···█Ω█ █ █   █   █···█   █Σ█     █ █ █
 ███·█ █ █ █ ███ █████·█ █ ███ ███ █ ███
   █·█   █ █ █   █·····█ █       █ █   █
██ █·█████ █ █████·█████ ███████ █ ███ █
   █·█   █ █ █···█···█         █ █     █
 ███·█ █ █ █ █·█·███·███████████ █████ █
 █···█ █     █·█·  █···█·····█   █   █ █
 █·███ ███████·█·█████·█·███·█ ███ █ ███
 █·█ █ █ █·····█·······█·█···█     █   █
██·█ █ █ █·█████████████·█·█████ █████ █
···█ █ █ █·█          ···█·····█ █ █   █
·███ █ █ █·███████ ███·███████·█ █ █ ███
·█       █···█···█ █···█     █·█   █   █
·███████████·█·█·███·█████ █ █·███████ █
·····█·····█···█·····█···  █ █·······█ █
 ███·█·███·███████████·█·███████████·█ █
   █···  █·············█·············  █
████████████████████████████████████████

```

## Usage

You can generate your own maze using `scripts/gen_maze.py` with the following options:

```
usage: gen_maze.py [-h] FILE [HEIGHT] [WIDTH]

Generate a maze with a start and finish.

positional arguments:
  FILE        File to save the maze
  HEIGHT      Height of the maze
  WIDTH       Width of the maze

options:
  -h, --help  show this help message and exit
```

Or use a pre-generated one that is already in the repo. If you want to use another one with name other than `data/out1.dat`, make sure to alter the correspondent code in [`src/main.cpp`](src/main.cpp).


```cpp
// In main.cpp
maze::Maze maze("data/out1.dat"); //!< Change to desired file
```

### Compiling and running

> Make sure you have cmake and a c++ compiler installed

In project root folder:

1. Source `CMakeLists.txt` and create `build/` directory:

    ```
    cmake -S . -B build
    ```

2. Compile the program:
    
    ```
    cmake --build build
    ```

3. The executable will be `build/maze`. Run-it!
    
    ```
    ./build/maze
    ``` 


# Contributing

- [ ] Get the `.dat` file from config file and/or command line.
- [ ] Show colors for visualizing in terminal.
- [ ] Animate the search process into a video.

---
&copy; IMD/UFRN 2024.
