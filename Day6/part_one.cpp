#include <iostream>

#include "timer.h"
#include <fstream>

using namespace std;


struct vec2d {
    int d_row, d_column;
};

struct Position {
    int row, column;

     bool is_on_edge(const vector<vector<char>>& grid) const {
        return row == 0 || column == 0 || row == grid.size() - 1 || column == grid[0].size() - 1;
    }

    Position operator+(const vec2d& vec) const {
         return {row + vec.d_row, column + vec.d_column};
     }
};

struct Grid {
    vector<vector<char>> grid;
    Position current_position;
    int visited_cells = 1;

    char get_char(const Position& pos) const {
        return grid[pos.row][pos.column];
    }

    void set_char(const Position& pos, const char& new_char) {
        grid[pos.row][pos.column] = new_char;
    }

    bool move(const vec2d& direction) {
        const Position next_pos = current_position + direction;
        if (get_char(next_pos) == '#') {
            return false;
        }
        if (get_char(next_pos) == '.') {
            set_char(next_pos, 'X');
            visited_cells++;
        }
        current_position = next_pos;
        return true;
    }

    bool is_on_edge() const {
        return current_position.is_on_edge(grid);
    }
};


Grid build_grid(const string& path) {
    ifstream File(path);
    if (!File.is_open()) {
        throw invalid_argument("Couldn't open file correctly");
    }

    vector<vector<char>> grid;
    grid.reserve(130);
    string line;
    Position final_pos{};
    int row = 0;
    while (getline(File, line)) {
        grid.emplace_back(line.begin(), line.end());
        int column = 0;
        for (char c: line) {
            if (c == '^') {
                final_pos = Position(row, column);
            }
            column++;
        }
        row++;
    }

    if (final_pos.row == 0 && final_pos.column == 0 && grid[final_pos.row][final_pos.column] != '^') {
        throw invalid_argument("Didn't find start pos");
    }
    // cout << "Start Pos: " << final_pos.row << "," << final_pos.column << endl;
    return Grid(grid, final_pos);
}


int code() {
    Grid grid = build_grid("Advent-of-Code/Day6/data.txt");

    int direction_index = 0;
    constexpr vec2d directions[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    while (!grid.is_on_edge()) {
        if (!grid.move(directions[direction_index])) {
            direction_index = (direction_index + 1) % 4;
        }
    }

    return grid.visited_cells;
}


int main() {
    Timer timer;
    for (int i=0; i<1; i++) {
        cout << code() << endl;
        // code();
    }
    return 0;
}
