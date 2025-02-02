#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>

const int WIDTH = 20;
const int HEIGHT = 10;

enum Direction { NORTH, SOUTH, EAST, WEST };

struct Cell {
    bool visited;
    bool walls[4];

    Cell() : visited(false) {
        walls[NORTH] = walls[SOUTH] = walls[EAST] = walls[WEST] = true;
    }
};

std::vector<std::vector<Cell>> maze(HEIGHT, std::vector<Cell>(WIDTH));

bool is_valid(int x, int y) {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

Direction get_random_direction() {
    return static_cast<Direction>(rand() % 4);
}

void remove_wall(int x, int y, int nx, int ny, Direction dir) {
    maze[y][x].walls[dir] = false;
    switch (dir) {
        case NORTH: maze[ny][nx].walls[SOUTH] = false; break;
        case SOUTH: maze[ny][nx].walls[NORTH] = false; break;
        case EAST:  maze[ny][nx].walls[WEST] = false; break;
        case WEST:  maze[ny][nx].walls[EAST] = false; break;
    }
}

void generate_maze(int start_x, int start_y) {
    std::stack<std::pair<int, int>> stack;
    stack.push({start_x, start_y});
    maze[start_y][start_x].visited = true;

    while (!stack.empty()) {
        int x = stack.top().first;
        int y = stack.top().second;

        std::vector<Direction> directions = {NORTH, SOUTH, EAST, WEST};
        std::vector<Direction> unvisited_neighbors;

        for (Direction dir : directions) {
            int nx = x, ny = y;
            switch (dir) {
                case NORTH: ny = y - 1; break;
                case SOUTH: ny = y + 1; break;
                case EAST:  nx = x + 1; break;
                case WEST:  nx = x - 1; break;
            }

            if (is_valid(nx, ny) && !maze[ny][nx].visited) {
                unvisited_neighbors.push_back(dir);
            }
        }

        if (!unvisited_neighbors.empty()) {
            Direction dir = unvisited_neighbors[rand() % unvisited_neighbors.size()];
            int nx = x, ny = y;
            switch (dir) {
                case NORTH: ny = y - 1; break;
                case SOUTH: ny = y + 1; break;
                case EAST:  nx = x + 1; break;
                case WEST:  nx = x - 1; break;
            }

            remove_wall(x, y, nx, ny, dir);
            maze[ny][nx].visited = true;
            stack.push({nx, ny});
        } else {
            stack.pop();
        }
    }
}

void print_maze() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            std::cout << "+";
            if (maze[y][x].walls[NORTH]) {
                std::cout << "---";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "+" << std::endl;

        for (int x = 0; x < WIDTH; x++) {
            if (maze[y][x].walls[WEST]) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << "   ";
        }
        if (maze[y][WIDTH - 1].walls[EAST]) {
            std::cout << "|";
        }
        std::cout << std::endl;
    }

    for (int x = 0; x < WIDTH; x++) {
        std::cout << "+---";
    }
    std::cout << "+" << std::endl;
}

int main() {
    srand(time(0));

    generate_maze(0, 0);

    print_maze();

    return 0;
}