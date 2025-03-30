#include <iostream>

#include "timer.h"
#include <fstream>
#include <queue>
#include <unordered_map>

using namespace std;


template <typename T>
bool contains(const vector<T>& vec, const T& element) {
    return find(vec.begin(), vec.end(), element) != vec.end();
}

struct Vec2d {
    int d_row, d_column;

    Vec2d operator*(const int multiplicand) const {
        return {d_row * multiplicand, d_column * multiplicand};
    }

    bool operator==(const Vec2d &other) const {
        return d_row == other.d_row && d_column == other.d_column;
    }
};

struct Position {
    int row, column;

    [[nodiscard]] bool is_on_edge(const vector<vector<char>>& grid) const {
        return row == 0 || column == 0 || row == grid.size() - 1 || column == grid[0].size() - 1;
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
        return to_string(row) + to_string(column);
    }
};

struct PositionHash {
    size_t operator()(const Position& pos) const {
        return hash<string>()(pos.toString());
    }
};

struct Line {
    Position end_pos;
    Vec2d direction;
    int length;

    Line(const Position end, const Vec2d dir, const int len)
        : end_pos(end), direction(dir), length(len) {}

    [[nodiscard]] bool check_possible(const Position& pos) const {
        if (direction.d_row == 0) {
            return end_pos.row == pos.row;
        }
        if (direction.d_column == 0) {
            return end_pos.column == pos.column;
        }
        throw invalid_argument("Invalid distance vector");
    }
};

struct Grid {
    vector<vector<char>> grid;
    Position current_position;
    unordered_map<Position, vector<Vec2d>, PositionHash> direction_dict;
    int visited_cells = 1;
    vector<Line> lines;
    int moved_without_turn = 0;
    int direction_index = 0;
    constexpr static Vec2d directions[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int loop_count = 0;

    Grid(const vector<vector<char>>& grid_vec, const Position& start_pos)
        : grid(grid_vec), current_position(start_pos) {
    }

    [[nodiscard]] char get_char(const Position& pos) const {
        return grid[pos.row][pos.column];
    }

    void set_char(const Position& pos, const char& new_char) {
        grid[pos.row][pos.column] = new_char;
    }

    [[nodiscard]] bool find_loop_with_line(const Line &line) const {
        if (line.check_possible(current_position)) {
            const Vec2d next_direction = directions[(direction_index+1)%4];
            Position look_position = current_position;
            while (!look_position.is_on_edge(grid) && get_char(look_position) != '#' && look_position != line.end_pos) {
                look_position = look_position + next_direction;
            }
            if (look_position == line.end_pos) {
                return true;
            }
        }
        return false;
    }

    bool find_loop() {
        if (contains(direction_dict[current_position], directions[direction_index])) {
            return true;
        }
        Position next_test_pos = current_position;
        int direction_test_index = direction_index;
        while (true) {
            next_test_pos = next_test_pos + directions[direction_index];
            if (next_test_pos.is_on_edge(grid)) {
                return false;
            }
            if (get_char(next_test_pos + directions[direction_test_index]) == '#') {
                direction_test_index = (direction_test_index + 1) % 4;
            }
            if (contains(direction_dict[next_test_pos], directions[direction_test_index])) {
                return true;
            }
        }
    }

    bool move() {
        Vec2d direction = directions[direction_index];
        const Position next_pos = current_position + direction;
        if (get_char(next_pos) == '#') {
            lines.emplace_back(current_position, direction, moved_without_turn);
            moved_without_turn = 0;
            direction_index = (direction_index + 1) % 4;
            return false;
        }
        if (get_char(next_pos) == '.') {
            set_char(next_pos, 'X');
            visited_cells++;
        }
        direction_dict[current_position].emplace_back(directions[direction_index]);
        current_position = next_pos;
        moved_without_turn++;

        /*for (int i=static_cast<int>(lines.size())-3; i>=0; i-=4) {
            if (find_loop_with_line(lines[i])) {
                loop_count++;
                break;
            }
        }*/

        if (find_loop()) {
            loop_count++;
        }

        return true;
    }

    [[nodiscard]] bool is_on_edge() const {
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
                grid[row][column] = '.';
            }
            column++;
        }
        row++;
    }

    // cout << "Start Pos: " << final_pos.row << "," << final_pos.column << endl;
    return {grid, final_pos};
}


int code() {
    Grid grid = build_grid("Advent-of-Code/Day6/data.txt");

    while (!grid.is_on_edge()) {
        grid.move();
    }

    return grid.loop_count;
}


int main() {
    Timer timer;
    for (int i=0; i<1; i++) {
        cout << code() << endl;
        // code();
    }
    return 0;
}
