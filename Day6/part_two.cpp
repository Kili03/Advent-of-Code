#include <iostream>

#include "timer.h"
#include <fstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;


template <typename T>
bool contains(const vector<T>& vec, const T& element) {
    return find(vec.begin(), vec.end(), element) != vec.end();
}

struct Vec2d {
    int d_row, d_column;

    bool operator==(const Vec2d &other) const {
        return d_row == other.d_row && d_column == other.d_column;
    }
};

struct Position {
    int row, column;

    [[nodiscard]] bool is_on_edge(const vector<vector<char>>& grid) const {
        return row <= 0 || column <= 0 || row >= grid.size() - 1 || column >= grid[0].size() - 1;
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
        return hash<string>()(pos.toString());
    }
};

struct Grid {
    vector<vector<char>> grid;
    Position current_position;
    unordered_map<Position, vector<Vec2d>, PositionHash> direction_dict{};
    int direction_index = 0;
    constexpr static Vec2d directions[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    unordered_set<Position, PositionHash> loop_obstacles;

    Grid(const vector<vector<char>>& grid_vec, const Position& start_pos)
        : grid(grid_vec), current_position(start_pos) {
    }

    [[nodiscard]] char get_char(const Position& pos) const {
        return grid[pos.row][pos.column];
    }

    void set_char(const Position& pos, const char& new_char) {
        grid[pos.row][pos.column] = new_char;
    }

    bool find_loop() const {
        unordered_map<Position, vector<Vec2d>, PositionHash> direction_test_dict;
        direction_test_dict[current_position].emplace_back(directions[direction_index]);

        if (get_char(current_position + directions[direction_index]) == '^') {
            return false;
        }

        Position next_test_pos = current_position;
        int direction_test_index = (direction_index + 1) % 4;

        while (!next_test_pos.is_on_edge(grid)) {
            if (contains(direction_test_dict[next_test_pos], directions[direction_test_index])) {
                // cout << "Found loop after " << checked_positions << " positions" << endl;
                return true;
            }
            direction_test_dict[next_test_pos].emplace_back(directions[direction_test_index]);

            if (get_char(next_test_pos + directions[direction_test_index]) == '#') {
                direction_test_index = (direction_test_index + 1) % 4;
            } else {
                next_test_pos = next_test_pos + directions[direction_test_index];
            }

        }
        return false;
    }

    void move() {
        Position next_pos = current_position + directions[direction_index];
        if (get_char(next_pos) == '#') {
            direction_index = (direction_index + 1) % 4;
            // next_pos = current_position + directions[direction_index];
        } else {
            current_position = next_pos;
        }

        if (current_position.is_on_edge(grid)) {
            return;
        }
        // direction_dict[current_position].emplace_back(directions[direction_index]);

        if (find_loop()) {
            if (!loop_obstacles.contains(current_position + directions[direction_index])) {
                loop_obstacles.emplace(current_position + directions[direction_index]);
            }
        }
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
