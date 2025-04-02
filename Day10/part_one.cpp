#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <array>

#include "timer.h"

using namespace std;

struct Position {
    int row, column;

    Position(const int row, const int column)
        : row(row), column(column) {}

    [[nodiscard]] bool in_bounds(const int size) const {
        return row >= 0 && row < size && column >= 0 && column < size;
    }

    bool operator==(const Position& other) const {
        return row == other.row && column == other.column;
    }

    Position operator+(const Position& other) const {
        return {row + other.row, column + other.column};
    }
};

struct PositionHash {
    size_t operator()(const Position &pos) const {
        return hash<int>()(pos.row) ^ hash<int>()(pos.column);
    }
};


unordered_set<Position, PositionHash>& search(const vector<vector<int>>& digits, vector<vector<unordered_set<Position,PositionHash>>>& peaks, const Position& now_pos, const int now_digit, const int size) {
    const int row = now_pos.row;
    const int column = now_pos.column;

    const array<Position, 4> directions = {{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

    unordered_set<Position,PositionHash>& now_set = peaks[row][column];
    if (!now_set.empty()) {
        return now_set;
    }
    if (now_digit == 9) {
        now_set.insert(now_pos);
        return now_set;
    }
    for (const Position& direction : directions) {
        const Position next_pos = now_pos + direction;
        if (next_pos.in_bounds(size) && digits[next_pos.row][next_pos.column] == now_digit+1) {
            unordered_set<Position, PositionHash>& return_set = search(digits, peaks, next_pos, now_digit+1, size);
            now_set.insert(return_set.begin(), return_set.end());
        }
    }
    return now_set;
}


int calculate(const vector<vector<int>>& digits, const vector<Position>& zero_positions, const int size) {
    vector peaks(size,vector<unordered_set<Position,PositionHash>>(size));

    int sum = 0;

    for (Position p: zero_positions) {
        auto return_set = search(digits, peaks, p, 0, size);
        sum += static_cast<int>(return_set.size());
    }
    return sum;
}

int code() {
    ifstream DataFile("Advent-of-Code/Day10/data.txt");
    if (!DataFile.is_open()) {
        cerr << "File not found!" << endl;
        return 1;
    }

    vector<vector<int>> digits;
    vector<Position> zero_positions;

    string line;
    int i = 0;
    while (getline(DataFile, line)) {
        vector<int> row;
        row.reserve(line.size());
        int j = 0;
        for (const char c: line) {
            int n = c - '0';
            if (n == 0) {
                zero_positions.emplace_back(i, j);
            }
            row.emplace_back(n);
            j++;
        }
        digits.emplace_back(row);
        i++;
    }

    return calculate(digits, zero_positions, i);
}


int main() {
    Timer timer;
    cout << code() << endl;

    return 0;
}

