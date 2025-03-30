#include <iostream>

#include "timer.h"
#include <fstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

enum cell_type {
    WALL,
    EMPTY,
    START
};

struct Vec2d {
    int d_row, d_column;

    bool operator==(const Vec2d& other) const {
        return d_row == other.d_row && d_column == other.d_column;
    }
};

struct Position {
    int row, column;

    [[nodiscard]] bool is_on_edge(const vector<vector<char>>& grid) const {
        return row == 0 || column == 0 || row == 130 - 1 || column == 130 - 1;
    }

    Position operator+(const Vec2d& vec) const {
         return {row + vec.d_row, column + vec.d_column};
     }

    Position operator-(const Vec2d& vec) const {
         return {row - vec.d_row, column - vec.d_column};
     }

    bool operator==(const Position& pos) const {
        return row == pos.row && column == pos.column;
    }

    [[nodiscard]] string toString() const {
        return to_string(row) + " " + to_string(column);
    }
};

struct PositionHash {
    size_t operator()(const Position& pos) const {
        // Use bit shifting to create a hash without string conversion
        return (static_cast<size_t>(pos.row) << 32) | static_cast<size_t>(pos.column);
    }
};

struct Grid {
    vector<vector<char>> grid;
    Position current_position;
    // unordered_map<Position, vector<Vec2d>, PositionHash> direction_dict{};
    int direction_index = 0;
    constexpr static Vec2d directions[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    unordered_set<Position, PositionHash> loop_obstacles;
    unordered_set<Position, PositionHash> checked_positions;

    Grid(const vector<vector<char>>& grid_vec, const Position& start_pos)
        : grid(grid_vec), current_position(start_pos) {
    }

    [[nodiscard]] char get_char(const Position& pos) const {
        return grid[pos.row][pos.column];
    }

    void set_char(const Position& pos, const char& new_char) {
        grid[pos.row][pos.column] = new_char;
    }

    bool find_loop(const Position& start_pos, const int& start_dir) const {
        unordered_set<string> visited;

        Position test_pos = start_pos;
        int direction_test_index = start_dir;

        while (!test_pos.is_on_edge(grid)) {
            string pos_dir_key = test_pos.toString() + ":" + to_string(direction_test_index);
            if (visited.contains(pos_dir_key)) {
                return true;
            }
            visited.insert(pos_dir_key);

            Position next_pos = test_pos + directions[direction_test_index];

            if (get_char(next_pos) == '#') {
                direction_test_index = (direction_test_index + 1) % 4;
            } else {
                test_pos = next_pos;
            }

        }
        return false;
    }

    void move() {
        Position next_pos = current_position + directions[direction_index];
        if (get_char(next_pos) == '#') {
            direction_index = (direction_index + 1) % 4;
            return;
        }

        if (next_pos.is_on_edge(grid)) {
            current_position = next_pos;
            return;
        }

        // Only check positions we haven't checked before
        if (!loop_obstacles.contains(next_pos) && !checked_positions.contains(next_pos)) {
            // Temporarily mark this position as an obstacle
            const char old_char = get_char(next_pos);
            if (old_char == '^') {
                current_position = next_pos;
                return;
            }
            set_char(next_pos, '#');

            // Start the loop check from the starting position with the original direction
            checked_positions.emplace(next_pos);
            if (find_loop(current_position, direction_index)) {
                loop_obstacles.emplace(next_pos);
            }

            // Restore the original character
            set_char(next_pos, old_char);
        }
        current_position = next_pos;
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
    Position final_start_pos{};
    int row = 0;
    while (getline(File, line)) {
        grid.emplace_back(line.begin(), line.end());
        int column = 0;
        for (const char c: line) {
            if (c == '^') {
                final_start_pos = Position(row, column);
            }
            column++;
        }
        row++;
    }

    // cout << "Start Pos: " << final_pos.row << "," << final_pos.column << endl;
    return {grid, final_start_pos};
}


int code() {
    Grid grid = build_grid("Advent-of-Code/Day6/data.txt");

    while (!grid.current_position.is_on_edge(grid.grid)) {
        grid.move();
    }

    return grid.loop_obstacles.size();
}


int main() {
    Timer timer;

    for (int i=0; i<1; i++) {
        cout << code() << endl;
        // code();
    }
    return 0;
}
